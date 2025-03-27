#include <vec.h>

vec3uint8_t vec3uint8(unsigned char x, unsigned char y, unsigned char z){
    return (vec3uint8_t){x, y, z};
}

vec3uint8_t sum_vec3uint8(vec3uint8_t a, vec3uint8_t b){
    return (vec3uint8_t){a.x + b.x, a.y + b.y, a.z + b.z};
}

void print_vec3uint8(vec3uint8_t a){
    printf("x:%d y:%d z:%d ", a.x, a.y, a.z);
}