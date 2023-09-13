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
#ifndef _POSAPP_H_
#define _POSAPP_H_

namespace sdds {
   class PosApp {
      char filename[256];
      int itemCount;
      char* items;     
      int menu();
      void addItem();
      void removeItem();
      void stockItem();
      void listItems() const;
      void POS() const;
      void saveRecs() const;
      void loadRecs();
      bool load();
      
   public:
      PosApp(const char* name);
      PosApp(const PosApp& other) = delete;
      PosApp& operator=(const PosApp& other) = delete;
      void run();
   };

}

#endif