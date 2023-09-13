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
            strncpy(m_sku, sku, MAX_SKU_LEN); //use copy 
            setName(name); //use the setName function to set the name
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
        delete[] m_name; //delete the name first
        m_name = nullptr;
        m_sku[0] = 0;
        m_price = 0.0;
        m_taxed = false;
        m_quantity = 0;
        m_displayType = 0;
        m_err.clear(); //clear function
    }
    //assign the value to each member
    void Item::setAll(const char* sku, const char* name, double price, bool taxed, int quantity) {
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
        //if the name is not nullptr and the length of name is more than 0
        if (name != nullptr && strlen(name) > 0) {
            //Dynamic memory allocation
            m_name = new char[(strlen(name)) + 1];
            strcpy(m_name, name);
        }
        else { //otherwise, set the name to nullptr
            m_name = nullptr;
        }
    }
    //Member operator overloads
    //Adds an integer value (right-hand operand) to the quantity and returns the quantity
    int Item::operator+=(int cnt) {
       int sum = m_quantity + cnt;
       //set to MAX_STOCK_NUMBER and the Item error will be set to ERROR_POS_QTY.
       if (sum > MAX_STOCK_NUMBER) {
          m_quantity = MAX_STOCK_NUMBER;
          m_err.message(ERROR_POS_QTY.c_str());
       }
       else { //sum of the value and the quantity exceeds the MAX_STOCK_NUMBER
          m_quantity = sum;
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
    //helper += operator overload
    double& operator+=(double& d, const Item& item) {
       d += item.CQtotal(); //cost() * quantity();
       return d;
    }
    //Returns the opposite of the status of the error attribute. This method does not modify the object.
    Item::operator bool() const {
       return !m_err;
    }
    Item::operator double() const {
       return this->CQtotal(); //cost() * quantity();
    }
    //returns a character as the type indicator of the item in future descendants of the Item -> not modify the object
    char Item::itemType() const {
       return '\0';
    }
    //Receives an integer (POS_LIST or POS_FORM) and sets the corresponding attribute.
    Item& Item::displayType(int value) {
       if (value == POS_LIST || value == POS_FORM) {
          m_displayType = value;
       }
       return *this; //returns the reference
    }
    //the price of the item (plus tax if the item is taxable) -> not modify the object
    double Item::cost() const {
       if (m_taxed) {
          return m_price + (m_price * TAX_RATE);
       }
       else {
          return m_price;
       }
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
    //return the error
    Error& Item::error() {
       return m_err;
    }
    //return the cost() * quantity();
    double Item::CQtotal() const {
        return cost() * quantity();
    }
    //IO
    //write function
    ostream& Item::write(ostream& os) const {
        if (!m_err.isClear()) {
            os << m_err.message();      
        }
        else {
            //If in POS_LIST mode
            if (m_displayType == POS_LIST) {
                string name = m_name;
                os << setw(MAX_SKU_LEN) << left << m_sku << "|";
                os << setw(20) << left << name.substr(0, 20) << "|"; //if longer than 20 characters, only the first 20 will be printed
                os << setw(7) << right << fixed << setprecision(2) << m_price << "|";
                os << " ";
                os << setw(1) << right << (m_taxed ? "X" : "") << " |"; //if true X is printed or else space
                os << setw(4) << right << m_quantity << "|";
                os << setw(9) << fixed << setprecision(2) << CQtotal() << "|";
            }
            //If in POS_FORM mode
            else if (m_displayType == POS_FORM) {
                os << "=============v" << endl;
                os << "Name: " << setw(13) << m_name << endl;
                os << "Sku: " << setw(12) << m_sku << endl;
                os << "Price: " << setw(11) << m_price << endl;
                if (m_taxed) {
                    os << "Price + tax: " << cost() << endl;
                }
                else {
                    os << "Price + tax: " << "N/A" << endl;
                }
                os << "Stock Qty:" << setw(5) << m_quantity << endl;
            }
        }
        return os;
    }
    //save function
    ofstream& Item::save(ofstream& ofs) const {
       //First, the itemType is printed and then all the attributes are saved separated by commas.
       ofs << itemType() << "," << sku() << "," << name() << "," << fixed << setprecision(2) << price() << "," << taxed() << "," << quantity();
       //if it is fail -> show the error message
       if (ofs.fail()) {
          cerr << "Unable to save file";
       }
       return ofs;
    }
    //read function
    istream& Item::read(istream& is) {
        char sku[100];
        char name[100];
        double price = -1;
        char taxed;
        int quantity;
        bool isValid = false;
        m_err.clear();
        //enter the attributs -> SKU, Name, Price, Taxed or not and Quantity.
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
        //check if the value of taxed is validated or not
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
    //load function
    ifstream& Item::load(ifstream& ifs) {
        m_err.clear();  //First, the error status will be cleared
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
        //validate the values one by one and if any of the validation fails,
        if (ifs.fail()) {
            m_err.message("Unable to read data from file");
            return ifs;
        }//check the sku
        if (sku.size() <= 0 || sku.size() > MAX_SKU_LEN) {
            m_err.message(ERROR_POS_SKU.c_str());
            return ifs;
        }//check the name
        if (name.size() <= 0 || name.size() > MAX_NAME_LEN) {
            m_err.message(ERROR_POS_NAME.c_str());
            return ifs;
        }//check the size
        if (price < 0.01) {
            m_err.message(ERROR_POS_PRICE.c_str());
            return ifs;
        }//check the quantity 
        if (quantity <= 0 || quantity > MAX_STOCK_NUMBER) {
            m_err.message(ERROR_POS_QTY.c_str());
            return ifs;
        }       
        setEmpty(); //first set all to be empty
        //set the value
        strncpy(m_sku, sku.c_str(), MAX_SKU_LEN); 
        setName(name.c_str());
        m_price = price;
        m_taxed = taxed;
        m_quantity = quantity;   
        return ifs; //The reference of the ifstream object is returned at the end.
    }
    //The bill print function will only print the Name, taxed price, and if the item is taxed or not
    ostream& Item::bprint(ostream& os) {
       string name = m_name;
       os << "| " << setw(20) << left << name.substr(0, 20) << "|"
          << fixed << setprecision(2) << setw(10) << right << cost() << " | "
          << (taxed() ? " T " : "   ") << " |" << endl; // check the taxed
       return os;
    }
}

