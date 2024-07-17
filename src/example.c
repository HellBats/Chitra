#include"include/Chitra.c"
#define WIDTH 1900
#define HEIGHT 1000



static uint32_t pixels[HEIGHT*WIDTH];



void main()
{
    int x[] = {-100,800,200};
    int y[] = {-50,500,700};
    Chitra chitra = {.pixels=pixels,.width=WIDTH,.height=HEIGHT};
    ChitraFill(chitra,0xFFFFFFFF);
    ChitraFillRectangle(chitra,10,10,200,200,0x5A0000FF);
    ChitraFillRectangle(chitra,100,100,250,200,0x4A00FF00);
    // // ChitraDrawLine(chitra,500,-100,-100,600,0xFF00FF00);
    // // ChitraDrawTriangle(chitra,x,y,0xFF00FF00);
    ChitraFillTriangle(chitra,x,y,0xAA00FF00);
    ChitraFillCircle(chitra,x[0],y[0],10,0xAAFF0000);
    ChitraFillCircle(chitra,x[1],y[1],10,0xAAFF0000);
    ChitraFillCircle(chitra,x[2],y[2],10,0xAAFF0000);
    ChitraFillCircle(chitra,200,100,100,0xAAFF0000);
    ChitraSavePPM(chitra,"output.ppm");
}