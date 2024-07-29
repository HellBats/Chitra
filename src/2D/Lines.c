#ifndef LINES_C
#define LINES_C
#include<stdint.h>
#include<stdio.h>
#include"include/2D/Lines.h"


void ChitraDrawLine(Chitra chitra,Line line,uint32_t color)
{
    float mx,cx,my,cy;
    int dx = ((line.x1-line.x0)>>31) | 1;
    int dy = ((line.y1-line.y0)>>31) | 1;
    if(line.x1==line.x0)
    {
        for(;line.y0!=line.y1;line.y0+=dy)
        {
            if(line.y0>0 && line.y0<chitra.height)
            {
                chitra.pixels[line.y0*chitra.stride+line.x0] = color;
            }
        }
    }
    if(line.y1==line.y0)
    {
        for(;line.x0!=line.x1;line.x0+=dx)
        {
            if(line.x0>0 && line.x0<chitra.width)
            {
                chitra.pixels[line.y0*chitra.stride+line.x0] = color;
            }
        }
    }
    else
    {
        mx = ((float)(line.y1-line.y0))/((float)(line.x1-line.x0));
        my = ((float)(line.x1-line.x0))/((float)(line.y1-line.y0));
        cx = line.y1 - mx*line.x1;
        cy = line.x1 - my*line.y1;
        for(;line.x0!=line.x1;line.x0+=dx)
        {
            int y = (int)(mx*line.x0 + cx);
            // printf("%d ",line.x0);
            if(y>0 && line.x0>0)
            {
                chitra.pixels[y*chitra.stride+line.x0] = color;
            }
        }
        for(;line.y0!=line.y1;line.y0+=dy)
        {
            int x = (int)(my*line.y0 + cy);
            if(x>0 && line.y0>0)
            {
                chitra.pixels[line.y0*chitra.stride+x] = color;
            }
        }
    }
}

void ChitraAntiAiliasingDrawLine(Chitra chitra,Line line,uint32_t color)
{
    float mx,cx,my,cy;
    int dx = ((line.x1-line.x0)>>31) | 1;
    int dy = ((line.y1-line.y0)>>31) | 1;
    if(line.x1==line.x0)
    {
        for(;line.y0!=line.y1;line.y0+=dy)
        {
            if(line.y0>0 && line.y0<chitra.height)
            {
                chitra.pixels[line.y0*chitra.width+line.x0] = color;
            }
        }
    }
    if(line.y1==line.y0)
    {
        for(;line.x0!=line.x1;line.x0+=dx)
        {
            if(line.x0>0 && line.x0<chitra.width)
            {
                chitra.pixels[line.y0*chitra.width+line.x0] = color;
            }
        }
    }
    else
    {
        mx = ((float)(line.y1-line.y0))/((float)(line.x1-line.x0));
        my = ((float)(line.x1-line.x0))/((float)(line.y1-line.y0));
        cx = line.y1 - mx*line.x1;
        cy = line.x1 - my*line.y1;
        for(int i=line.x0;i!=line.x1;i+=dx)
        {
            int y = (int)(mx*i + cx);
            // printf("%d ",line.x0);
            if(y>0 && i>0)
            {
                chitra.pixels[y*chitra.stride+i] = color;
            }
        }
        for(int j=line.y0;j!=line.y1;j+=dy)
        {
            int x = (int)(my*j + cy);
            if(x>0 && j>0)
            {
                chitra.pixels[j*chitra.stride+x] = color;
            }
        } 
        if(NormalizedRectangle(chitra,line.x0,line.y0,line.x1,line.y1,&line.x0,&line.y0,&line.x1,&line.y1))
        {
            for(int i=line.x0;i!=line.x1;i+=1)
            {
                for(int j=line.y0;j!=line.y1;j+=1)
                {
                    int x2 =i-1,y2=j-1,x3=i+1,y3=j+1;
                    if(NormalizedRectangle(chitra,x2,y2,x3,y3,&x2,&y2,&x3,&y3))
                    {
                        size_t popularity = 0;
                        uint32_t color_trans = 0x00000000;
                        uint32_t back_color = chitra.pixels[y2*chitra.stride+x2];
                        for(int k=x2;k<=x3;k++)
                        {
                            for(int l=y2;l<=y3;l++)
                            {
                                if(chitra.pixels[l*chitra.stride+k]==color) popularity++;
                                else back_color = chitra.pixels[l*chitra.stride+k];
                            }   
                        }
                        if(popularity)
                        {
                            uint32_t transparency = 102 + 17*popularity;
                            color_trans = (transparency << 24);
                        }
                        uint32_t new_color = MixRGBA(back_color,((color << 8) >> 8) | color_trans);
                        chitra.pixels[j*chitra.stride+i] = new_color;
                    }            
                }
            }
        }
    }
}

#endif