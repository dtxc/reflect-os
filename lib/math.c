/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include "math.h"

float abs(float x) {
    if (x < 0) return pow(x, 2)/x;
    return x;
}

float sin(float x) {
    float res;
    for (int i = 0; i <= TAYLOR_SERIES_N; i++) {
        res += (pow(-1, i)/(factorial(2*i+1)))*pow(x, 2*i+1);
    }
    return res;
}

float cos(float x) {
    //return 1 - ((x*x)/(2)) + ((x*x*x*x)/(24)) - ((x*x*x*x*x*x)/(720)) + ((x*x*x*x*x*x*x*x)/(40320));
    float res;
    for (int i = 0; i <= TAYLOR_SERIES_N; i++) {
        res += (pow(-1, i)/(factorial(2*i)))*pow(x, 2*i);
    }
    return res;
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

u64 factorial(u16 x) {
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

complex32_t ln(float x) {
    complex32_t complex;
    if (x < 0) {
        x = abs(x);
        complex.Im = pi;
    }
    unsigned int a = *(unsigned int * ) &x;
    unsigned int b = a >> 23;
    signed int t = (signed int)b - (signed int)127;
    unsigned int s = (t < 0) ? (-t) : t;
    a = 1065353216 | (a & 8388607);
    x = * (float *) &x;
    complex.Re = -1.49278+(2.11263+(-0.729104+0.10969*x)*x)*x+0.6931471806*t;
    return complex;
}

complex32_t log(float x, float base) {
    complex32_t res;
    complex32_t complex = ln(x);
    complex32_t complex1 = ln(base);

    res.Re = complex.Re/complex1.Re;
    res.Im = complex.Im/complex1.Im;
    return res;
}

complex64_t sqrt(double x) {
    complex64_t complex;
    if (x == 0){
        complex.Im = 0;
        complex.Re = 0;
        return complex;
    }
    double a = (x < 0) ? abs(x) : x;
    double b = 0;
    double c = x/2;
    while (c*c != x) {
        if (c*c > x) a = c;
        else b = c;
        double d = (a+b)/2;
        if (c == d) break;
        c = d;
    }
    complex.Re = (x < 0) ? 0 : c;
    complex.Im = (x < 0) ? c : 0;
    return complex;
}

float asin(float x) {
    if (abs(x) > 1) return *(float *) nan;
    //return x + pow(x, 3)/6 + (3*pow(x, 5))/40 + (5*pow(x, 7))/112;
    float res;
    for (int i = 0; i <= TAYLOR_SERIES_N; i++) {
        //res += factorial(2*i)/(pow(4, i)*pow(factorial(i), 2)*(2*i+1))*pow(2, 2*i+1);
        res += factorial(2*i)/(pow(4, i)*pow(factorial(i), 2)*(2*i+1))*pow(x, 2*i+1);
    }
    return res;
}

float acos(float x) {
    if (x > 1) return *(float *) nan;
    return pi/2 - asin(x);
}

float atan(float x) {
    if (abs(x) > 1) return *(float *)nan;
    float res;
    for (int i = 0; i <= TAYLOR_SERIES_N; i++) {
        res += (pow(-1, i)/(2*i+1))*pow(x, 2*i+1);
    }
    return res;
}

float acsc(float x) {
    return asin(1/x);
}

float asec(float x) {
    return acos(1/x);
}

float acot(float x) {
    return atan(1/x);
}

float asinh(float x) {
    complex64_t root = sqrt(pow(x, 2)+1);
    return ln(x+root.Re).Re;
}

complex32_t acosh(float x) {
    complex64_t root = sqrt(pow(x, 2)-1);
    complex32_t q;
    q.Re = root.Re + ln(x+root.Re).Re;
    q.Im = root.Im + ln(x+root.Im).Im;
    return q;
}

complex32_t atanh(float x) {
    if (x == 1) {
        complex32_t q;
        q.Re = *(float *)nan;
        q.Im = 0;
        return q;
    }
    complex32_t q;
    q.Re = ln(1+x/1-x).Re/2;
    q.Im = ln(1+x/1-x).Im/2;
    return q;
}

float acsch(float x) {
    return ln(1/x + sqrt(1/pow(x, 2)+1).Re).Re;
}

float asech(float x) {
    return ln(sqrt(1 - pow(x, 2)).Re/x).Re;
}

float acoth(float x) {
    return ln((x + 1)/(x - 1)).Re/2;
}