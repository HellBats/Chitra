#include"include/3D/Math.h"


Matrix2X2 AddMatrix2X2(Matrix2X2 matrix1,Matrix2X2 matrix2)
{
    Matrix2X2 matrix3;
    for(int i=0;i<4;i++) matrix3.matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
    return matrix3;
}

Matrix2X2 SubMatrix2X2(Matrix2X2 matrix1,Matrix2X2 matrix2)
{
    Matrix2X2 matrix3;
    for(int i=0;i<4;i++) matrix3.matrix[i] = matrix1.matrix[i] - matrix2.matrix[i];
    return matrix3;
}

Matrix2X2 Multiply2X2(Matrix2X2 matrix1,Matrix2X2 matrix2)
{
    Matrix2X2 matrix3;
    float m1 = (matrix1.matrix[0]+matrix1.matrix[3])*(matrix2.matrix[0]+matrix2.matrix[3]);
    float m2 = ((matrix1.matrix[2]+matrix1.matrix[3]))*matrix2.matrix[0];
    float m3 = (matrix1.matrix[0])*((matrix2.matrix[1]-matrix2.matrix[3]));
    float m4 = (matrix1.matrix[3])*(matrix2.matrix[2]-matrix2.matrix[0]);
    float m5 = (matrix1.matrix[0]+matrix1.matrix[1])*matrix2.matrix[3];
    float m6 = (matrix1.matrix[2]-matrix1.matrix[0])*(matrix2.matrix[0]+matrix2.matrix[1]);
    float m7 = (matrix1.matrix[1]-matrix1.matrix[3])*(matrix2.matrix[2]+matrix2.matrix[3]);
    matrix3.matrix[0] = m1+m4+m7-m5;
    matrix3.matrix[1] = m3 + m5;
    matrix3.matrix[2] = m2 + m4;
    matrix3.matrix[3] = m1+m3+m6-m2;
    return matrix3;
}
 
Matrix4x4 MatrixMultiplication4D_4D(Matrix4x4 matrix1,Matrix4x4 matrix2)
{
    Matrix4x4 resultant;
    Matrix2X2 m1 = Multiply2X2((AddMatrix2X2(matrix1.matrix[0],matrix1.matrix[3])),(AddMatrix2X2(matrix2.matrix[0],matrix2.matrix[3])));
    Matrix2X2 m2 = Multiply2X2(((AddMatrix2X2(matrix1.matrix[2],matrix1.matrix[3]))),matrix2.matrix[0]);
    Matrix2X2 m3 = Multiply2X2((matrix1.matrix[0]),SubMatrix2X2(matrix2.matrix[1],matrix2.matrix[3]));
    Matrix2X2 m4 = Multiply2X2((matrix1.matrix[3]),SubMatrix2X2(matrix2.matrix[2],matrix2.matrix[0]));
    Matrix2X2 m5 = Multiply2X2((AddMatrix2X2(matrix1.matrix[0],matrix1.matrix[1])),matrix2.matrix[3]);
    Matrix2X2 m6 = Multiply2X2(SubMatrix2X2(matrix1.matrix[2],matrix1.matrix[0]),(AddMatrix2X2(matrix2.matrix[0],matrix2.matrix[1])));
    Matrix2X2 m7 = Multiply2X2((SubMatrix2X2(matrix1.matrix[1],matrix1.matrix[3])),(AddMatrix2X2(matrix2.matrix[2],matrix2.matrix[3])));
    resultant.matrix[0] = SubMatrix2X2(AddMatrix2X2(AddMatrix2X2(m1,m4),m7),m5);
    resultant.matrix[1] = AddMatrix2X2(m3 , m5);                            
    resultant.matrix[2] = AddMatrix2X2(m2 , m4);
    resultant.matrix[3] = SubMatrix2X2(AddMatrix2X2(AddMatrix2X2(m1,m3),m6),m2);
    return resultant;
}

Matrix4x4 AddMatrix4X4(Matrix4x4 matrix1,Matrix4x4 matrix2)
{
    Matrix4x4 resultant;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++) 
            resultant.matrix[i] = AddMatrix2X2(matrix1.matrix[i],matrix2.matrix[i]);
    return resultant;
}

float SinDeg(float x)
{
    while(x>360) x-=360;
    unsigned int *number = (unsigned int *)&x;
    int maintisa = (*number <<9)>>9;
    x = x*3.14/180;
    if((((int)x/90))%2 != 1 || maintisa!=0) return x-Power(x,3)/6+Power(x,5)/120-Power(x,7)/5040+Power(x,9)/3672880;
    return 1.0;
}

float CosDeg(float x)
{
    while(x>360) x-=360;
    x = x*3.14/180;
    return 1-Power(x,2)/2+Power(x,4)/24-Power(x,6)/720+Power(x,8)/40320;
}

float Power(float x,int a)
{
    float result  = x;
    for(;a>1;a--) result*=x;
}

Matrix4x4 CalculateProjectionMatrix()
{
    Matrix4x4 Rotx,Roty,Rotz;
    float sin_rot_x = SinDeg(CAMERAROTX);
    float sin_rot_y = SinDeg(CAMERAROTY);
    float sin_rot_z = SinDeg(CAMERAROTZ);
    float cos_rot_x = CosDeg(CAMERAROTX);
    float cos_rot_y = CosDeg(CAMERAROTY);
    float cos_rot_z = CosDeg(CAMERAROTZ);
    float Rotate_x[] = {1,0,0,0,
                    0,cos_rot_x,-sin_rot_x,0,
                    0,sin_rot_x,cos_rot_x,0,
                    0,0,0,0};
    float Rotate_y[] = {cos_rot_y,0,sin_rot_y,0,
                    0,1,0,0,
                    -sin_rot_y,0,cos_rot_y,0,
                    0,0,0,0};
    float Rotate_z[] = {cos_rot_z,-sin_rot_z,0,0,
                    sin_rot_z,cos_rot_z,0,0,
                    0,0,1,0,
                    0,0,0,0};
    FillMatrix(&Rotx,Rotate_x);
    FillMatrix(&Roty,Rotate_y);
    FillMatrix(&Rotz,Rotate_z);
    // PrintMatrix4X4(&Rotx);
    // PrintMatrix4X4(&Roty);
    // PrintMatrix4X4(&Rotz);
    Matrix4x4 Camera_rotation = MatrixMultiplication4D_4D(MatrixMultiplication4D_4D(Rotx,Roty),Rotz);
    Matrix4x4 Translation;
    Matrix4x4 result;
    float translate[] = {0,0,0,-CAMERAX,
                         0,0,0,-CAMERAY,
                         0,0,0,-CAMERAZ,
                         0,0,0,0};
    FillMatrix(&Translation,translate);
    result = AddMatrix4X4(Camera_rotation,Translation);
    // PrintMatrix4X4(&result);
    return result; 
}


Vec4 MatrixMultiplication4D_Vec4D(Matrix4x4 matrix,Vec4 vector)
{
    Vec4 new_vector;
    for(int j=0;j<2;j++)
        for(int i=0;i<2;i++)
        {
            float sum =0;
            for(int k=0;k<4;k++)
            {
                sum+=matrix.matrix[2*j+k/2].matrix[2*i+k%2]*(vector.cords[k]);
            }
            new_vector.cords[2*j+i] = sum;
        }
    // new_vector.cords[3] = new_vector.cords[2]*(float)1/SCREENDEPTH;
    // for(int k=0;k<4;k++)
    // {
    //     new_vector.cords[k]/=new_vector.cords[3];
    // }
    return new_vector;
}




void FillMatrix(Matrix4x4 *matrix,float numbers[])
{
    for(int j=0;j<2;j++)
        for(int i=0;i<2;i++)
            for(int k=0;k<4;k++)
            {
                matrix->matrix[2*j+i].matrix[k] = numbers[8*j+2*i+4*(k/2)+(k%2)];
            }
}

void PrintMatrix4X4(Matrix4x4 *matrix)
{
    for(int j=0;j<2;j++)
        for(int i=0;i<2;i++)
        {
            for(int k=0;k<4;k++) printf("%f,",matrix->matrix[2*j+k/2].matrix[2*i+k%2]);
            printf("\n");
        }
}

void PrintVec4(Vec4 vector)
{
    for(int i=0;i<4;i++)
    {
        printf("%f\n",vector.cords[i]);
    }
}
void FillVec4(Vec4 *vector,float numbers[])
{
    for(int i=0;i<4;i++)
    {
        vector->cords[i] = numbers[i];
    }
}

Vec4 ProjectPoint(Chitra chitra,Matrix4x4 ProjectionMatrix,Vec4 vector)
{
    // PrintVec4(vector);
    Vec4 new_vector = MatrixMultiplication4D_Vec4D(ProjectionMatrix,vector);

    new_vector.cords[3] = new_vector.cords[2]*(float)1/SCREENDEPTH;
    for(int k=0;k<4;k++)
    {
        new_vector.cords[k]/=new_vector.cords[3];
    }
    // PrintVec4(new_vector); 
    new_vector.cords[0] = chitra.width/2 + new_vector.cords[0];
    new_vector.cords[1] = chitra.height/2 - new_vector.cords[1];  
    return new_vector;
}