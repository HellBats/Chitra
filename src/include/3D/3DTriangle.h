#ifndef TRIANGLE_DOT_H
#define TRIANGLE_DOT_H

#include"include/3D/Math.h"

typedef struct
{
    float p1[4];
    float p2[3];
    float p3[3];
}Triangle3D;

void ChitraDraw3DTriangle(Chitra chitra,Triangle3D triangle,uint32_t color);

#endif