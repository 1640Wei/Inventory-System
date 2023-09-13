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
#include "NonPerishable.h"
using namespace std;
namespace sdds {
    //return 'N'
    char NonPerishable::itemType() const  { 
        return 'N';
    }
    //write
    ostream& NonPerishable::write(ostream& os) const {
        if (isClear()) {
            Item::write(os);
            if (m_displayType == POS_LIST) {
                os << "     N / A   |";
            }
            else if (m_displayType == POS_FORM) {
                os << "=============^" << endl;
            }
        }
        return os;
    }
}
