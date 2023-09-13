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
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds {
    class Perishable : public Item {
        Date m_expiry;
        void setExpiry(Date expiry);     
    public:
       char itemType()const override;
       //override functions
        std::ofstream& save(std::ofstream& ofs) const override;
        std::ifstream& load(std::ifstream& ifs) override;
        std::ostream& write(std::ostream& os)const override;
        std::istream& read(std::istream& is)override;
    };
}

#endif // !SDDS_PERISHABLE_H
