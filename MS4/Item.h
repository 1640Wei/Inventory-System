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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iomanip>
#include <iostream>
#include "Error.h"
#include "PosIO.h"
#include "POS.h"
namespace sdds {
    class Item : public PosIO {
           char m_sku[MAX_SKU_LEN + 1]; //an SKU code up to MAX_SKU_LEN characters.
           char* m_name; //A dynamically allocated C-string to keep the name of the Item up to MAX_NAME_LEN characters.
           double m_price; //A double value
           bool m_taxed; //A boolean
           int m_quantity; //An integer value for the stock number of the Item
        protected:
           int m_displayType; //An integer flag that can be either POS_LIST or POS_FORM
           Error m_err; //An Error object to keep the error status of the Item.
    public:
       //Constructor
        Item();
        //Rule of three
        Item(const char* sku, const char* name, double price, bool taxed = true, int quantity = 0);
        Item(const Item& I);
        Item& operator=(const Item& I);
        //Destructor
        ~Item();
        //returm the value of member 
        const char* sku() const;
        const char* name() const;
        double price() const;
        bool taxed() const;
        int quantity() const;
        //displayType
        Item& displayType(int value);
        //set member to empty state
        void setEmpty();
        //set the value
        void set(const char* sku, const char* name, double price, bool taxed, int quantity);
        //set the name
        void setName(const char* name);
        //Member operator overloads
        int operator+=(int cnt);
        int operator-=(int cnt);
        bool operator==(const char* sku) const;
        bool operator>(const Item& other) const;
        operator bool() const;
        operator double() const;
        //Member function (Methods)
        //itemType -> pure virtual method
        virtual char itemType() const = 0;
        //cost query
        double cost() const;
        //check error
        Error& error();
        //clear
        bool isClear() const;
        Item& clear();
        double CQtotal() const;
        //IO
        //write
        std::ostream& write(std::ostream& os) const override;
        //read
        std::istream& read(std::istream& is) override;
        //save
        std::ofstream& save(std::ofstream& ofs) const override;
        //load
        std::ifstream& load(std::ifstream& ifs) override;
        //print the bill
        std::ostream& bprint(std::ostream& os);
    };
    //helper += operator overload
    double& operator+=(double& d, const Item& item);
}
#endif // SDDS_ITEM_H
