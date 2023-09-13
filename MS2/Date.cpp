// Final Project Milestone 2
//
// Version 1.0
// Date	2023-03-20
// Author	Ching Wei Lai
// Description
// This program test the student implementation of the PosApp class
// for submission.
//
///////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include "Date.h"

using namespace std;
namespace sdds {
   //The valid range of values for the year
   const int MAX_YEAR = 2038;
   const int MIN_YEAR = 2000;
   //implemented function
   //system date and time
   void Date::getSystemDate() {
      time_t currentTime = time(NULL);
      tm* localTime = localtime(&currentTime);
      m_day = localTime->tm_mday;
      m_month = localTime->tm_mon + 1;
      m_year = localTime->tm_year + 1900;
      if (!m_dateOnly) {
         m_hour = localTime->tm_hour;
         m_min = localTime->tm_min;
      }
   }
   //set the error to error object in the class
   void Date::errCheck(int E) {
      err = E;
   }
   //constructor
   Date::Date() {
      m_dateOnly = false;
      getSystemDate();
      err = noerr;
   }
   //year, month, day
   Date::Date(int year, int month, int day) {
      m_dateOnly = true;
      m_year = year;
      m_month = month;
      m_day = day;
      m_hour = m_min = 0;
      err = noerr;
   }
   //year, month, day, hour, min 
   Date::Date(int year, int month, int day, int hour, int min) {
      m_dateOnly = false;
      m_year = year;
      m_month = month;
      m_day = day;
      m_hour = hour;
      m_min = min;
      err = noerr;
   }
   //year, month, day ,hour, nin
   void Date::set(int year, int month, int day, int hour, int min) {
      m_year = year;
      m_month = month;
      m_day = day;
      m_hour = hour;
      m_min = min;
      err = noerr;
   }
   //error is empty
   bool Date::empty() const {
      return err != noerr;
   }
   //is date only
   bool Date::isDateOnly() const {
      return m_dateOnly;
   }
   //set error to empty state
   void Date::setEmpty() {
      err = noerr;
   }
   //return error message
   string Date::error() const {
      string message;
      switch (err) {
      case 0:
         message = "";
         break;
      case 1:
         message = "Cannot read year entry";
         break;
      case 2:
         message = "Invalid Year";
         break;
      case 3:
         message = "Cannot read month entry";
         break;
      case 4:
         message = "Invalid Month";
         break;
      case 5:
         message = "Cannot read day entry";
         break;
      case 6:
         message = "Invalid Day";
         break;
      case 7:
         message = "Cannot read hour entry";
         break;
      case 8:
         message = "Invalid Hour";
         break;
      case 9:
         message = "Cannot read minute entry";
         break;
      case 10:
         message = "Invlid Minute";
         break;
      }
      return message;
   }
   //error attribute is not "no error"
   bool Date::notErr() const {
      return err != noerr;
   }
   //Comparison Operator Overloads ->   ==, != , < , > , <= , >=
   bool Date::operator==(const Date& D) const {
      return (this->m_year == D.m_year && this->m_month == D.m_month &&
         this->m_day == D.m_day && this->m_hour == D.m_hour &&
         this->m_min == D.m_min);
   }
   bool Date::operator!=(const Date& D) const {
      return !(*this == D);
   }
   bool Date::operator<(const Date& D) const {
      if (this->m_year < D.m_year)
         return true;
      else if (this->m_year == D.m_year && this->m_month < D.m_month)
         return true;
      else if (this->m_year == D.m_year && this->m_month == D.m_month &&
         this->m_day < D.m_day)
         return true;
      else if (this->m_year == D.m_year && this->m_month == D.m_month &&
         this->m_day == D.m_day && this->m_hour < D.m_hour)
         return true;
      else if (this->m_year == D.m_year && this->m_month == D.m_month &&
         this->m_day == D.m_day && this->m_hour == D.m_hour &&
         this->m_min < D.m_min)
         return true;
      else
         return false;
   }
   bool Date::operator>(const Date& D) const {
      return !(*this <= D);
   }
   bool Date::operator<=(const Date& D) const {
      return (*this == D || *this < D);
   }
   bool Date::operator>=(const Date& D) const {
      return !(*this < D);
   }
   //dateOnly Modifier method
   //receives a boolean and returns the reference of the current date class.
   Date& Date::dateOnly(bool b){
      //set the date-only flag to the value received from the argument of the function
      m_dateOnly = b;
      // is "true" which sets the object to date only
      if (m_dateOnly) {
         //hour and minute attributes -> 0
         m_hour = 0;
         m_min = 0;
      }
      return *this;
   }
   //Overload the bool type conversion operator
   bool Date::operator!() const {
      //return the opposite of the state of the error attribute.
      return err != noerr;
   }
   //Number of days in the month
   int Date::daysOfMonth() const {
      //set the day to zero
      int days = 0;
      //check the month is valid
      if (m_month >= 1 && m_month <= 12) {
         //2 -> 28, 4.6.9.11 -> 30, else -> 31
         switch (m_month) {  
         case 2:
            days = 28 + (int)(m_year % 4 == 0 && (m_year % 100 != 0 || m_year % 400 == 0));
            break; // 2 -> 28,  
         case 4:
         case 6:
         case 9:
         case 11:
            days = 30;
            break; //4.6.9.11 -> 30,
         default:
            days = 31;
            break;
         }
      }
      //return the days
      return days;
   }
   //read the data -> do the date validation process 
   istream& Date::read(istream& istr) {
      m_year = 0;
      m_month = 0;
      m_day = 0;
      m_hour = 0;
      m_min = 0;
      //create an array for reading
      int ent = m_dateOnly ? 3 : 5;
      //dynamic allocation
      int* date = new int[ent];
      for (int i = 0; i < ent; i++) {
         date[i] = 0;
      }
      //do not need to verify the delimiters
      char del = '\0';
      int i = 0;
      bool flag = false;
      while (!istr.fail() && i < ent) {
         if (flag) { //ignore delimeter
            istr >> del;
            flag = false;
         }
         else { //keep reading
            istr >> date[i];
            i += 1;
            flag = true;
         }
      }
      m_year = date[0]; //set the year value
      m_month = date[1]; //set the month value
      m_day = date[2]; //set the day value
      //check the dateOnly -> set hour & minuter to 0
      if (m_year == 0) {
         errCheck(missY);
         delete[] date;
         date = nullptr;
         return istr;
      }
      else if (m_year < MIN_YEAR || m_year > MAX_YEAR) {
         errCheck(yerr);
         delete[] date;
         date = nullptr;
         return istr;
      }
      // Validate the month
      if (m_month == 0) {
         errCheck(missM);
         delete[] date;
         date = nullptr;
         return istr;
      }
      else if (m_month < 1 || m_month > 12) {
         errCheck(merr);
         delete[] date;
         date = nullptr;
         return istr;
      }
      // Validate the day
      if (m_day == 0) {
         errCheck(missD);
         delete[] date;
         date = nullptr;
         return istr;
      }
      else if (m_day < 1 || m_day > daysOfMonth()) {
         errCheck(derr);
         delete[] date;
         date = nullptr;
         return istr;
      }
      // If date only, we are done.
      if (m_dateOnly) {
         errCheck(noerr);
         delete[] date;
         date = nullptr;
         return istr;
      }
      else {
         m_hour = date[3];
         m_min = date[4];
      }
      // Validate the hour
      if (m_hour == 0 && istr.fail()) {
         errCheck(missH);
         delete[] date;
         date = nullptr;
         return istr;
      }
      else if (m_hour < 0 || m_hour > 23) {
         errCheck(herr);
         delete[] date;
         date = nullptr;
         return istr;
      }
      // Validate the minute
      if (m_min == 0 && istr.fail()) {
         errCheck(missMin);
         delete[] date;
         date = nullptr;
         return istr;
      }
      else if (m_min < 0 || m_min > 59) {
         errCheck(minerr);
         delete[] date;
         date = nullptr;
         return istr;
      }
      // All entries are valid
      errCheck(noerr);
      delete[] date;
      date = nullptr;
      return istr;
   }


   //set the correct format for output
   ostream& Date::write(ostream& ostr) const {
      if (err != noerr) {
         ostr << error() << "(";
      }
      ostr << m_year << '/';
      ostr.width(2);
      ostr.fill('0');
      ostr << m_month << '/';
      ostr.width(2);
      ostr.fill('0');
      ostr << m_day;

      if (!m_dateOnly) {
         ostr << ", ";
         ostr.width(2);
         ostr.fill('0');
         ostr << m_hour << ':';
         ostr.width(2);
         ostr.fill('0');
         ostr << m_min;
      }
      if (err != noerr) {
         ostr << ")";
      }
      return ostr;
   }
   //ostream insertion operator overload
   std::ostream& operator<<(std::ostream& os, const Date& D) {
      return D.write(os);
   }
   // istream extraction operator overload
   std::istream& operator>>(std::istream& is, Date& D) {
      return D.read(is);
   }
}
