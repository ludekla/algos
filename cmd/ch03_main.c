#include <stdio.h>

#include "ch03_recursion.h"

int main() {

    int n = 10;

    // factorial
    int result;

    // normal recursion
    result = factorial(n);
    printf("Factorial of %d: %d\n", n, result);

    // tail recursion
    result = factorial_tail(n, 1);
    printf("Factorial of %d: %d\n", n, result);

    // harmonic series
    float harm;

    // normal recursion
    harm = harmonic_series(n);
    printf("Harmonic series for %d: %f\n", n, harm);

    // tail recursion
    harm = harmonic_series_tail(n, 1);
    printf("Harmonic series for %d: %f\n", n, harm);

    int m = fibonacci(6);
    printf("Fibonacci(6): %d\n", m);

    return 0;
}

