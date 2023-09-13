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
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <iomanip>
#include <ctype.h>
#include "Item.h"
using namespace std;
namespace sdds {
   //Constructor -> set all member to empty state
    Item::Item() {
        m_sku[0] = 0;
        m_name = nullptr;
        m_price = 0.0;
        m_taxed = false;
        m_quantity = 0;
        m_displayType = 0;
        m_err.clear();
    }
    //Rule of three
    Item::Item(const char* sku, const char* name, double price, bool taxed, int quantity) {
        setEmpty();
        // check the sku and name are empty or not
        if (sku != nullptr && name != nullptr) {
           //copy and set value to each member
            strncpy(m_sku, sku, MAX_SKU_LEN);//use copy 
            setName(name);//use the setName function to set the name
            m_price = price;
            m_taxed = taxed;
            m_quantity = quantity;
        }
    }
    //copy constructor
    Item::Item(const Item& I) {
        setEmpty();
        *this = I;
    }
    //copy assignment operator
    Item& Item::operator=(const Item& I) {
         if (this != &I) {
            //set all member to empty state
            setEmpty();
            strncpy(m_sku, I.m_sku, MAX_SKU_LEN);//use copy 
            setName(I.m_name);//use the setName function to set the name
            m_price = I.m_price;
            m_taxed = I.m_taxed;
            m_quantity = I.m_quantity;
            m_displayType = I.m_displayType;
        }
        return *this;
    }
    //destructor
    Item::~Item() {
        if (m_name != nullptr && strlen(m_name) > 0) {
            delete[] m_name;
        }
        m_name = nullptr;
    }
    //return the sku
    const char* Item::sku() const {
       return m_sku;
    }
    //return the name
    const char* Item::name() const {
       return m_name;
    }
    //return the price
    double Item::price() const {
       return m_price;
    }
    //return the tax
    bool Item::taxed() const {
       return m_taxed;
    }
    //return the quantity
    int Item::quantity() const {
       return m_quantity;
    }
    //Set empty -> set all member to empty state
    void Item::setEmpty() {
        delete[] m_name;//delete the name first
        m_sku[0] = 0;
        m_name = nullptr;
        m_price = 0.0;
        m_taxed = false;
        m_quantity = 0;
        m_displayType = 0;
        m_err.clear();//clear function
    }
    //assign the value to each member
    void Item::set(const char* sku, const char* name, double price, bool taxed, int quantity) {
        strncpy(this->m_sku, sku, MAX_SKU_LEN);//use copy
        this->m_sku[MAX_SKU_LEN] = '\0';
        setName(name);//use setName function
        this->m_price = price;
        this->m_taxed = taxed;
        this->m_quantity = quantity;
    }
    //set the name
    void Item::setName(const char* name) {
       //check if the name is nullptr or not
        if (m_name != nullptr) {
           //if it is not nullptr -> delete the name and set to empty
            delete[] m_name;
            m_name = nullptr;
        }
        //if the name is not nullptr and the length of name is more than 0 -> DMA
        if (name != nullptr && strlen(name) > 0) {
            m_name = new char[(strlen(name)) + 1];
            strcpy(m_name, name);
        }
        else {//otherwise, set the name to nullptr
            m_name = nullptr;
        }
    }
    //Member operator overloads
    //Adds an integer value (right-hand operand) to the quantity and returns the quantity
    int Item::operator+=(int cnt) {
       //set to MAX_STOCK_NUMBER and the Item error will be set to ERROR_POS_QTY.
       int newQuantity = m_quantity + cnt;
       if (newQuantity > MAX_STOCK_NUMBER) {
          m_quantity = MAX_STOCK_NUMBER;
          m_err.message(ERROR_POS_QTY.c_str());
       }
       else {  //sum of the value and the quantity exceeds the MAX_STOCK_NUMBER
          m_quantity = newQuantity;
       }
       return m_quantity;
    }
    //Reduces the quantity by the right-hand value and returns the quantity
    int Item::operator-=(int cnt) {
       //value is more than the quantity -> quantity : zero ,the Item error will be set to ERROR_POS_STOCK
       if (cnt > m_quantity) {
          m_err.message(ERROR_POS_STOCK.c_str());
          m_quantity = 0;
       }
       else {
          m_quantity -= cnt;
       }
       return m_quantity;
    }
    //Returns the opposite of the status of the error attribute. This method does not modify the object.
    Item::operator bool() const {
       return !m_err;
    }
    //helper += operator overload
    double& operator+=(double& d, const Item& item) {
       d += item.CQtotal(); //cost() * quantity();
       return d;
    }
    //Compares an Item to a C-string and returns true if the C-sting is a match to the SKU code of the Item.
    bool Item::operator==(const char* sku) const {
       return strcmp(this->m_sku, sku) == 0;
    }
    //Compares two items alphabetically based on their names.
    bool Item::operator>(const Item& other) const {
       if ((this->name() != nullptr) && other.m_name != nullptr) {
          if (strcmp(this->m_name, other.m_name) > 0) {
             return true;
          }
       }
       return false;
    }
    //the price of the item (plus tax if the item is taxable) -> not modify the object
    double Item::cost() const {
        if (m_taxed) {
            return m_price + (m_price * TAX_RATE);
        } else {
            return m_price;
        }
    }
    //return the cost() * quantity();
    double Item::CQtotal() const {
        return cost() * quantity();
    }
    //return the error
    Error& Item::error() {
        return m_err;
    }
    //check is it clear
    bool Item::isClear() const {
        return m_err.isClear();
    }
    //Clears the error status of the object
    Item& Item::clear() {
        m_err.clear();
        return *this;
    }
    //Receives an integer (POS_LIST or POS_FORM) and sets the corresponding attribute.
    Item& Item::displayType(int value) {
        if (value == POS_LIST || value == POS_FORM) {
            m_displayType = value; 
        }
        return *this;//returns the reference
    }
    Item::operator double() const {
        return this->CQtotal();//cost() * quantity();
    }
    //returns a character as the type indicator of the item in future descendants of the Item -> not modify the object
    char Item::itemType() const {
        return '\0';
    }
    //write
    ostream& Item::write(ostream& os) const {
        if (!m_err.isClear()) {
            os << m_err.message();     
        }
        else {
            if (m_displayType == POS_LIST) {
                string name = m_name;
                os << setfill(' ');
                os << setw(MAX_SKU_LEN) << left << m_sku << "|";
                os << setw(20) << left << name.substr(0, 20) << "|";
                os << setw(7) << right << fixed << setprecision(2) << m_price << "|";
                os << " ";
                os << setw(1) << right << (m_taxed ? "X" : "") << " |";
                os << setw(4) << right << m_quantity << "|";
                os << setw(9) << fixed << setprecision(2) << CQtotal() << "|";
            }
            else if (m_displayType == POS_FORM) {
                os << "=============v" << endl;
                os << setfill(' ');
                os << left << setw(13) << "Name:" << m_name << endl;
                os << left << setw(13) << "Sku:" << m_sku << endl;
                os << left << setw(13) << "Price:"  << m_price << endl;
                if (m_taxed) {
                    os << left << setw(13) << "Price + tax:" << cost() << endl;
                }
                else {
                    os << left << setw(13) << "Price + tax:" << "N/A" << endl;
                }
                os << left << setw(13) << "Stock Qty:" << m_quantity << endl;
            }
        }
        os.unsetf(ios::right);
        os.unsetf(ios::left);
        return os;
    }
    //read 
    istream& Item::read(istream& is) {
        char sku[100];
        char name[100];
        double price = -1;
        char taxed;
        int quantity;
        bool isValid = false;
        m_err.clear();
        //check if the value of sku is validated or not
        cout << "Sku";
        do {
            cout << "\n" << "> ";
            is.getline(sku, sizeof(sku), '\n');
            if (strlen(sku) > MAX_SKU_LEN) {
                cout << ERROR_POS_SKU;
            }
            else {
                isValid = true;
                strcpy(m_sku, sku);
            }
        } while (!isValid || is.fail());
        //check if the value of name is validated or not
        isValid = false;
        cout << "Name";
        do {
            cout << "\n" << "> ";
            is.getline(name, sizeof(name), '\n');      
            if (strlen(name) > MAX_NAME_LEN) {
                cout << ERROR_POS_NAME;
            }
            else {
                isValid = true;
                m_name = new char[strlen(name) + 1];
                strcpy(m_name, name);
            }
        } while (!isValid || is.fail());
        //check if the value of price is validated or not
        isValid = false;
        cout << "Price";
        do {
            cout << "\n" << "> ";
            is >> price;
            if (is.fail()) {
                cout << ERROR_POS_PRICE;
                is.clear();
                is.ignore(1000, '\n');
            }
            else if (price < 0) {
                cout << ERROR_POS_PRICE;
            }
            else {
                isValid = true;
                m_price = price;
            }
        } while (!isValid || is.fail());
        //check if the value of tax is validated or not
        isValid = false;
        cout << "Taxed?" << "\n" << "(Y)es/(N)o: ";
        do {
            is >> taxed;
            if (taxed != 'y' && taxed != 'Y' && taxed != 'n' && taxed != 'N') {
                cout << "Only 'y' and 'n' are acceptable: ";
                is.clear();
                is.ignore(1000, '\n');
            }
            else {
                isValid = true;
                if (toupper(taxed) == 'Y') {
                    m_taxed = true;
                }
                else {
                    m_taxed = false;
                }
            }
        } while (!isValid || is.fail());
        //check if the value of quantity is validated or not
        isValid = false;
        cout << "Quantity";
        do {
            cout << "\n" << "> ";
            is >> quantity;

            if (is.fail()) {
                cout << ERROR_POS_QTY;
                is.clear();
                is.ignore(1000, '\n');
            }
            else if (quantity < 1 || quantity > 99) {
                cout << ERROR_POS_QTY;
            }
            else {
                isValid = true;
                m_quantity = quantity;
            }
        } while (!isValid || is.fail());
        return is;
    }
    //save
    ofstream& Item::save(ofstream& ofs) const {
        ofs << itemType() << "," << sku() << "," << name() << "," << fixed << setprecision(2) << price() << "," << taxed() << "," << quantity();
        if (ofs.fail()) {
            cerr << "Unable to save file";
        }
        return ofs;
    }
    //load
    ifstream& Item::load(ifstream& ifs) {
        m_err.clear();       
        string sku = "";
        string name = "";
        double price = 0;
        int quantity = 0;
        bool taxed = false;
        char delimeter = '\0';
        getline(ifs, sku, ',');
        getline(ifs, name, ',');
        ifs >> price;
        ifs >> delimeter;
        ifs >> taxed;
        ifs >> delimeter;
        ifs >> quantity;
        //if input is fail
        if (ifs.fail()) {
            m_err.message("Unable to read data from file");
            return ifs;
        }
        //check sku
        if (sku.size() <= 0 || sku.size() > MAX_SKU_LEN) {
            m_err.message(ERROR_POS_SKU.c_str());
            return ifs;
        }
        //check name
        if (name.size() <= 0 || name.size() > MAX_NAME_LEN) {
            m_err.message(ERROR_POS_NAME.c_str());
            return ifs;
        }
        //check price
        if (price < 0.01) {
            m_err.message(ERROR_POS_PRICE.c_str());
            return ifs;
        }
        //check quantity
        if (quantity <= 0 || quantity > MAX_STOCK_NUMBER) {
            m_err.message(ERROR_POS_QTY.c_str());
            return ifs;
        }
        //set empty -> DMA
        setEmpty();
        strncpy(m_sku, sku.c_str(), MAX_SKU_LEN);
        setName(name.c_str());
        m_price = price;
        m_taxed = taxed;
        m_quantity = quantity;       
        return ifs;
    }
    //The bill print function will only print the Name, taxed price, and if the item is taxed or not
    ostream& Item::bprint(ostream& os) {
       string name = m_name;
       os << "| " << setw(20) << left << name.substr(0, 20) << "|"
          << fixed << setprecision(2) << setw(10) << right << cost() << " | "
          << (taxed() ? " T " : "   ") << " |" << endl;
       return os;
    }
}

