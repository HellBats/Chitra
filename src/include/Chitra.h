#ifndef CHITRA_H
#define CHITRA_H

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>


#define ANTIAIALISING 1
#define return_defer(value) do {result=value; goto defer;} while (0)
#define Chitra_NULL (Chitra) {0}
typedef struct 
{
    uint32_t *pixels;
    size_t height;
    size_t width;
    size_t stride;
    unsigned char background_opacity;
}Chitra;

typedef enum
{
    //0xAARRGGBB
    COMP_BLUE =0,
    COMP_GREEN,
    COMP_RED,
    COMP_ALPHA,
    COMP_COUNTS,
} comp_index;


#include"PPMReader.h"
#include"PNGHandler.h"
#include"3D/Math.h"
#include"2D/Triangles.h"
#include"2D/Circles.h"
#include"2D/Lines.h"
#include"2D/Rectangles.h"
#include"3D/3DTriangle.h"


Chitra NewChitra(uint32_t *pixels, size_t width,size_t height);
void ChitraFill(Chitra chitra,uint32_t color);
char ChitraSavePPM(Chitra chitra,const char* path);
int Min(int *a,int *b);
Chitra SubChitra(Chitra chitra,int x, int y, int width,int height);
char NormalizedRectangle(Chitra chitra,int x,int y,int x_, int y_,int *x1,int *x2,int *y1,int *y2);
void UnpackRGBA(uint32_t c,uint8_t comp[COMP_COUNTS]);
uint32_t PackRGBA(uint8_t comp[COMP_COUNTS]);
uint8_t MixComps(uint32_t c1,uint32_t c2,uint32_t t1,uint32_t t2);
uint32_t MixRGBA(uint32_t c1,uint32_t c2);
Chitra ChitraCopy(Chitra chitra);
#endif