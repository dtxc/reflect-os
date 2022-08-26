#pragma once

#include <stdint.h>

#define e 2.71828182845
#define pi 3.14159265359

typedef struct {
    float Re, Im;
} complex32_t;

typedef struct {
    double Re, Im;
} complex64_t;

float add(float x, float y);
float sub(float x, float y);
float mult(float x, float y);
float div(float x, float y); 
float abs(float x);
float sin(float x);
float cos(float x); //sine and cosine are defined using taylor expansion
float tan(float x);
float sec(float x);
float csc(float x);
float cot(float x);
float sinh(int x);
float cosh(int x);
float tanh(int x);
uint64_t factorial(uint16_t x);
float pow(float x, int y);
float exp(int x);
//uint64_t perm(uint16_t x, uint16_t y);
