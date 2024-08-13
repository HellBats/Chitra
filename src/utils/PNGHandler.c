#include"include/PNGHandler.h"
#define STB_IMAGE_RESIZE_RECOMMENDED
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"  
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image_write.h"


Chitra ReadPNG(char *path,int *height,int *width,int *channels)
{
    unsigned char *img = stbi_load(path,width,height,channels,3);
    if(img==NULL) return Chitra_NULL;
    Chitra chitra = {.width=*width,.height=*height,.stride=*width};
    uint32_t *pixels = (uint32_t*)malloc(sizeof(uint32_t)*chitra.width*chitra.height);
    chitra.pixels = pixels;
    ChitraFill(chitra,0xFF000000);
    uint8_t comp[4];
    for (size_t i = 0; i < chitra.height; i++)
    {
        for (size_t j = 0; j < chitra.width; j++)
        {
            comp[0] = img[i*(*channels)*chitra.stride+j*(*channels)+1];
            comp[1] = img[i*(*channels)*chitra.stride+j*(*channels)+2];
            comp[2] = img[i*(*channels)*chitra.stride+j*(*channels)];
            comp[3] = 255;
            chitra.pixels[i*chitra.stride+j] = MixRGBA(chitra.pixels[i*chitra.stride+j],PackRGBA(comp));
        }
        
    }
    return chitra;
}

Chitra WritePNG(char path[],Chitra chitra)
{
    int channels = 4;
    unsigned char *img = (char*)malloc(sizeof(char)*chitra.height*chitra.width*channels);
    uint8_t comp[channels];
    for (size_t i = 0; i < chitra.height; i++)
    {
        for (size_t j = 0; j < chitra.width; j++)
        {
            UnpackRGBA(chitra.pixels[i*chitra.stride+j],comp);
            img[i*(channels)*chitra.stride+j*(channels)+3] = chitra.background_opacity; //Alpha
            img[i*(channels)*chitra.stride+j*(channels)+2] = comp[2];//Blue
            img[i*(channels)*chitra.stride+j*(channels)+1] = comp[3];//Green
            img[i*(channels)*chitra.stride+j*(channels)] = comp[1];//Red
        }
    }
    stbi_write_png(path,chitra.width,chitra.height,channels,img,chitra.stride*channels);
}