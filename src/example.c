#include"include/Chitra.c"
#define WIDTH 1900
#define HEIGHT 1000



static uint32_t pixels[HEIGHT*WIDTH];



void main()
{
    ChitraFill(pixels,WIDTH,HEIGHT,0xFFFFFFFF);
    ChitraFillRectangle(pixels,WIDTH,HEIGHT,10,10,200,200,0xFF0000FF);
    ChitraFillCircle(pixels,WIDTH,HEIGHT,WIDTH/2,HEIGHT/2,100,0xFFFF0000);
    ChitraDrawLine(pixels,WIDTH,HEIGHT,-100,100,500,100,0xFF00FF00);
    ChitraSavePPM(pixels,WIDTH,HEIGHT,"output.ppm");
}