#include <iostream>
#include "config.h"

std::string defaultsort ;       
std::string advancesort  ;       
std::string searchtechnique  ;  


void initializeConfig() {
    std::cout << "Enter default sort: ";
    std::cin >> defaultsort;

    std::cout << "Enter advanced sort: ";
    std::cin >> advancesort;

    std::cout << "Enter search technique: ";
    std::cin >> searchtechnique;
}
