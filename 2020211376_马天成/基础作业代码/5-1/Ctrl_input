#ifndef _CTRL_INPUT
#define _CTRL_INPUT

// ----------------------------------------------------------------------------
#include<iostream>
#include<string>

// declaration
bool my_getChar( char &target ) ;
bool my_getStr( std::string &target ) ;
bool my_getNums( int size , int* target ) ;
bool my_getNums( int size , double* target ) ;

// definition
bool my_getChar( char &target )
{
    while( std::cin.peek() == ' ' )  std::cin.get() ;  // ignore spaces

    if( std::cin.peek() == '\n' ) {
        std::cin.clear() ; std::cin.sync() ;
        std::cout << "Not enough! Please try again.\n" ;
        return false ;
    }

    std::cin >> target ;

    if( std::cin.fail() ){
        std::cin.clear() ; std::cin.sync() ;
        std::cout << "Error! Please try again.\n" ;
        return false ;
    }

    while( std::cin.peek() == ' ' )  std::cin.get() ;  // ignore spaces
    if( std::cin.get() != '\n' ) {
        std::cin.clear() ; std::cin.sync() ;
        std::cout << "Oh what you input in the tail? Please try again.\n" ;
        return false ;
    }

    return true ;
}

bool my_getStr( std::string &target )
{
    std::cout << "Please input a string with numbers, characters, '_' or '.' .\n" ;
    std::cin >> target ;
    for( int i=0 ; i < target.length() ; i++ )
        if (
            ( target[i] < '0' || target[i] > '9' ) &&
            ( target[i] < 'A' || target[i] > 'Z' ) &&
            ( target[i] < 'a' || target[i] > 'z' ) &&
            target[i] != '_' && target[i] != '.'
        ) {
            std::cout << "Please try again!\n" ;
            return false ;
        }
    
    return true ;
}

bool my_getNums( int size , int* target )
{
    for( int i=0 ; i < size ; i++ ) {

        while( std::cin.peek() == ' ' )  std::cin.get() ;  // ignore spaces

        if( std::cin.peek() == '\n' ) {
            std::cin.clear() ; std::cin.sync() ;
            std::cout << "Not enough! Please try again.\n" ;
            return false ;
        }

        std::cin >> target[i] ;  // get a number

        if( std::cin.fail() ){
            std::cin.clear() ; std::cin.sync() ;
            std::cout << "Error!(overflow or characters) Please try again.\n" ;
            return false ;
        }
    }

    while( std::cin.peek() == ' ' )  std::cin.get() ;  // ignore spaces
    if( std::cin.get() != '\n' ) {
        std::cin.clear() ; std::cin.sync() ;
        std::cout << "Oh what you input in the tail? Please try again.\n" ;
        return false ;
    }

    return true ;
}

bool my_getNums( int size , double* target )
{
    for( int i=0 ; i < size ; i++ ) {

        while( std::cin.peek() == ' ' )  std::cin.get() ;  // ignore spaces

        if( std::cin.peek() == '\n' ) {
            std::cin.clear() ; std::cin.sync() ;
            std::cout << "Not enough! Please try again.\n" ;
            return false ;
        }

        std::cin >> target[i] ;  // get a number

        if( std::cin.fail() ){
            std::cin.clear() ; std::cin.sync() ;
            std::cout << "Overflow! Please try again.\n" ;
            return false ;
        }
    }

    while( std::cin.peek() == ' ' )  std::cin.get() ;  // ignore spaces
    if( std::cin.get() != '\n' ) {
        std::cin.clear() ; std::cin.sync() ;
        std::cout << "Oh what you input in the tail? Please try again.\n" ;
        return false ;
    }

    return true ;
}

// ----------------------------------------------------------------------------
#endif