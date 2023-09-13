// Final Project Milestone 3
//
// Version 1.0
// Date	2023-03-31
// Author	Ching Wei Lai
// Description
// This program test the student implementation of the PosApp class
// for submission.
//
///////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Error.h"

using namespace std;
namespace sdds {
   //Error Construction
   Error::Error() {
      m_errMes = nullptr;
   }
   Error::Error(const char* err) {
      m_errMes = nullptr;
      message(err);
   }
   //copy constructor
   Error::Error(const Error& R) {
      m_errMes = nullptr;
      *this = R;
   }
   //copy assignment operator
   Error& Error::operator=(const Error& R) {
      if (this != &R) {
         message(R.m_errMes);
      }
      return *this;
   }
   //destructor
   Error::~Error() {
      delete[] m_errMes;
   }
   //check it is clear or not
   Error::operator bool() const {
      return !isClear();
   }
   //clear()
   void Error::clear() {
      delete[] m_errMes;
      m_errMes = nullptr;
   }
   // return the object if it is null (double check it is nullptr)
   bool Error::isClear() const {
      return m_errMes == nullptr;
   }
   // not nullptr  or empty -> DMA
   void Error::message(const char* V) {
      //delete the message before allocate -> clear function
      clear();
      //if not nullpte or empty
      if (V != nullptr && V[0] != '\0') {
         //Dynamic Memory Allocation -> copy it to error meaage
         m_errMes = new char[strlen(V) + 1];
         strcpy(m_errMes, V);
      }
   }
   // return the error message
   const char* Error::message() const {
      return m_errMes;
   }
   ostream& operator<<(ostream& os, const Error& E) {
      //if the message is not nullptr
      if (E.message() != nullptr) {
         os << E.message(); //print the message
      }
      return os;
   }
}