#include<iostream>
#include"Matrix"

int main()
{
    Matrix A1(4,4) , A2(4,4) , A3(4,4) ;
    
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
        A3 = A1+A2;
        std::cout << "\nA3 = A1+A2 - output:\n" ;
        A3.output() ;

    // minus
        A3 = A1-A2;
        std::cout << "\nA3 = A1-A2 - output:\n" ;
        A3.output() ;
    
    // copy
        Matrix* pA1 = new Matrix(A1);
        Matrix* pA2 = new Matrix(A2);
        Matrix* pA3 = new Matrix(A3);

        *pA3 = *pA1 + *pA2;
        std::cout << "pA3=pA1+pA2\n" ;
        std::cout << pA3->getObj()[1][1];
        pA3->output();
        *pA3 = *pA1 - *pA2;
        std::cout << "pA3=pA1-pA2\n" ;
        pA3->output();

        // 不用自己写函数释放，会主动调用析构
        delete pA1;
        delete pA2;
        delete pA3;

    return 0 ;
}