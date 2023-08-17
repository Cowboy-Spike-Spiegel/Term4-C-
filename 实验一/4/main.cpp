#include<iostream>
#include<string>
#include"Ctrl_input"
#include"Ctrl_output"

int main()
{
    // ********************************************************************************************
    my_putStr( "One day , you have a dream. You don't believe God is exist, but you met him.\n"
                "God: A number between 1 an 1000 has been generated. Can you guess it?\n"
                "You: My choice is[Y/N]: " ) ;

    char choice ; // select what you choose
    while(1) {
        while( !my_getChar( choice ) ) ;
        std::cout << "\n" ;

        if( choice == 'Y' || choice == 'y' ) break ;
        else if( choice == 'N' || choice == 'n' ) {
            my_putStr( "God: What a bored man! See you forever! PUA~\n" ) ;
            my_putStr( "You wake up.\n" ) ;
            system("pause") ;
            return 0 ;
        }
        my_putStr( "God: Whar a stupid man! Just Yes or No!\n" ) ;
    }

    lable:
    // ********************************************************************************************
    srand(time(0));
    int randomNum = rand()%1000 + 1 ;
    int inputNum ;

    int cnt = 0 ;
    int flag = 0 ; // guess correctly
    while( !flag && cnt <= 10 ) {
        my_putStr( "God: Guess it the " + std::to_string(++cnt) + "th time.\n" ) ;
        
        while( !my_getNums( 1 , &inputNum ) ) ;
        if( inputNum < 1 || inputNum > 1000 ) {
            my_putStr( "God: Not in the domain, try again.\n" ) ;
            cnt--;
            continue;
        }
        if( inputNum == randomNum )
            flag = 1 ;
        else if( inputNum < randomNum )
            my_putStr( "God: Small, try again.\n" ) ;
        else if( inputNum > randomNum )
            my_putStr( "God: Large, try again.\n" ) ;
    }

    if( flag == 0 ) {
        my_putStr( "God: You have guessed for 11 times, 11 is enough, but you don't guess it. A clever man never do that.\n"
                    "     Do you want to guess again?\n"
                    "You: My choice is[Y/N]: " ) ;

        while(1) {
            while( !my_getChar( choice ) ) ;
            std::cout << "\n" ;

            if( choice == 'N' || choice == 'n' ) {
                my_putStr( "God: Shame on you! PUA~\n" ) ;
                break ;
            }
            else if( choice == 'Y' || choice == 'y' ) {
                my_putStr( "God: Emmmm, OK, give you a chance.\n" ) ;
                goto lable ; 
            }
            my_putStr( "God: Whar a stupid man! Just Yes or No!\n" ) ;
        }
    }
    else  my_putStr( "God: Congratulations. PUA~\n" ) ;

    my_putStr( "You wake up.\n" ) ;
    system("pause") ;

    return 0 ;
}