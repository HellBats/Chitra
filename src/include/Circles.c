#include<stdint.h>
#include<stdio.h>
#include"Chitra.h"


void ChitraFillCircle(Chitra chitra,int cx,int cy,
size_t r,uint32_t color)
{
    int x,y,x_,y_;
    if(NormalizedRectangle(chitra,cx-r,cy-r,cx+r,cy+r,&x,&y,&x_,&y_))
    {
        for(;y<y_;y++)
        {
            for(int i=x;i<x_;i++)
            {
                if((cx-i)*(cx-i)+(cy-y)*(cy-y) <= r*r)
                {
                    chitra.pixels[y*chitra.width+i] = MixRGBA(chitra.pixels[y*chitra.width+i],color);
                }
            }
        }
    }
}