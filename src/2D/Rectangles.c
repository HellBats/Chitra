#ifndef RECTANGLES_C
#define RECTANGLES_C
#include"include/2D/Rectangles.h"

void ChitraFillRectangle(Chitra chitra,Rectangle rectangle,uint32_t color)
{
    int x,y,x_,y_;
    if(NormalizedRectangle(chitra,rectangle.x0,rectangle.y0,rectangle.x0+rectangle.width,
        rectangle.y0+rectangle.height,&x,&y,&x_,&y_))
    {
        // printf("%d %d %d %d\n",x,y,x_,y_);
        for(;y<y_;y++)
            for(int i=x;i<x_;i++) 
                chitra.pixels[y*chitra.stride+i] = MixRGBA(chitra.pixels[y*chitra.stride+i],color);
    }
}

#endif