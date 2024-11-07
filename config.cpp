#include <iostream>
#include "config.h"
using namespace std ; 
  string defaultsort ;       
  string advancesort  ;       
  string searchtechnique  ;  


void initializeConfig() {
      cout << "Enter default sort: ";
      cin >> defaultsort;

      cout << "Enter advanced sort: ";
      cin >> advancesort;

      cout << "Enter search technique: ";
      cin >> searchtechnique;
}
