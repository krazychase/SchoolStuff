#include <stdlib.h>

int main() {
    int *x = (int *) malloc(sizeof(int));
    x = NULL;
    free(*x);
    return 0;
}