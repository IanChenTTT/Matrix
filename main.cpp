#include <iostream>
#include <iomanip>
#include "./matrix.h"
void testAdd();
void testSub();
void showBrLine(int);
void testTranspose();
void testMult();
void testMultNum();
void testDotMat();
void testOperator1();
void testOperator2();

int main(){
    try{
        // testAdd();
        // showBrLine(10);
        // testSub();
        // showBrLine(10);
        // testTranspose();
        // showBrLine(10);
        // testMult();
        // showBrLine(10);
        // testMultNum();
        // showBrLine(10);
        // testDotMat();
        // testOperator1();
         testOperator2();
    }
    catch(std::exception& ex){
        std::cerr << "ERR:" << ex.what() << std::endl;
    }

    return 0;
}
Matrix* testMatInit(int row,int col,int val){
    Matrix* mat =new Matrix(row,col);
    int y;
    int x;
    for(y = 0 ; y < row ; y++)
        for(x = 0 ; x < col; x++)
            mat->set(y,x,val);
    return mat;
}
Matrix* testMatInitNum(int row,int col){
    Matrix* mat =new Matrix(row,col);
    int y;
    int x;
    int i = 0;
    for(y = 0 ; y < row ; y++)
        for(x = 0 ; x < col; x++)
            mat->set(y,x,i++);
    return mat;
}
void testAdd(){
    Matrix* mat = testMatInit(2,2,1);
    mat->show();
    std :: cout << std::endl;
    std :: cout <<std::setw(10)<< "+" << std::endl;
    Matrix* mat1 = testMatInit(2,2,2);
    mat1->show();

    mat->add(mat1);
    std :: cout << std::endl;
    std :: cout <<std::setw(10)<< "=" << std::endl;
    mat->show();
    delete mat;
    delete mat1;
}
void showBrLine(int N){
    std::cout<< std::setw(5);
    while(N--)std::cout << "-";
    std::cout << std::endl;
}
void testSub(){
    Matrix* mat = testMatInit(2,2,3);
    mat->show();
    std :: cout << std::endl;
    std :: cout <<std::setw(10)<< "-" << std::endl;
    Matrix* mat1 = testMatInit(2,2,2);
    mat1->show();
    mat->sub(mat1);

    std :: cout << std::endl;
    std :: cout <<std::setw(10)<< "=" << std::endl;
    mat->show();
    delete mat;
    delete mat1;
}
void testTranspose(){
    Matrix* mat = testMatInitNum(2,2);
    mat->show();
    std :: cout << std::endl;
    std :: cout <<std::setw(10)<< "Transpose" << std::endl;
    std :: cout << std::endl;
    Matrix newT = mat->transpose();
    newT.show();
    delete mat;
}
void testMult(){

    Matrix* mat = testMatInitNum(2,3);
    Matrix* mat1 = testMatInitNum(3,2);
    try{
        mat->show();
        std :: cout << std::endl;
        std :: cout <<std::setw(10)<< "*" << std::endl;
        mat1->show();
        Matrix newMul = mat->mulMat(mat1);

        std :: cout << std::endl;
        std :: cout <<std::setw(10)<< "=" << std::endl;
        newMul.show();
        delete mat;
        delete mat1;
    }
    catch(std::logic_error e){
        throw e;
        delete mat;
        delete mat1;
    }

}
void testMultNum(){
    Matrix* mat = testMatInitNum(2,2);
    mat->show();
    std :: cout << std::endl;
    std :: cout <<std::setw(10)<< "Multiply 3" << std::endl;
    std :: cout << std::endl;
    mat->multNum(3);
    mat->show();
    delete mat;
}
void testDotMat(){
    Matrix* mat = testMatInitNum(3,1);
    Matrix* mat1 = testMatInitNum(3,1);
    try{
        mat->show();
        std :: cout << std::endl;
        std :: cout <<std::setw(5)<< "." << std::endl;
        mat1->show();
        int Ans = mat->matDot(mat1);

        std :: cout << std::endl;
        std :: cout <<std::setw(10)<< "= " <<Ans<< std::endl;
        delete mat;
        delete mat1;
    }
    catch(std::logic_error e){
        throw e;
        delete mat;
        delete mat1;
    }
}
void testOperator1()
{
    Matrix A(2,2);
    std::cin >> A;
    showBrLine(5);
    A.show();
}
void testOperator2(){
    Matrix A(3, 3);
    A(0, 0) = 1; A(0, 1) =2; A(0,2) = 3;

    A(1, 0) = 1; A(1, 1) = 2; A(1,2) = 3;


    A(2,0) = 1; A(2, 1) =2; A(2,2) = 3;

    Matrix I(3, 3);

    I(0, 0) = 0; I(0,1) =1; I(0,2)=0;

    I(1,0)=1; I(1,1)=0; I(1,2)=0;

    I(2, 0) = 0; I(2, 1)=0; I(2,2)=1;

    std::cout << A << std::endl;
    showBrLine(5);
    std::cout << I << std::endl;
    showBrLine(5);
    A *= I;
    std::cout <<A<< std::endl;
}
