#ifndef LINES_DOT_H
#define LINES_DOT_H

#include"include/Chitra.h"

typedef struct 
{
    int x0;
    int y0;
    int x1;
    int y1;
}Line;


void ChitraDrawLine(Chitra chitra,Line line,uint32_t color);
void ChitraAntiAiliasingDrawLine(Chitra chitra,Line line,uint32_t color);
#endif