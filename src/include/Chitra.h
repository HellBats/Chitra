#ifndef CHITRA_H
#define CHITRA_H
#include<stdint.h>
#include<stdio.h>

#define Chitra_NULL (Chitra) {0}
typedef struct 
{
    uint32_t *pixels;
    size_t height;
    size_t width;
    size_t stride;
}Chitra;

typedef enum
{
    //0xAARRBBGG
    COMP_GREEN=0,
    COMP_BLUE,
    COMP_RED,
    COMP_ALPHA,
    COMP_COUNTS,
} comp_index;


Chitra NewChitra(uint32_t *pixels, size_t width,size_t height);
void ChitraFill(Chitra chitra,uint32_t color);
char ChitraSavePPM(Chitra chitra,const char* path);
int Min(int *a,int *b);
Chitra SubChitra(Chitra chitra,int x, int y, int width,int height);
char NormalizedRectangle(Chitra chitra,int x,int y,int x_, int y_,int *x1,int *x2,int *y1,int *y2);
void UnpackRGBA(uint32_t c,uint8_t comp[COMP_COUNTS]);
uint32_t MixRGBA(uint32_t c1,uint32_t c2);

#endif