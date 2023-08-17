#include<iostream>
#include<windows.h>
#include"Shape"

int main()
{
    std::cout << "\nShape:\n" ;
    MyShape objShape ;
    objShape.create() ;
    objShape.showArea() ;

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

    return 0 ;
}