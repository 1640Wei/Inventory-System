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
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <ctype.h>
#include "Error.h"
using namespace std;
namespace sdds {
   //constructor -> set to empty state
   Error::Error() {
      m_emessage = nullptr;
   }
   //Rule of three
   Error::Error(const Error& other) {
      m_emessage = nullptr;
      *this = other;
   }
   Error& Error::operator=(const Error& other) {
      if (this != &other) {
         message(other.m_emessage);
      }
      return *this;
   }
   //destructor
   Error::~Error() {
      delete[] m_emessage;
   }
   Error::Error(const char* errorMessage) {
      m_emessage = nullptr;
      message(errorMessage);
   }
   //set to empty state
   void Error::clear() {
      delete[] m_emessage;
      m_emessage = nullptr;
   }
   //set the error message to nullptr
   bool Error::isClear() const {
      return m_emessage == nullptr;
   }
   void Error::message(const char* value) {
      clear();
      // check the value is not nullptr and not '\0'
      if (value != nullptr && value[0] != '\0') {
         //DMA
         m_emessage = new char[strlen(value) + 1];
         strcpy(m_emessage, value);
      }
   }
   //return the error message
   const char* Error::message() const {
      return m_emessage;
   }
   Error::operator bool() const {
      return !isClear();
   }
   //helper function
   ostream& operator<<(ostream& os, const Error& e) {
      //check the message is not nullptr
      if (e.message() != nullptr) {
         os << e.message();
      }
      return os;
   }
}


