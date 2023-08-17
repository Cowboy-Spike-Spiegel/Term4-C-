#include<iostream>
#include<windows.h>
#include"Shape"

int main()
{
    /*
        std::cout << "\nShape:\n" ;
        MyShape objShape ;
        objShape.create() ;
        objShape.showArea() ;
    */

    std::cout << "\nRectangle:\n" ;
    MyRectangle objRectangle ;
    objRectangle.create() ;
    objRectangle.showArea() ;

    std::cout << "\nCircle:\n" ;
    MyCircle objCircle ;
    objCircle.create() ;
    objCircle.showArea() ;

    std::cout << "\nSquare:\n" ;
    MySquare objSquare ;
    objSquare.create() ;
    objSquare.showArea() ;

    MyShape& tmp1 = objRectangle;
    tmp1.showArea();

    MyShape& tmp2 = objCircle ;
    tmp2.showArea();

    MyShape& tmp3 = objSquare;
    tmp3.showArea();

    return 0 ;
}