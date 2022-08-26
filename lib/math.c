#include "math.h"
#include <stdbool.h>

float abs(float x) {
    if (x < 0) return pow(x, 2)/x;
    return x;
}

float sin(float x) {
    float res = 0;
    float pow = x;
    float fac = 1;

    for (int i = 0; i < 5; i++) {
        res += pow/fac;
        pow *= -1*x*x;
        fac *= (2*(i+1))*(2*(i+1)+1);
    }
    return res;
}

float cos(float x) {
    return 1 - ((x*x)/(2)) + ((x*x*x*x)/(24)) - ((x*x*x*x*x*x)/(720)) + ((x*x*x*x*x*x*x*x)/(40320));
}

float tan(float x) {
    return sin(x)/cos(x);
}

float sec(float x) {
    return 1/cos(x);
}

float csc(float x) {
    return 1/sin(x);
}

float cot(float x) {
    return cos(x)/sin(x);
}

float sinh(int x) {
    return (pow(e, x)-pow(e, -x))/2;
}

float cosh(int x) {
    return (pow(e, x)+pow(e, -x))/2;
}

float tanh(int x) {
    return sinh(x)/cosh(x);
}

uint64_t factorial(uint16_t x) {
    uint64_t res = 1;
    for (int i = 2; i < x; i++) {
        res *= i;
    }
    return res;
}

float pow(float x, int y) {
    bool neg = false;
    if (y == 0) return 1;
    if (y < 0) {
        y = abs(y);
        neg = true;
    }
    float res = x;
    for (int i = 1; i < y; i++) {
        res *= x;
    }
    if (neg) return 1/res;
    return res;
}

float exp(int x) {
    return pow(e, x);
}

uint64_t perm(uint16_t x, uint16_t y) {
    return factorial(x)/(factorial(x-y));
}
