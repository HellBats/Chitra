#include"include/PPMReader.h"


int ReadPPM(Chitra chitra,const char* path)
{
    int result = 0;
    FILE *ptr = NULL;
    {
        ptr = fopen(path,"rb");
        if (ptr == NULL) return_defer(-1);
        char buffer[33];
        fread(buffer,sizeof(char),32,ptr);
        if(ferror(ptr)) return_defer(-1);
        int i=3,j=1,k=0;
        size_t dimensions[2];
        while(i<13)
        {
            // printf("%d\n",buffer[i]);
            if(buffer[i] == ' ')
            {
                CalculateImageDimensions(buffer,&dimensions[k],i,j);
                // printf("%zu\n",dimensions[k]);
                k++;
                j=0;
            }
            i++;
            j++;
        }
        i+=5;
        char *pixels = (char*)malloc(sizeof(char)*4*dimensions[0]*dimensions[1]+19);
        fread(pixels,sizeof(char),dimensions[0]*dimensions[1]*4+19,ptr);
        if(ferror(ptr)) return_defer(-1);
        uint8_t comp[4];
        for(;i<dimensions[0]*dimensions[1]*4+19 && pixels[i]!=0;i+=4)
        {
            // printf("%c",pixels[i]);
            comp[0] = 255;
            comp[1] = pixels[i];
            comp[2] = pixels[i+1];
            comp[3] = pixels[i+2];
            chitra.pixels[(i-18)/4] = PackRGBA(comp);
        }
    }
defer:
    if(ptr) fclose(ptr);
    return 0;
}


void CalculateImageDimensions(char buffer[],size_t *dimension,int pointer,int length)
{
    size_t number=0;
    for(int i=1;i<length;i++)
    {
        size_t digit= (int)(buffer[pointer-i] - 48);
        for(int j=1;j<i;j++) digit*=10;
        number += digit;
    }
    *dimension = number;
}