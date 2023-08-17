#include "basic_Time.h"

//_____________________________________________________________________________
BigTime::BigTime(void) { obj = new int[3] ; }
BigTime::~BigTime(void) { delete[] obj ; }
int* BigTime::get(void) { return obj ; }
bool BigTime::create( int year, int month, int day )
{
    // obviously false
    if( year != 2022 || day < 1 )
        return false ;
    if( month < 1 || month > 12 )
        return false ;
    if( day < 1 || day > 31 )
        return false ;
    
    // month-day false
    if( day==31 && month!=1 && month!=3 && month!=5 && month!=7 && month!=8 && month!=10 && month!=12 )
        return false ;
    if( month == 2 && day > 28 )
        return false ;

    // evaluation
    obj[0] = year ;
    obj[1] = month ;
    obj[2] = day ;

    return true ;
}


//_____________________________________________________________________________
SmallTime::SmallTime(void) { obj = new int[3] ; }
SmallTime::~SmallTime(void) { delete[] obj ; }
int* SmallTime::get(void) { return obj ; }
bool SmallTime::create( int hour, int minute=0, int second=0 )
{
    // obviously false
    if( hour < 0 || hour > 23 )
        return false ;
    if( minute < 0 || minute > 59 )
        return false ;
    if( second < 0 || second > 59 )
        return false ;

    // evaluation
    obj[0] = hour ;
    obj[1] = minute ;
    obj[2] = second ;

    return true ;
}


//_____________________________________________________________________________
bool FullTime::create( int year, int month, int day, int hour, int minute=0, int second=0, int dayOfWeek=1, int week=1 )
{
    this->dayOfWeek = dayOfWeek;
    this->week = week;
    return
        bigTime.create(year, month, day)
        && smallTime.create(hour, minute, second) ;
}
void FullTime::create_BigTime( BigTime obj )    { bigTime = obj ; }
void FullTime::create_SmallTime( SmallTime obj )    { smallTime = obj ; }
void FullTime::create_DayOfWeek( int dayOfWeek ) { this->dayOfWeek = dayOfWeek ; }
void FullTime::create_week(int week)    { this->week = week; }
BigTime& FullTime::get_BigTime(void)    { return bigTime ; }
SmallTime& FullTime::get_SmallTime(void)    { return smallTime ; }
int& FullTime::get_DayOfWeek(void) { return dayOfWeek ; }
int& FullTime::get_Week(void)   { return week ; }
void FullTime::second_Pass() {
    smallTime.get()[2]+=10;
    if(smallTime.get()[2]>=60) {
        smallTime.get()[2]=0;
        minute_Pass();
    }
}
void FullTime::minute_Pass() {
    smallTime.get()[1]++;
    if(smallTime.get()[1]==60) {
        smallTime.get()[1]=0;
        hour_Pass();
    }
}
void FullTime::hour_Pass() {
    smallTime.get()[0]++;
    if(smallTime.get()[0]==24) {
        smallTime.get()[0]=0;
        day_Pass();
    }
}
void FullTime::day_Pass() {
    bigTime.get()[2]++;
    if(bigTime.get()[2]==32) {
        bigTime.get()[2]=1;
        month_Pass();
    }
    if(bigTime.get()[2]==31 &&
      (bigTime.get()[1]==4||bigTime.get()[1]==6||bigTime.get()[1]==9||bigTime.get()[1]==11) ) {
        bigTime.get()[1]=1;
        month_Pass();
    }
    if(bigTime.get()[1]==2) {
        if(bigTime.get()[2]==30 && (bigTime.get()[0]%4)==0) {
            bigTime.get()[2]=1;
            month_Pass();
        }
        if(bigTime.get()[2]==29 && (bigTime.get()[0]%4)!=0) {
            bigTime.get()[2]=1;
            month_Pass();
        }
    }
    if(dayOfWeek==7) {
        dayOfWeek = 1;
        week++;
    }
    else
        dayOfWeek++;
}
void FullTime::month_Pass() {
    bigTime.get()[1]++;
    if(bigTime.get()[1]==13) {
        bigTime.get()[1]=1;
        bigTime.get()[0]++;
    }
}
