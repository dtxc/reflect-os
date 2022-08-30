#pragma once

#include "../kernel/core/types.h"

#define e 2.71828182845
#define pi 3.14159265359
#define nan 0x7F800001
#define TAYLOR_SERIES_N 10

float abs(float x);
float sin(float x);
float cos(float x);
float tan(float x);
float sec(float x);
float csc(float x);
float cot(float x);
float sinh(int x);
float cosh(int x);
float tanh(int x);
u64 factorial(u16 x);
float pow(float x, int y);
float exp(int x);
complex32_t ln(float x);
complex32_t log(float x, float base);
complex64_t sqrt(double x);
float asin(float x);
float acos(float x);
float atan(float x);
float acsc(float x);
float asec(float x);
float acot(float x);
float asinh(float x);
complex32_t acosh(float x);
complex32_t atanh(float x);
float acsch(float x);
float asech(float x);
float acoth(float x);
