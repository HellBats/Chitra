#ifndef TRIANGLES_DOT_H
#define TRIANGLES_DOT_H

#include"../Chitra.h"

typedef struct
{
    int x[3];
    int y[3];
}Triangle;


void ChitraDrawTriangle(Chitra chitra,Triangle triangle,uint32_t color);
char LieInsideTriangle(int x[],int y[],int x0,int y0);
int Min3(int a,int b,int c);
int Max(int a,int b,int c);
void ChitraFillTriangle(Chitra chitra,Triangle triangle,uint32_t color);
void ChitraAntiAiliasingFillTriangle(Chitra chitra,Triangle triangle,uint32_t color);
#endif