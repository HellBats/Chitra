#ifndef RECTANGLES_DOT_H
#define RECTANGLES_DOT_H

#include"include/Chitra.h"

typedef struct 
{
    int x0;
    int y0;
    size_t width;
    size_t height;
}Rectangle;




void ChitraFillRectangle(Chitra chitra,Rectangle rectangle,uint32_t color);


#endif