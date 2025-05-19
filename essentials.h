#pragma once
#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <iostream>
using namespace std;

void inputFailure(){
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
    
        cout << "Invalid input, please try again." << endl;
    }
}

#endif

