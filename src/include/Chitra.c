#ifndef CHITRA_C
#define CHITRA_C
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

#define return_defer(value) do {result=value; goto defer;} while (0)





void ChitraFill(uint32_t *pixels,size_t width,size_t height,uint32_t color)
{
    for(size_t i=0;i<height*width;i++)
    {
        pixels[i] = color;
    }
}

void ChitraFillRectangle(uint32_t *pixels,size_t pixels_width,size_t pixels_height,int x0,int y0,
size_t width,size_t height,uint32_t color)
{
    size_t x,y;
    x = x0<0?0:x0;
    y = y0<0?0:y0;
    width = x0+width;
    height = y0+height;
    for(;y<height && y<pixels_height;y++)
    {
        for(;x<width && x<pixels_width;x++)
        {  
            pixels[y*pixels_width+x] = color;
        }
        x = x0<0?0:x0;
    }
}

void ChitraFillCircle(uint32_t *pixels,size_t pixels_width,size_t pixels_height,int cx,int cy,
size_t r,uint32_t color)
{
    size_t x,y;
    x = (cx-r)<0?0:(cx-r);
    y = (cy-r)<0?0:(cy-r);
    int width = cx+r;
    int height = cy+r;
    for(;y<height && y<pixels_height;y++)
    {
        for(;x<width && x<pixels_width;x++)
        {
            if((cx-x)*(cx-x)+(cy-y)*(cy-y) <= r*r)
            {
                pixels[y*pixels_width+x] = color;
            }
        }
        x = (cx-r)<0?0:(cx-r);
    }
}


void ChitraDrawLine(uint32_t *pixels,size_t pixels_width,size_t pixels_height,int x0,int y0,int x1,int y1,
uint32_t color)
{
    float mx,cx,my,cy;
    int dx = (((x1-x0)>>31)<<31) | 1;
    int dy = (((y1-y0)>>31)<<31) | 1;
    if(x1==x0)
    {
        for(;y0!=y1;y0+=dy)
        {
            if(y0>0)
            {
                pixels[y0*pixels_width+x0] = color;
            }
        }
        return;
    }
    if(y1==y0)
    {
        for(;x0!=x1;x0+=dx)
        {
            if(x0>0)
            {
                pixels[y0*pixels_width+x0] = color;
            }
        }
        return;
    }
    mx = ((float)(y1-y0))/((float)(x1-x0));
    my = ((float)(x1-x0))/((float)(y1-y0));
    cx = y1 - mx*x1;
    cy = x1 - my*y1;
    for(;x0!=x1;x0+=dx)
    {
        if((mx*x0 + cx)>0 && x0>0)
        {
            pixels[((int)(mx*x0 + cx))*pixels_width+x0] = color;
        }
    }
    for(;y0!=y1;y0+=dy)
    {
        if((my*y0 + cy)>0 && y0>0)
        {
            pixels[y0*pixels_width+((int)(my*y0 + cy))] = color;
        }
    }
}

int ChitraSavePPM(uint32_t *pixels,size_t width,size_t height,const char* path)
{
    int result = 0;
    FILE *ptr = NULL;
    {
        ptr = fopen(path,"wb");
        if (ptr == NULL) return_defer(-1);
        fprintf(ptr,"P6\n%zu %zu 255 \n",width,height);
        if(ferror(ptr)) return_defer(-1);

        for(size_t i=0;i<height*width;i++)
        {
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = {(pixel>>8*0)&0xFF,(pixel>>8*1)&0xFF,(pixel>>8*2)&0xFF};
            fwrite(bytes,sizeof(bytes),1,ptr);
            if(ferror(ptr)) return_defer(-1);
        }
    }
defer:
    if(ptr) fclose(ptr);
    return 0;
}

#endif