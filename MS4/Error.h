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
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <iostream>
namespace sdds {
	class Error {
		char* m_emessage;
	public:
		//constructor
		Error();
		//Rule of three
		Error(const Error& other);
		Error& operator=(const Error& other);
		//destructor
		virtual ~Error();
		Error(const char* errorMessage);
		operator bool() const;
		//clear function
		void clear();
		//check if it is clear or not
		bool isClear() const;
		//message function
		void message(const char* value);
		const char* message()const;
	};
	//helper function
	std::ostream& operator<<(std::ostream& os, const Error& error);
}
#endif