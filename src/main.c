#include <stdio.h>

#define major 0
#define minor 0
#define patch 1

int main(){
    printf("Welcome to DemaxNet v%d.%d.%d\n", major, minor, patch);

    for(;;); //infinite loop, press ctrl + C to stop the application

    return 0;
}