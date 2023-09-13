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
#include "PosIO.h"
using namespace std;
namespace sdds {

    ostream& operator<<(ostream& os, const PosIO& o) {
        return o.write(os);
    }

    istream& operator>>(istream& is, PosIO& o) {
        return o.read(is);
    }

    ofstream& operator<<(ofstream& ofs, const PosIO& o) {
        return o.save(ofs);
    }

    ifstream& operator>>(ifstream& ifs, PosIO& o) {
        return o.load(ifs);
    }

}
