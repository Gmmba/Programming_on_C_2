#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: 1 argument expected.\n");
        printf("Usage: %s <Positive integer>\n", argv[0]);
        return 1;
    }

    if (!is_valid_positive_integer(argv[1])) {
        fprintf(stderr, "Error: bad value. Argument needs to be positive integer greater than zero.\n");
        return 1;
    }

    int *n = (int *)malloc(sizeof(int));
    if (!n) {
        fprintf(stderr, "Error: failure in memory allocation.\n");
        return 1;
    }

    *n = atoi(argv[1]);
    printf("Triangle number T(%d) = %d\n\n", *n, triangle_recursive(*n));

    triangle_to_file(*n, "triangle.txt");

    free(n);
    return 0;
}
