#include <stdio.h>

int match_ints(const void* data1, const void* data2) {
    return *(int*)data1 == *(int*)data2;
}

int main() {

    int a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    return 0;
}

