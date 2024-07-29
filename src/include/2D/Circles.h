#ifndef CIRCLES_DOT_H
#define CIRCLES_DOT_H


#include"include/Chitra.h"

typedef struct
{
    int pos_x;
    int pos_y;
    size_t radius;
}Circle;


void ChitraFillCircle(Chitra chitra,Circle circle,uint32_t color);
void ChitraAltFillCircle(Chitra chitra,Circle circle,uint32_t color);

#endif