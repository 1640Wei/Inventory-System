// Final Project Milestone 4
//
// Version 1.0
// Date	2023-04-03
// Author	Ching Wei Lai
// Description
// This program test the student implementation of the PosApp class
// for submission.
//
///////////////////////////////////////////////////////////////////
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
namespace sdds {
   //For date validation
    const int noerr = 0; //For date validation
    const int missY = 1; //Invalid Year + cnannot read the year
    const int yerr = 2;
    const int missM = 3; //Invalid Month  + cnannot read the month
    const int merr = 4;
    const int missD = 5;//Invalid Day + cnannot read the day
    const int derr = 6;
    const int missH = 7;//Invalid Hour + cnannot read the hour
    const int herr = 8;
    const int missMin = 9;//Invalid Minute + cnannot read the minute
    const int minerr = 10;

    class Date {
        int m_year;
        int m_month;
        int m_day;
        int m_hour;
        int m_min;
        int err; //Error attribute to keep track of the success of operations
        bool m_dateOnly;//Date also has a flag for using date only (no hour or minutes)
        int mdays()const;
        //implemented function
        //system date and time
        void getSystemDate();
    public:
        //constructor
        Date();
        //year, month, day
        Date(int year, int month, int day);
        //year, month, day, hour, min 
        Date(int year, int month, int day, int hour, int min = 0);
        //year, month, day ,hour, nin
        void set(int year, int month, int day, int hour, int min);
        //is empty
        bool empty()const;
        //is date only
        bool isDateOnly() const;
        //set error to empty state
        void setEmpty();
        //Comparison Operator Overloads ->   ==, != , < , > , <= , >=
        bool operator==(const Date& D)const;
        bool operator!=(const Date& D)const;
        bool operator<(const Date& D)const;
        bool operator>(const Date& D)const;
        bool operator<=(const Date& D)const;
        bool operator>=(const Date& D)const;
        //the error query
        std::string error() const; //reutnr messag
        //set the error to error object in the class
        void errCheck(int e);
        bool bad() const;
        //dateOnly Modifier method
        Date& dateOnly(bool b);
        bool operator!() const;
        //set the correct output format
        std::ostream& write(std::ostream& ostr) const;
        //Date validation -> check the year, month, day, hour, min etc.
        std::istream& read(std::istream& istr);
    };
    //ostream insertion operator overload
    std::ostream& operator<<(std::ostream& ostr, const Date& D);
    //istream extraction operator overload
    std::istream& operator>>(std::istream& istr, Date& D);
}
#endif

