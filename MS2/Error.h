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
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <iostream>

namespace sdds {
	class Error {
		char* m_errMes;
	public:
		//Error Construction
		Error();
		Error(const char* err);
		//Rule of three
		//copy constructor
		Error(const Error& R);
		//copy assignment operator
		Error& operator=(const Error& R);
		//destructor
		virtual ~Error();
		//boolean type conversion
		operator bool() const;
		//clear()
		void clear();
		//(double check it is nullptr)
		bool isClear() const;
		//if not nullpte or empty -> DMA
		void message(const char* V);
		// return the error message
		const char* message()const;
		
	};
	//ostream insertion
	std::ostream& operator<<(std::ostream& os, const Error& E);

}
#endif