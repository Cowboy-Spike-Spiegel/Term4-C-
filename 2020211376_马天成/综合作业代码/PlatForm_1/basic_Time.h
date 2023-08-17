 #ifndef _BASIC_TIME
#define _BASIC_TIME

// 时间点：年月日 
class BigTime
{
private:
    int* obj ;

public:
    BigTime(void) ;
    ~BigTime(void) ;
    int* get(void) ;
    bool create( int year, int month, int day ) ;
} ;


// 时间点：时分秒
class SmallTime
{
private:
    int* obj ;

public:
    SmallTime(void) ;
    ~SmallTime(void) ;
    int* get(void) ;
    bool create( int hour, int minute, int second ) ;
} ;


// 时间点：完整时间
class FullTime
{
private:
    BigTime bigTime ;
    SmallTime smallTime ;
    int dayOfWeek;
    int week;

public:
    bool create( int year, int month, int day, int hour, int minute, int second , int dayOfWeek, int week ) ;
    void create_BigTime( BigTime obj ) ;
    void create_SmallTime( SmallTime obj ) ;
    void create_DayOfWeek( int dayOfWeek ) ;
    void create_week(int week);
    BigTime& get_BigTime(void) ;
    SmallTime& get_SmallTime(void) ;
    int& get_DayOfWeek(void) ;
    int& get_Week(void);
    void second_Pass() ;
    void minute_Pass() ;
    void hour_Pass();
    void day_Pass();
    void month_Pass();
} ;

#endif
