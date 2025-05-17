#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "triangle.h"

// Рекурсивная функция
int triangle_recursive(int n) {
    if (n == 1)
        return 1;
    return n + triangle_recursive(n - 1);
}

// Запись треугольника чисел
void triangle_to_file(int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            int val = triangle_recursive(j);
            fprintf(file, "%d ", val);
            printf("%d ", val);
        }
        fprintf(file, "\n");
        printf("\n");
    }

    fclose(file);
}

// Проверка, что строка — положительное целое число
int is_valid_positive_integer(const char *str) {
    if (str == NULL || *str == '\0')
        return 0;

    for (int i = 0; str[i]; i++) {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }

    int val = atoi(str);
    return val > 0;
}
