#include"include/UpperLayer.h"
#define FPS 30


int increment = 0;
Matrix4x4 PROJECTION_MATRIX;

void Setup(Chitra chitra)
{
    // printf("%f %f",SinDeg(225),CosDeg(225));
    // ChitraDraw3DTriangle(chitra,x,y,z,0xFFAABBCC);
    // float point1[4] = {4,4,5,1};
    // float point2[4] = {14,7,5,1};
    // float point3[4] = {6,11,5,1};
    // Vec4 points[3];
    // Triangle triangle;
    PROJECTION_MATRIX = CalculateProjectionMatrix();
    // float sin_rot_y = SinDeg(CAMERAROTY+increment);
    //     float cos_rot_y = CosDeg(CAMERAROTY+increment);
    //     float points_array[4][4] = {{-4,-4,5,1},
    //                                 {-4,8,5,1},
    //                                 {10,8,5,1},
    //                                 {10,-4,5,1}};
    //     float Rotate_y[] = {cos_rot_y,0,sin_rot_y,0,
    //                         0,1,0,0,
    //                         -sin_rot_y,0,cos_rot_y,0,
    //                         0,0,0,1};
    //     Matrix4x4 Roty;
    //     FillMatrix(&Roty,Rotate_y);
    //     Vec4 points[4];
    //     Circle circles[4];
    //     FillVec4(&points[0],points_array[0]);
    //     FillVec4(&points[1],points_array[1]);
    //     FillVec4(&points[2],points_array[2]);
    //     FillVec4(&points[3],points_array[3]);
    //     for(int i=0;i<4;i++)
    //     {
    //         points[i] = MatrixMultiplication4D_Vec4D(Roty,points[i]);
    //         // PrintVec4(points[i]);
    //         points[i] = ProjectPoint(chitra,PROJECTION_MATRIX,points[i]);
    //         // PrintVec4(points[i]);
    //     }
    //     for(int i=0;i<4;i++)
    //     {
    //         circles[i].pos_x = points[i].cords[0];
    //         circles[i].pos_y = points[i].cords[1];
    //         circles[i].radius = 5;
    //     }
    //     for(int i=0;i<4;i++)
    //     {
    //         ChitraAltFillCircle(chitra,circles[i],0xFF112233);
    //     }
    // FillVec4(&points[0],point1);
    // FillVec4(&points[1],point2);
    // FillVec4(&points[2],point3);
    // points[0] = MatrixMultiplication4D_Vec4D(PROJECTION_MATRIX,points[0]);
    // points[1] = MatrixMultiplication4D_Vec4D(PROJECTION_MATRIX,points[1]);
    // points[2] = MatrixMultiplication4D_Vec4D(PROJECTION_MATRIX,points[2]);
    // ProjectPoint(chitra,&points[0]);
    // ProjectPoint(chitra,&points[1]);
    // ProjectPoint(chitra,&points[2]);
    // for(int i=0;i<3;i++)
    // {
    //     triangle.x[i] = points[i].cords[0];
    //     triangle.y[i] = points[i].cords[1];
    // }
    // PrintVec4(points[0]);
    // PrintVec4(points[1]);
    // PrintVec4(points[2]);
    // ChitraAntiAiliasingFillTriangle(chitra,triangle,0xAA0000AA);
    // printf("%f",CosDeg(1.5));
    // Matrix4x4 matrix1,matrix2,result;
    // float mat1[] = {1,0,0,0,
    //               0,1,0,0,
    //               0,0,1,0,
    //               0,0,0,1};
    // float mat2[] = {1,0,0,0,
    //     0,1,0,0,
    //     0,0,1,0,
    //     0,0,0,1};
    // FillMatrix(&matrix1,mat1);
    // FillMatrix(&matrix2,mat2);
    // result = MatrixMultiplication4D_4D(matrix1,matrix2);
    // PrintMatrix4X4(&result);
    ChitraSavePPM(chitra,"output.ppm");
}




void EventLoop(Chitra chitra,clock_t start)
{   
    increment = (60*(clock()-start)/(CLOCKS_PER_SEC)); 
    // printf("%d",increment);
    ChitraFill(chitra,0xFFFFFFFF);
    float sin_rot_y = SinDeg(CAMERAROTY+increment);
    float cos_rot_y = CosDeg(CAMERAROTY+increment);
    float points_array[4][4] = {{-4,-4,5,1},
                                {-4,4,5,1},
                                {4,4,5,1},
                                {4,-4,5,1}};
    float Rotate_y[] = {cos_rot_y,0,sin_rot_y,0,
                        0,1,0,0,
                        -sin_rot_y,0,cos_rot_y,0,
                        0,0,0,1};
    Matrix4x4 Roty;
    FillMatrix(&Roty,Rotate_y);
    Vec4 points[4];
    Circle circles[4];
    FillVec4(&points[0],points_array[0]);
    FillVec4(&points[1],points_array[1]);
    FillVec4(&points[2],points_array[2]);
    FillVec4(&points[3],points_array[3]);
    for(int i=0;i<4;i++)
    {
        points[i] = MatrixMultiplication4D_Vec4D(Roty,points[i]);
        points[i] = ProjectPoint(chitra,PROJECTION_MATRIX,points[i]);
        // PrintVec4(points[i]);
        // PrintVec4(points[i]);
    }
    for(int i=0;i<4;i++)
    {
        circles[i].pos_x = points[i].cords[0];
        circles[i].pos_y = points[i].cords[1];
        circles[i].radius = 5;
    }
    // for(int i=0;i<4;i++)
    // {
    //     ChitraAltFillCircle(chitra,circles[i],0xFFFF0000);
    // }
    Triangle triangle1,triangle2;
    Line line1,line2;
    for(int i=0;i<3;i++)
    {
        triangle1.x[i] = points[i].cords[0];
        triangle1.y[i] = points[i].cords[1];
    }

    triangle2.x[0] = points[0].cords[0];
    triangle2.y[0] = points[0].cords[1];
    triangle2.x[1] = points[2].cords[0];
    triangle2.y[1] = points[2].cords[1];
    triangle2.x[2] = points[3].cords[0];
    triangle2.y[2] = points[3].cords[1];
    line1.x0 = points[0].cords[0];
    line1.y0 = points[0].cords[1];
    line1.x1 = points[2].cords[0];
    line1.y1 = points[2].cords[1];
    line2.x0 = points[1].cords[0];
    line2.y0 = points[1].cords[1];
    line2.x1 = points[3].cords[0];
    line2.y1 = points[3].cords[1];
    ChitraAntiAiliasingFillTriangle(chitra,triangle1,0xFFFF0000);
    ChitraAntiAiliasingFillTriangle(chitra,triangle2,0xFFFF0000);
    // ChitraDrawLine(chitra,line1,0xFFFF0000);
    // ChitraDrawLine(chitra,line2,0xFFFF0000);
    ChitraAntiAiliasingDrawLine(chitra,line1,0xFFFF0000);
    ChitraAntiAiliasingDrawLine(chitra,line1,0xFFFF0000);
}