#ifndef CIRCLES_C
#define CIRCLES_C
#include<stdint.h>
#include<stdio.h>
#include"include/2D/Circles.h"

void ChitraFillCircle(Chitra chitra,Circle circle,uint32_t color)
{
    int x,y,x_,y_;
    if(NormalizedRectangle(chitra,(circle.pos_x-circle.radius),(circle.pos_y-circle.radius),
        (circle.pos_x+circle.radius),(circle.pos_y+circle.radius),&x,&y,&x_,&y_))
        for(int j=y;j<y_;j+=1)
            for(int i=x;i<x_;i+=1)
                if((circle.pos_x-i)*(circle.pos_x-i)+(circle.pos_y-j)*(circle.pos_y-j) 
                    <= circle.radius*circle.radius) chitra.pixels[j*chitra.stride+i] = color;
}

void ChitraAltFillCircle(Chitra chitra,Circle circle,uint32_t color)
{
    int x,y,x_,y_;
    if(NormalizedRectangle(chitra,(circle.pos_x-circle.radius),(circle.pos_y-circle.radius),
        (circle.pos_x+circle.radius),(circle.pos_y+circle.radius),&x,&y,&x_,&y_))
        //Pixels are subdivided into 4 subpixels
        for(int j=2*y;j<2*y_;j+=2)
            for(int i=2*x;i<2*x_;i+=2)
            {
                size_t popularity = 0;
                for(int k=0;k<2;k++)
                    for(int l=0;l<2;l++)
                       if((2*circle.pos_x-i+k)*(2*circle.pos_x-i+k)+(2*circle.pos_y-j+l)*(2*circle.pos_y-j+l) <=
                            4*circle.radius*circle.radius) 
                                popularity++;
  
                uint32_t color_trans = (color >>24);
                uint32_t transparency = (popularity==4?(color_trans << 24):((color_trans/4*popularity) 
                << 24)) | 0x00000000;
                uint32_t new_color = MixRGBA(chitra.pixels[j/2*chitra.stride+i/2],((color << 8) >> 8) |
                transparency);
                chitra.pixels[j/2*chitra.stride+i/2] = new_color;
            }
}
#endif