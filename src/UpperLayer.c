#include"include/UpperLayer.h"
#define FPS 30


int increment = 0;
Matrix4x4 PROJECTION_MATRIX;

void Setup(Chitra chitra)
{
    PROJECTION_MATRIX = CalculateProjectionMatrix();
    Circle circle;
    Line line;
    line.x0 = 0;
    line.x1 = 800;
    line.y0 = 0;
    line.y1 = 800;
    circle.pos_x = 600;
    circle.pos_y = 600;
    circle.radius = 20;
    ChitraAltFillCircle(chitra,circle,0xFF0011CC);
    // uint32_t color = 0xFF0011CC;
    // uint32_t transparency = 80;
    // transparency = (transparency<<24);
    // color = (color & 0x00FFFFFF) | transparency;
    // color = MixRGBA(0xFFFFFFFF,color);
    // ChitraAntiAiliasingDrawLine(chitra,line,color);
    WritePNG("new_image.png",chitra);
    // int width,height,channels;
    // char path[] = "image.png"; 
    // Chitra chitraq = ReadPNG(path,&width,&height,&channels);
    // ChitraSavePPM(chitraq,"image.ppm");
    ChitraSavePPM(chitra,"output.ppm");
}




// void EventLoop(Chitra chitra,clock_t start)
// {
//     ChitraFill(chitra,0xFFFFFFFF);
//     increment = (180*(clock()-start)/(CLOCKS_PER_SEC)); 
//     Circle circle = {.pos_x=100+increment,.pos_y=100,.radius=20};
//     ChitraAltFillCircle(chitra,circle,0xFFFF0000);
// }

void EventLoop(Chitra chitra,clock_t start)
{   
    increment = (30*(clock()-start)/(CLOCKS_PER_SEC)); 
    // printf("%d",increment);
    ChitraFill(chitra,0xFF000000);
    float sin_rot_y = SinDeg(CAMERAROTY+increment);
    float cos_rot_y = CosDeg(CAMERAROTY+increment);
    const int NUMBER = 64;
    float points_array[NUMBER][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            for(int k=0;k<4;k++)
            {
                points_array[i+4*j+16*k][0] = 4*i - 8;
                points_array[i+4*j+16*k][1] = 4*j - 8;
                points_array[i+4*j+16*k][2] = 4*k - 8;
                points_array[i+4*j+16*k][3] = 1; 
            }

    float Rotate_y[] = {cos_rot_y,0,sin_rot_y,0,
                        0,1,0,0,
                        -sin_rot_y,0,cos_rot_y,0,
                        0,0,0,1};
    Matrix4x4 Roty;
    FillMatrix(&Roty,Rotate_y);
    Vec4 points[NUMBER];
    Circle circles[NUMBER];
    for(int i=0;i<NUMBER;i++)
    {
        FillVec4(&points[i],points_array[i]);
        points[i] = MatrixMultiplication4D_Vec4D(Roty,points[i]);
        points[i] = ProjectPoint(chitra,PROJECTION_MATRIX,points[i]);
        // PrintVec4(points[i]);
        // PrintVec4(points[i]);
        circles[i].pos_x = points[i].cords[0];
        circles[i].pos_y = points[i].cords[1];
        circles[i].radius = 5;
        ChitraAltFillCircle(chitra,circles[i],0xFF000000 | 255-3*i | -i*i/32 + 2*i + 128 <<8 | 2*i <1<16);
    }
}