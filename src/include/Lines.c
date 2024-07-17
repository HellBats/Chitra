
#include<stdint.h>
#include<stdio.h>
#include"Chitra.h"

void ChitraDrawLine(Chitra chitra,int x0,int y0,int x1,int y1,
uint32_t color)
{
    float mx,cx,my,cy;
    int dx = ((x1-x0)>>31) | 1;
    int dy = ((y1-y0)>>31) | 1;
    if(x1==x0)
    {
        for(;y0!=y1;y0+=dy)
        {
            if(y0>0 && y0<chitra.height)
            {
                chitra.pixels[y0*chitra.width+x0] = color;
            }
        }
    }
    if(y1==y0)
    {
        for(;x0!=x1;x0+=dx)
        {
            if(x0>0 && x0<chitra.width)
            {
                chitra.pixels[y0*chitra.width+x0] = color;
            }
        }
    }
    else
    {
        mx = ((float)(y1-y0))/((float)(x1-x0));
        my = ((float)(x1-x0))/((float)(y1-y0));
        cx = y1 - mx*x1;
        cy = x1 - my*y1;
        for(;x0!=x1;x0+=dx)
        {
            int y = (int)(mx*x0 + cx);
            // printf("%d ",x0);
            if(y>0 && x0>0)
            {
                chitra.pixels[y*chitra.width+x0] = color;
            }
        }
        for(;y0!=y1;y0+=dy)
        {
            int x = (int)(my*y0 + cy);
            if(x>0 && y0>0)
            {
                chitra.pixels[y0*chitra.width+x] = color;
            }
        }
    }
}