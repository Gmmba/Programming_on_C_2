// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// pthread_mutex_t mutex;
// pthread_cond_t cond;
// int turn = 0;

// void* thread_func(void* arg) {
//     for (int i = 0; i < 5; i++) {
//         pthread_mutex_lock(&mutex);
//         while (turn != 1)
//             pthread_cond_wait(&cond, &mutex);

//         printf("Дочерний: строка %d\n", i + 1);
//         turn = 0;
//         pthread_cond_signal(&cond);
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// int main() {
//     pthread_t thread;

//     pthread_mutex_init(&mutex, NULL);
//     pthread_cond_init(&cond, NULL);

//     pthread_create(&thread, NULL, thread_func, NULL);

//     for (int i = 0; i < 5; i++) {
//         pthread_mutex_lock(&mutex);
//         while (turn != 0)
//             pthread_cond_wait(&cond, &mutex);

//         printf("Родительский: строка %d\n", i + 1);
//         turn = 1;
//         pthread_cond_signal(&cond);
//         pthread_mutex_unlock(&mutex);
//     }

//     pthread_join(thread, NULL);
//     pthread_mutex_destroy(&mutex);
//     pthread_cond_destroy(&cond);

//     return 0;
// }

// ---------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **A, **B, **C;
int N, thread_count;

void* multiply(void* arg) {
    int id = *(int*)arg;
    int start = id * (N / thread_count);
    int end = (id + 1) * (N / thread_count);

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    free(arg);
    return NULL;
}

void print_matrix(int** M, const char* name) {
    printf("Matrix %s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Deployment: %s <matrix size N> <number of threads>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    thread_count = atoi(argv[2]);

    A = malloc(N * sizeof(int*));
    B = malloc(N * sizeof(int*));
    C = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    pthread_t threads[thread_count];

    for (int i = 0; i < thread_count; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, multiply, id);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    if (N <= 5) {
        print_matrix(A, "A");
        print_matrix(B, "B");
        print_matrix(C, "C");
    }

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A); free(B); free(C);

    return 0;
}

// ---------------------------------------

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <sys/time.h>

// int **A, **B, **C;
// int N, thread_count;

// void* multiply(void* arg) {
//     int id = *(int*)arg;
//     int start = id * (N / thread_count);
//     int end = (id + 1) * (N / thread_count);

//     for (int i = start; i < end; i++) {
//         for (int j = 0; j < N; j++) {
//             C[i][j] = 0;
//             for (int k = 0; k < N; k++) {
//                 C[i][j] += A[i][k] * B[k][j];
//             }
//         }
//     }

//     free(arg);
//     return NULL;
// }

// double time_diff_ms(struct timeval start, struct timeval end) {
//     return (end.tv_sec - start.tv_sec) * 1000.0 +
//            (end.tv_usec - start.tv_usec) / 1000.0;
// }

// int main(int argc, char* argv[]) {
//     if (argc != 3) {
//         printf("Использование: %s <размер матрицы N> <кол-во потоков>\n", argv[0]);
//         return 1;
//     }

//     N = atoi(argv[1]);
//     thread_count = atoi(argv[2]);

//     A = malloc(N * sizeof(int*));
//     B = malloc(N * sizeof(int*));
//     C = malloc(N * sizeof(int*));
//     for (int i = 0; i < N; i++) {
//         A[i] = malloc(N * sizeof(int));
//         B[i] = malloc(N * sizeof(int));
//         C[i] = malloc(N * sizeof(int));
//         for (int j = 0; j < N; j++) {
//             A[i][j] = 1;
//             B[i][j] = 1;
//         }
//     }

//     pthread_t threads[thread_count];

//     struct timeval start, end;
//     gettimeofday(&start, NULL);

//     for (int i = 0; i < thread_count; i++) {
//         int* id = malloc(sizeof(int));
//         *id = i;
//         pthread_create(&threads[i], NULL, multiply, id);
//     }

//     for (int i = 0; i < thread_count; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     gettimeofday(&end, NULL);
//     printf("Размер матрицы: %d, Потоки: %d, Время: %.2f мс\n",
//            N, thread_count, time_diff_ms(start, end));

//     for (int i = 0; i < N; i++) {
//         free(A[i]); free(B[i]); free(C[i]);
//     }
//     free(A); free(B); free(C);

//     return 0;
// }




