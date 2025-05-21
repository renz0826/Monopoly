#pragma once
#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <iostream>
#include <vector>
#include <string>
#include "operations.h"
using namespace std;

void inputFailure(){
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
    
        cout << "Invalid input, please try again." << endl;
    }
}

void fileNotFound(){
    cerr << "File cannot be found." << endl;
}

#endif

