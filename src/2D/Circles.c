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
    int t = (chitra.width<chitra.height?chitra.width:chitra.height)/(circle.radius*10);
    t = t<2?2:t;
    if(NormalizedRectangle(chitra,(circle.pos_x-circle.radius),(circle.pos_y-circle.radius),
        (circle.pos_x+circle.radius),(circle.pos_y+circle.radius),&x,&y,&x_,&y_))
        //Pixels are subdivided into t*t subpixels
        for(int j=t*y;j<t*y_+t;j+=t)
            for(int i=t*x;i<t*x_+t;i+=t)
            {
                size_t popularity = 0;
                for(int k=0;k<t;k++)
                    for(int l=0;l<t;l++)
                       if((t*circle.pos_x-i+k)*(t*circle.pos_x-i+k)+(t*circle.pos_y-j+l)*(t*circle.pos_y-j+l) <=
                            t*t*circle.radius*circle.radius) 
                                popularity++;
  
                uint32_t color_trans = (color >>24);
                uint32_t transparency = (popularity==t*t?(color_trans << 24):((color_trans/(t*t)*popularity) 
                << 24)) | 0x00000000;
                uint32_t new_color = MixRGBA(chitra.pixels[j/t*chitra.stride+i/t],((color << 8) >> 8) |
                transparency);
                chitra.pixels[j/t*chitra.stride+i/t] = new_color;
            }
}
#endif