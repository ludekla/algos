#include "ch03_recursion.h"

int factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n-1);
}

int factorial_tail(int n, int a) {
    if (n < 0) return 0;
    if (n == 0 || n == 1)
        return a;
    return factorial_tail(n-1, n*a);
}

float harmonic_series(int n) {
    if (n < 0 || n == 0) return 0;
    if (n == 1)
        return 1.0;
    return 1.0 / n + harmonic_series(n-1);
}

float harmonic_series_tail(int n, float a) {
    if (n < 0 || n == 0) return 0;
    if (n == 1)
        return a;
    return harmonic_series_tail(n-1, a + 1.0 / n);
}
