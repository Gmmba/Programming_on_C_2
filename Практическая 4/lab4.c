// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_LINE_LENGTH 2048

// void reverseWord(char *word) {
//     int len = strlen(word);
//     for (int i = 0; i < len / 2; i++) {
//         char temp = word[i];
//         word[i] = word[len - i - 1];
//         word[len - i - 1] = temp;
//     }
// }

// void processLine(char *line) {
//     char *token = strtok(line, " .,-?");
//     while (token) {
//         reverseWord(token);
//         printf("%s ", token);
//         token = strtok(NULL, " .,-?");
//     }
//     printf("\n");
// }

// int main() {
//     FILE *inputFile = fopen("file.txt", "r");
//     FILE *outputFile = fopen("ofile.txt", "w");
//     if (!inputFile || !outputFile) {
//         perror("Ошибка открытия файла");
//         return EXIT_FAILURE;
//     }

//     char line[MAX_LINE_LENGTH];
//     while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
//         line[strcspn(line, "\n")] = 0; // Удаляем символ новой строки
//         processLine(line);
//         fprintf(outputFile, "%s\n", line);
//     }

//     fclose(inputFile);
//     fclose(outputFile);
//     return EXIT_SUCCESS;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2048

void reverseWord(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len / 2; i++) {
        char temp = word[i];
        word[i] = word[len - i - 1];
        word[len - i - 1] = temp;
    }
}

void processLine(const char *line, char *output) {
    char temp[MAX_LINE_LENGTH];  
    strcpy(temp, line);  // Make a copy to avoid modifying original line

    char *token = strtok(temp, " ");
    output[0] = '\0'; // Ensure output buffer is empty

    while (token) {
        reverseWord(token);
        strcat(output, token);
        token = strtok(NULL, " ");
        if (token) strcat(output, " "); // Add space between words
    }
}

int main() {
    FILE *inputFile = fopen("file.txt", "r");
    FILE *outputFile = fopen("ofile.txt", "w");
    if (!inputFile || !outputFile) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH], output[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        processLine(line, output);
        fprintf(outputFile, "%s\n", output);
    }

    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}

