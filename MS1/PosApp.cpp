// Final Project Milestone 1
// Student POS App Mockup tester
// Version 1.0
// Date	2023-03-15
// Author	Ching Wei Lai
// Description
// This program test the student implementation of the PosApp class
// for submission.
//
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "PosApp.h"


using namespace std;
namespace sdds {

   PosApp::PosApp(const char* name) {
      strncpy(filename, name, 255);
      filename[255] = '\0';
   }

   int PosApp::menu() {
      int num;
      bool flag = false;
      cout << "The Sene-Store" << endl;
      cout << "1- List items" << endl;
      cout << "2- Add item" << endl;
      cout << "3- Remove item" << endl;
      cout << "4- Stock item" << endl;
      cout << "5- Point of Sale" << endl;
      cout << "0- exit program" << endl;
      cout << "> ";
      while (!flag) {
         if (cin >> num) {
            if (num < 0 || num > 5) {
               cout << "[0<=value<=5], retry: > ";
            }
            else {
               flag = true;
            }
         }
         else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Integer, try again: ";
         }
      }
      return num;
   }

   bool PosApp::load() {
      int itemCount = 0;
      char* items = nullptr;

      int numbersRead = 0;
      if (itemCount > 0) {
         //DMA
         items = new char[itemCount];
         ifstream file;
         file.open(filename);

         if (file.is_open()) {
            int i = 0;
            // check i is less than the total number of item from the file we read  and read the item form the file
            while (i < itemCount && file >> items[i]) {
               numbersRead++;
               i++;
            }
            file.close(); //close the file after read it
         }
         //if we cannot read the file, deallocate the memory
         else {
            delete[] items;
            items = nullptr;
         }
      }
      bool success = (numbersRead == itemCount);
      if (!success) { //just in case
         delete[] items;
         items = nullptr;
      }
      return success;
   }

   void PosApp::addItem() {
      cout << ">>>> Adding Item to the store................................................" << endl;
      cout << "Running addItem()" << endl;

   }

   void PosApp::removeItem() {
      cout << ">>>> Remove Item............................................................." << endl;
      cout << "Running removeItem()" << endl;
   }

   void PosApp::stockItem() {
      cout << ">>>> Select an item to stock................................................." << endl;
      cout << "Running stockItem()" << endl;
   }

   void PosApp::listItems() const {
      cout << ">>>> Listing Items..........................................................." << endl;
      cout << "Running listItems()" << endl;
   }

   void PosApp::POS() const {
      cout << ">>>> Starting Point of Sale.................................................." << endl;
      cout << "Running POS()" << endl;
   }

   void PosApp::saveRecs() const {
      cout << ">>>> Saving Data............................................................." << endl;
      cout << "Saving data in " << filename << endl;
   }

   void PosApp::loadRecs() {
      cout << ">>>> Loading Items..........................................................." << endl;
      if (!load()) {
         cout << "Error!!" << endl;
      }
      else {
         cout << "Loading data from " << filename << endl;
      }
   }

   void PosApp::run() {
      loadRecs();
      int num = -1;
      while (num != 0) {
         num = menu();
         switch (num) {
         case 1:
            listItems();
            break;
         case 2:
            addItem();
            break;
         case 3:
            removeItem();
            break;
         case 4:
            stockItem();
            break;
         case 5:
            POS();
            break;
         case 0:
            break;
         default:
            cout << "Invalid choice, try again..." << endl;
            break;
         }
      }
      saveRecs();
      cout << "Goodbye!" << endl;
   }

}
