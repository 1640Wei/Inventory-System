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
#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H
#include "Item.h"
namespace sdds {
    class NonPerishable : public Item {
    public:
        //override the virtual functions
        char itemType() const override;
        std::ostream& write(std::ostream& os) const override;
    };
} 
#endif // SDDS_NONPERISHABLE_H