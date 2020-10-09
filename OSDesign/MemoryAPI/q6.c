#include <stdlib.h>
#include <stdio.h>

int main() {
    int *data = (int *) malloc(sizeof(int) * 100);
    // free(data);
    // printf(data[13]);
    free(data[13]);
    return 0;
}