#include <stdlib.h>

int main() {
    int *data = (int *) malloc(sizeof(int) * 100);
    data[100] = 0;
    return 0;
}