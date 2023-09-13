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
#include "Perishable.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
using namespace std;
namespace sdds {
    //item type -> return 'P'
    char Perishable::itemType() const {
        return 'P';
    }
    //write 
    ostream& Perishable::write(ostream& os) const {
        Item::write(os);
        if (!isClear()) {
            return os;
        }
        if (m_displayType == POS_LIST) {
            os << setw(6) << m_expiry << " |";
        }
        else if (m_displayType == POS_FORM) {
            os << "Expiry date: " << m_expiry << endl;
            os << "=============^" << endl;
        }
        return os;
    }
    //read
    istream& Perishable::read(istream& is) {
        Item::read(is);
        // good state or istream has failed -> do nothing, otherwise -> create a local instance of Date and set it to date only
        if (!isClear() || is.fail()) {
            return is;
        }
        Date expiryDate;
        expiryDate.dateOnly(true);       
        cout << "Expiry date (YYYY/MM/DD)" << endl;
        cout << "> ";   
        is >> expiryDate;
        setExpiry(expiryDate);
        return is;
    }
    //load
    std::ifstream& Perishable::load(std::ifstream& ifs) {
        Item::load(ifs);
        //If the object is not in a good state or ifstream has failed -> do nothing, otherwise -> create a local instance of Date and set it to date only
        if (!isClear() || ifs.fail()) {
            return ifs;
        }
        Date expiryDate;
        expiryDate.dateOnly(true);
        ifs.ignore(1, ',');  // Ignore one character to pass the comma
        ifs >> expiryDate;
        setExpiry(expiryDate);
        return ifs;
    }
    //save
    ofstream& Perishable::save(ofstream& ofs) const {
        Item::save(ofs);
        //If the object is in a good state -> insert a commaand then the expiry date into ofstream, otherwise -> do nothing
        if (isClear()) {
            ofs << "," << m_expiry;
        }
        return ofs;
    }
    //set the expiry date
    void Perishable::setExpiry(Date expiry) {
       //check the expiry
        if (expiry.bad()) {
            m_err.message(expiry.error().c_str());
        } else {
            m_expiry = expiry;
        }
    }
}
