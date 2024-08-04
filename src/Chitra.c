#ifndef CHITRA_C
#define CHITRA_C
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include"include/Chitra.h"
#define return_defer(value) do {result=value; goto defer;} while (0)


Chitra NewChitra(uint32_t *pixels, size_t width,size_t height)
{
    Chitra Chitra_new = {.pixels = pixels,.width=width,.height=height,.stride=width};
    return Chitra_new;
}

void ChitraFill(Chitra chitra,uint32_t color)
{
    for(size_t i=0;i<chitra.height*chitra.width;i++) chitra.pixels[i] = color;
}

char ChitraSavePPM(Chitra chitra,const char* path)
{
    int result = 0;
    FILE *ptr = NULL;
    {
        ptr = fopen(path,"wb");
        if (ptr == NULL) return_defer(-1);
        fprintf(ptr,"P6\n%zu %zu 255 \n",chitra.width,chitra.height);
        if(ferror(ptr)) return_defer(-1);

        for(size_t i=0;i<chitra.height*chitra.width;i++)
        {
            uint32_t pixel = chitra.pixels[i];
            uint8_t bytes[3] = {(pixel>>8*0)&0xFF,(pixel>>8*1)&0xFF,(pixel>>8*2)&0xFF};
            fwrite(bytes,sizeof(bytes),1,ptr);
            if(ferror(ptr)) return_defer(-1);
        }
    }
defer:
    if(ptr) fclose(ptr);
    return 0;
}

int Min(int *a,int *b)
{
    if(*a<=*b) return *a;
    else return *b;
}


char NormalizedRectangle(Chitra chitra,int x,int y,int x_, int y_,int *x1,int *y1,int *x2,int *y2)
{
    int min_x = Min(&x,&x_);
    int min_y = Min(&y,&y_);
    int x_not_min = (min_x == x)?x_:x;
    int y_not_min = (min_y == y)?y_:y;
    // printf("%d %d %d %d\n",min_x,min_y,x_not_min,y_not_min);
    if(min_x>chitra.width || min_y>chitra.height || x_not_min<0 || y_not_min<0)
    {
        return 0;
    }
    if(min_x<0)
    {
        min_x = 0;
    }
    if(min_y<0)
    {
        min_y = 0;
    }
    if(x_not_min> (int) chitra.width)
    {
        x_not_min = chitra.width;
    }
    if(y_not_min> (int) chitra.height)
    {
        y_not_min = chitra.height;
    }
    *x1 = min_x;
    *x2 = x_not_min;
    *y1 = min_y;
    *y2 = y_not_min;
    return 1;
}

Chitra SubChitra(Chitra chitra,int x, int y, int width,int height)
{
    int x_,y_;
    if(NormalizedRectangle(chitra,x,y,x+width,y+height,&x,&y,&x_,&y_))
    {
        chitra.pixels = &chitra.pixels[y*chitra.stride+x];
        chitra.width = x_ - x + 1;
        chitra.height = y_ -y + 1;
        return chitra;
    }
    else return Chitra_NULL;
}

void UnpackRGBA(uint32_t c,uint8_t comp[COMP_COUNTS])
{
    for(int i=0;i<COMP_COUNTS;i++)
    {
        comp[i] = c & 0xFF;
        c >>= 8;
    }
}

uint32_t PackRGBA(uint8_t comp[COMP_COUNTS])
{
    uint32_t c = 0;
    for(int i=0;i<COMP_COUNTS;i++)
    {
        c |= comp[i] << 8*(i);
    }
    return c;
}

uint8_t MixComps(uint32_t c1,uint32_t c2,uint32_t t1,uint32_t t2)
{
    // c2 over c1
    uint32_t num = t2*c2+((255-t2)*t1*c1)/255;
    uint32_t den = t2 + ((255-t2)*t1)/255;
    return (uint8_t)(num/den);
}

uint32_t MixRGBA(uint32_t c1,uint32_t c2)
{
    uint8_t comp1[COMP_COUNTS], comp2[COMP_COUNTS];
    UnpackRGBA(c1,comp1);
    UnpackRGBA(c2,comp2);
    for(size_t i=0;i<COMP_COUNTS-1;i++) 
        comp1[i] = MixComps(comp1[i],comp2[i],comp1[COMP_ALPHA],comp2[COMP_ALPHA]);
    return PackRGBA(comp1);
}
#endif