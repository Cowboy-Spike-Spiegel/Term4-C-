#include<iostream>
#include"Matrix"

int main()
{
    Matrix A1 , A2 , A3 ;
    
    // A1
        std::cout << "\nCreate A1 !\n" ;
        A1.Matrix_create() ;
        std::cout << "A1 output:\n" ;
        A1.output() ;

    // A2
        std::cout << "\nCreate A2 !\n\n" ;
        A2.Matrix_create() ;
        std::cout << "A2 output:\n" ;
        A2.output() ;

    // plus
        A1.plus( A2 , A3 ) ;
        std::cout << "\nA3 = A1+A2 - output:\n" ;
        A3.output() ;

    // minus
        A1.minus( A2 , A3 ) ;
        std::cout << "\nA3 = A1-A2 - output:\n" ;
        A3.output() ;

    return 0 ;
}