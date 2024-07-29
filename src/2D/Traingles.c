#ifndef TRIANGLES_C
#define TRIANGLES_C
#include<stdint.h>
#include<stdio.h>
#include"include/2D/Triangles.h"
void ChitraDrawTriangle(Chitra chitra,Triangle triangle,uint32_t color)
{
    int x_from,x_to,y_from,y_to;
    float mx,cx,my,cy;
    for(int i=0;i<3;i++)
    {
        x_from = triangle.x[i];
        y_from = triangle.y[i];
        x_to = triangle.x[(i+1)%3];
        y_to = triangle.y[(i+1)%3];
        int dx = ((x_to-x_from)>>31) | 1;
        int dy = ((y_to-y_from)>>31) | 1;
        if(x_to==x_from)
        {
            for(;y_from!=y_to;y_from+=dy)
            {
                if(y_from>0 && y_from<chitra.height)
                {
                    chitra.pixels[y_from*chitra.stride+x_from] = color;
                }
            }
        }
        if(y_to==y_from)
        {
            for(;x_from!=x_to;x_from+=dx)
            {
                if(x_from>0 && x_from<chitra.width)
                {
                    chitra.pixels[y_from*chitra.stride+x_from] = color;
                }
            }
        }
        else
        {
            mx = ((float)(y_to-y_from))/((float)(x_to-x_from));
            my = ((float)(x_to-x_from))/((float)(y_to-y_from));
            cx = y_to - mx*x_to;
            cy = x_to - my*y_to;
            for(;x_from!=x_to;x_from+=dx)
            {
                int y0 = ((int)(mx*x_from + cx));
                if(y0>0 && x_from>0 && y0<chitra.height && x_from <chitra.width)
                {
                    chitra.pixels[y0*chitra.stride+x_from] = color;
                }
            }
            for(;y_from!=y_to;y_from+=dy)
            {
                int x0 = ((int)(my*y_from + cy));
                if(x0>0 && y_from>0 && x0<chitra.width && y_from<chitra.height)
                {
                    chitra.pixels[y_from*chitra.stride+x0] = color;
                }
            }
        }
    }
}


char LieInsideTriangle(int x[],int y[],int x0,int y0)
{
    for(int i=0;i<3;i++)
    {
        int x_from = x[i];
        int y_from = y[i];
        int x_to = x[(i+1)%3];
        int y_to = y[(i+1)%3];
        int x3 = x[(i+2)%3];
        int y3 = y[(i+2)%3];
        float m,c;
        int p1,p2;
        if(!(x_to-x_from))
        {
            p1 = (int) (x0-x_to);
            p2 = (int) (x3-x_to);
        }
        else
        {
            m = ((float)(y_to-y_from))/((float)(x_to-x_from));
            c = y_to - m*x_to;
            p1 = (int) (-m*x0+y0-c);
            p2 = (int) (-m*x3+y3-c);
        }
        // printf("%f %f ",m,c);
        if(p1==0 && p2==0) continue;
        else if(p2==0) return 0;
        else if(!(p1*p2>0))
        {
            return 0; 
        }
    }
    return 1;
}


int Min3(int a,int b,int c)
{
    int min = Min(&a,&b);
    return Min(&min,&c);
}
    


int Max(int a,int b,int c)
{
    if(a>=b)
    {
        if(a>=c) return a;
        else return c;
    }
    else
    {
        if(b>=c) return b;
        else return c;
    }
}

void ChitraFillTriangle(Chitra chitra,Triangle triangle,uint32_t color)
{
    int x_min = Min3(triangle.x[0],triangle.x[1],triangle.x[2]);
    int y_min = Min3(triangle.y[0],triangle.y[1],triangle.y[2]);
    int x_max = Max(triangle.x[0],triangle.x[1],triangle.x[2]);
    int y_max = Max(triangle.y[0],triangle.y[1],triangle.y[2]);
    if(NormalizedRectangle(chitra,x_min,y_min,x_max,y_max,&x_min,&y_min,&x_max,&y_max))
    {
        for(;y_min<=y_max;y_min++)
        {
            for(int i = x_min;i<=x_max;i++)
            {
                if(LieInsideTriangle(triangle.x,triangle.y,i,y_min)) chitra.pixels[y_min*chitra.stride+i] 
                    =MixRGBA(chitra.pixels[y_min*chitra.width+i],color);
            }
        }
    }
}

void ChitraAntiAiliasingFillTriangle(Chitra chitra,Triangle triangle,uint32_t color)
{
    int x_min = Min3(triangle.x[0],triangle.x[1],triangle.x[2]);
    int y_min = Min3(triangle.y[0],triangle.y[1],triangle.y[2]);
    int x_max = Max(triangle.x[0],triangle.x[1],triangle.x[2]);
    int y_max = Max(triangle.y[0],triangle.y[1],triangle.y[2]);
    if(NormalizedRectangle(chitra,x_min,y_min,x_max,y_max,&x_min,&y_min,&x_max,&y_max))
    {
        for(;y_min<=y_max;y_min++)
        {
            for(int i = x_min;i<=x_max;i++)
            {
                if(LieInsideTriangle(triangle.x,triangle.y,i,y_min)) chitra.pixels[y_min*chitra.stride+i]
                    =MixRGBA(chitra.pixels[y_min*chitra.stride+i],color);
            }
        }
        for(int i=x_min;i<=x_max;i+=1)
        {
            for(int j=y_min;j<=y_max;j+=1)
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
#endif
