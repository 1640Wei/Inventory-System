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
#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>
#include <fstream>
namespace sdds {
    class PosIO {
    public:
       //four virtual functions
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual std::ofstream& save(std::ofstream& ofs) const = 0;
        virtual std::ifstream& load(std::ifstream& ifs) = 0;
        virtual ~PosIO() {};
    };
    //helper functions
    std::ostream& operator<<(std::ostream& os, const PosIO& o);
    std::istream& operator>>(std::istream& is, PosIO& o);
    std::ofstream& operator<<(std::ofstream& ofs, const PosIO& o);
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& o);
}
#endif
