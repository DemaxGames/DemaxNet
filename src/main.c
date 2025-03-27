#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image/stb_image_resize2.h>

#include <vec.h>

#define major 0
#define minor 0
#define patch 1
#define resolutionRef 144

void ResizeToReferenceX(const char* pathFrom, const char* pathTo){
    int width, height, channels;
    vec3uint8_t* image = (void*)stbi_load(pathFrom, &width, &height, &channels, 0);
    if(image == NULL){
        printf("ERROR: File hasn't be found\n");
        return;
    }
    vec3uint8_t* resizedImage = malloc(sizeof(vec3uint8_t) * resolutionRef * height);
    if(resizedImage == NULL){
        printf("ERROR: Allocation failed\n");
        return;
    }
    
    float resRateX = resolutionRef / (float)width;

    printf("ResRate: %f\n", resRateX);

    int resX = 0;

    for(int y = 0; y < height; y++){
        resX = 0;
        vec3uint8_t resColor = {0, 0, 0};
        float counter = 0.0f;
        for(int x = 0; x < width; x++){
            if(counter + resRateX <= 1.0f){
                vec3uint8_t a = image[y * width + x];
                a.x = (uint8_t)((float)a.x * resRateX);
                a.y = (uint8_t)((float)a.y * resRateX);
                a.z = (uint8_t)((float)a.z * resRateX);
                resColor = sum_vec3uint8(resColor, a);
            }
            else{
                vec3uint8_t a = image[y * width + x];
                a.x = (uint8_t)((float)a.x * (1.0f - counter));
                a.y = (uint8_t)((float)a.y * (1.0f - counter));
                a.z = (uint8_t)((float)a.z * (1.0f - counter));
                resColor = sum_vec3uint8(resColor, a);
            }
            counter += resRateX;
            if(counter >= 1.0f){
                counter -= 1.0f;
                resizedImage[y * resolutionRef + resX] = resColor;
                resX++;
                resColor = vec3uint8(0, 0, 0);
                if(counter > 0){
                    vec3uint8_t a = image[y * width + x];
                    a.x = (uint8_t)((float)a.x * counter);
                    a.y = (uint8_t)((float)a.y * counter);
                    a.z = (uint8_t)((float)a.z * counter);
                    resColor = sum_vec3uint8(resColor, a);
                }
            }
        }
    }
    printf("Writing changes to %s\n", pathTo);

    stbi_write_jpg(pathTo, resolutionRef, height, channels, (void*)resizedImage, 100);
    free(image);
    free(resizedImage);
}

void ResizeToReferenceY(const char* pathFrom, const char* pathTo){
    int width, height, channels;
    vec3uint8_t* image = (void*)stbi_load(pathFrom, &width, &height, &channels, 0);
    if(image == NULL){
        printf("ERROR: File hasn't be found\n");
        return;
    }
    vec3uint8_t* resizedImage = malloc(sizeof(vec3uint8_t) * width * resolutionRef);
    if(resizedImage == NULL){
        printf("ERROR: Allocation failed\n");
        return;
    }
    
    float resRateY = resolutionRef / (float)height;

    printf("ResRate: %f\n", resRateY);

    int resY = 0;

    for(int x = 0; x < width; x++){
        resY = 0;
        vec3uint8_t resColor = {0, 0, 0};
        float counter = 0.0f;
        for(int y = 0; y < height; y++){
            if(counter + resRateY <= 1.0f){
                vec3uint8_t a = image[y * width + x];
                a.x = (uint8_t)((float)a.x * resRateY);
                a.y = (uint8_t)((float)a.y * resRateY);
                a.z = (uint8_t)((float)a.z * resRateY);
                resColor = sum_vec3uint8(resColor, a);
            }
            else{
                vec3uint8_t a = image[y * width + x];
                a.x = (uint8_t)((float)a.x * (1.0f - counter));
                a.y = (uint8_t)((float)a.y * (1.0f - counter));
                a.z = (uint8_t)((float)a.z * (1.0f - counter));
                resColor = sum_vec3uint8(resColor, a);
            }
            counter += resRateY;
            if(counter >= 1.0f){
                counter -= 1.0f;
                resizedImage[resY * width + x] = resColor;
                resY++;
                resColor = vec3uint8(0, 0, 0);
                if(counter > 0){
                    vec3uint8_t a = image[y * width + x];
                    a.x = (uint8_t)((float)a.x * counter);
                    a.y = (uint8_t)((float)a.y * counter);
                    a.z = (uint8_t)((float)a.z * counter);
                    resColor = sum_vec3uint8(resColor, a);
                }
            }
        }
    }
    printf("Writing changes to %s h:%d w:%d\n", pathTo, resolutionRef, width);

    stbi_write_jpg(pathTo, width, resolutionRef, channels, (void*)resizedImage, 100);
    free(image);
    free(resizedImage);
}

void ResizeToReference(const char* pathFrom, const char* pathTo){
    ResizeToReferenceX(pathFrom, pathTo);
    ResizeToReferenceY(pathTo, pathTo);
}

int main(int argc, char** argv){
    printf("Welcome to DemaxNet v%d.%d.%d\n", major, minor, patch);

    ResizeToReference(argv[1], argv[1]);
    return 0;
}