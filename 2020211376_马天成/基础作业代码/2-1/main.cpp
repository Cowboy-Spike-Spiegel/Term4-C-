#include<iostream>
//#include<Windows.h>
#include"Point&Circle"

int main()
{
    // initialization
    Circle A( "A" , 4 , 0 , 0 ) , B( "B" , 2 , 0 , 0 ) ;
    
    // relation between Circle A and B
    State relation = A.relation(B) ;
    if( relation == init )
        std::cout << "In it!\n" ;
    if( relation == disjoint )
        std::cout << "A and B is disjoint!\n" ;
    else if( relation == intersect )
        std::cout << "A and B is intersect!\n" ;
    else
        std::cout << "A and B is crossing!\n" ;
    system("pause") ;

    return 0 ;
}