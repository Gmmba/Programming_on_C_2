#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100

typedef struct {
    char name[64];
    int math;
    int physics;
    int informatics;
    int total;
} Student;


Student addStudent(const char* name, int math, int physics, int informatics) {
    Student newStudent;
    strncpy(newStudent.name, name, sizeof(newStudent.name) - 1);
    newStudent.name[sizeof(newStudent.name) - 1] = '\0';
    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.informatics = informatics;
    newStudent.total = math + physics + informatics;
    return newStudent;
}


void printStudentInfo(Student student) {
    printf("Имя: %s, Математика: %d, Физика: %d, Информатика: %d, Общий балл: %d\n",
           student.name, student.math, student.physics, student.informatics, student.total);
}


void countingSort(Student arr[], int size) {
    int max = 300;
    Student output[size];
    int count[max + 1];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < size; i++) {
        count[arr[i].total]++;
    }

    for (int i = max - 1; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    for (int i = 0; i < size; i++) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}


int partition(Student arr[], int low, int high) {
    int pivot = arr[high].total;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].total >= pivot) {
            i++;
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// вывод информации о процессоре
void printCPUInfo() {
    printf("Информация о процессоре:\n");
    system("cat /proc/cpuinfo | grep 'model name' | uniq");
}

int main() {
    Student students[N];
    srand(time(NULL));


    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Student_%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }


    printCPUInfo();

    // вывод до сортировки
    printf("Список студентов до сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }


    clock_t start = clock();
    countingSort(students, N);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nВремя работы Counting Sort: %f секунд\n", time_taken);


    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Student_%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    // замер времени сортировки QuickSort
    start = clock();
    quickSort(students, 0, N - 1);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nВремя работы QuickSort: %f секунд\n", time_taken);

    // вывод после сортировки QuickSort
    printf("\nСписок студентов после сортировки QuickSort:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    return 0;
}
