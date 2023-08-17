#include<iostream>
#include<Windows.h>
#include"Point"


int main()
{
    std::cout << "\n" ;
    Point obj( "point" , 10 , 10 ) ;

    std::cout << "\nobj: " << obj << "\n" ;
    system("pause") ;
    std::cout << "\nobj++: " << (obj++) << "\n" ;
    system("pause") ;
    std::cout << "\n++obj: " << (++obj) << "\n" ;
    system("pause") ;
    std::cout << "\nobj--: " << (obj--) << "\n" ;
    system("pause") ;
    std::cout << "\n--obj: " << (--obj) << "\n" ;
    system("pause") ;

    return 0 ;
}