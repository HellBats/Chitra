#include<stdint.h>
#include<stdio.h>
#include"Chitra.h"

void ChitraFillRectangle(Chitra chitra,int x0,int y0,
size_t width,size_t height,uint32_t color)
{
    int x,y,x_,y_;
    if(NormalizedRectangle(chitra,x0,y0,x0+width,y0+height,&x,&y,&x_,&y_))
    {
        // printf("%d %d %d %d\n",x,y,x_,y_);
        for(;y<y_;y++)
        {
            for(int i=x;i<x_;i++)
            {  
                chitra.pixels[y*chitra.width+i] = MixRGBA(chitra.pixels[y*chitra.width+i],color);
            }
        }
    }
}