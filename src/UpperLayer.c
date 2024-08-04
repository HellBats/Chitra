#include"include/UpperLayer.h"
#define FPS 30


int increment = 0;
Matrix4x4 PROJECTION_MATRIX;

void Setup(Chitra chitra)
{
    PROJECTION_MATRIX = CalculateProjectionMatrix();
    // Circle circle;
    // circle.pos_x = 600;
    // circle.pos_y = 600;
    // circle.radius = 50;
    // ChitraAltFillCircle(chitra,circle,0xFFAAAAAA);
    ChitraSavePPM(chitra,"output.ppm");
}



void EventLoop(Chitra chitra,clock_t start)
{   
    increment = (30*(clock()-start)/(CLOCKS_PER_SEC)); 
    // printf("%d",increment);
    ChitraFill(chitra,0xFF000000);
    float sin_rot_y = SinDeg(CAMERAROTY+increment);
    float cos_rot_y = CosDeg(CAMERAROTY+increment);
    const int NUMBER = 64;
    float points_array[NUMBER][4]; //= {{-4,-4,8,1},
                                // {-4,4,8,1},
                                // {4,4,8,1},
                                // {4,-4,8,1},
                                // {-4,-4,0,1},
                                // {-4,4,0,1},
                                // {4,4,0,1},
                                // {4,-4,0,1}};
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
    // Triangle triangle1,triangle2;
    // Line line1,line2;
    // for(int i=0;i<3;i++)
    // {
    //     triangle1.x[i] = points[i].cords[0];
    //     triangle1.y[i] = points[i].cords[1];
    // }

    // triangle2.x[0] = points[0].cords[0];
    // triangle2.y[0] = points[0].cords[1];
    // triangle2.x[1] = points[2].cords[0];
    // triangle2.y[1] = points[2].cords[1];
    // triangle2.x[2] = points[3].cords[0];
    // triangle2.y[2] = points[3].cords[1];
    // line1.x0 = points[0].cords[0];
    // line1.y0 = points[0].cords[1];
    // line1.x1 = points[2].cords[0];
    // line1.y1 = points[2].cords[1];
    // line2.x0 = points[1].cords[0];
    // line2.y0 = points[1].cords[1];
    // line2.x1 = points[3].cords[0];
    // line2.y1 = points[3].cords[1];
    // ChitraAntiAiliasingFillTriangle(chitra,triangle1,0xFFFF0000);
    // ChitraAntiAiliasingFillTriangle(chitra,triangle2,0xFFFF0000);
    // // ChitraDrawLine(chitra,line1,0xFFFF0000);
    // // ChitraDrawLine(chitra,line2,0xFFFF0000);
    // ChitraAntiAiliasingDrawLine(chitra,line1,0xFFFF0000);
    // ChitraAntiAiliasingDrawLine(chitra,line1,0xFFFF0000);
}