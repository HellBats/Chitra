#ifndef MATH_C
#define MATH_C


#include"include/Chitra.h"
#include<pthread.h>

#define SCREENDEPTH 500.0
#define CAMERAX 0.0
#define CAMERAY 10.0
#define CAMERAZ -40.0
#define CAMERAROTX -10
#define CAMERAROTY 0
#define CAMERAROTZ 0
#define PRECISION 10

typedef struct 
{
    float matrix[4];
}Matrix2X2;


typedef struct 
{
    float cords[4];
}Vec4;


typedef struct 
{
    Matrix2X2 matrix[4];
    size_t size;
}Matrix4x4;



float CalculateTaylorTerm(float x,int a);
float SinDeg(float x);
float CosDeg(float x);
Matrix2X2 AddMatrix2X2(Matrix2X2 matrix1,Matrix2X2 matrix2);
Matrix2X2 SubMatrix2X2(Matrix2X2 matrix1,Matrix2X2 matrix2);
Matrix2X2 Multiply2X2(Matrix2X2 matrix1,Matrix2X2 matrix2);
Matrix4x4 MatrixMultiplication4D_4D(Matrix4x4 matrix1,Matrix4x4 matrix2);
void FillMatrix(Matrix4x4 *matrix,float numbers[]);
void FillVec4(Vec4 *vector,float numbers[]);
void PrintMatrix4X4(Matrix4x4 *matrix);
Vec4 MatrixMultiplication4D_Vec4D(Matrix4x4 matrix,Vec4 vector);
Matrix4x4 CalculateProjectionMatrix();
Vec4 ProjectPoint(Chitra chitra,Matrix4x4 ProjectionMatrix,Vec4 vector);
void PrintVec4(Vec4 vector);


#endif