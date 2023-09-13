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
#ifndef SDDS_POS_H
#define SDDS_POS_H
#include <string>
using namespace std;
namespace sdds {
    const double TAX_RATE = 0.13;
    const int MAX_SKU_LEN = 7;
    const int MIN_YEAR = 2000;
    const int MAX_YEAR = 2030;
    const int MAX_STOCK_NUMBER = 99;
    const int MAX_NO_ITEMS = 2000;
    const int MAX_NAME_LEN = 40;
    const int POS_LIST = 1;
    const int POS_FORM = 2;
    const string ERROR_POS_SKU = "SKU too long";
    const string ERROR_POS_NAME = "Item name too long";
    const string ERROR_POS_PRICE = "Invalid price value";
    const string ERROR_POS_TAX = "Invalid tax status";
    const string ERROR_POS_QTY = "Invalid quantity value";
    const string ERROR_POS_STOCK = "Item out of stock";
    const string ERROR_POS_EMPTY = "Invalid Empty Item";
}
#endif

