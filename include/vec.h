#pragma once
#include <stdio.h>

typedef struct
{
    unsigned char x;
    unsigned char y;
    unsigned char z;
} vec3uint8_t;

vec3uint8_t vec3uint8(unsigned char x, unsigned char y, unsigned char z);
vec3uint8_t sum_vec3uint8(vec3uint8_t a, vec3uint8_t b);
void print_vec3uint8(vec3uint8_t a);
