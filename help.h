#pragma once
#ifndef HELP_H
#define HELP_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//for output formatting
void separation(){
    cout << "+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
}

void breakline(){
    cout << "-------------------------------------------------------------------------------------" << endl;
}

//check for input failute
void inputFailure(){
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
    
        cout << "Invalid input, please try again." << endl;
    }
}

//if file is not found. for uniformity
void fileNotFound(){
    cerr << "File cannot be found." << endl;
}

//to allow the user read the content before clear screen is implemented
void pressEnterToContinue() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

//to print the player's in the middle of the board
int getPlayerTotal(const string& player) {
    ifstream file(player + "Money.csv");
    if (!file.is_open()) return 0;
    int h, f, t, te, fi, o;
    char comma;
    file >> h >> comma >> f >> comma >> t >> comma >> te >> comma >> fi >> comma >> o;
    return h*100 + f*50 + t*20 + te*10 + fi*5 + o*1;
}

//to handle property file
struct Property {
    string name, house, hotel, owner;
    int iHouse, iHotel;
};

//reading contents within Properties.csv
Property readProperty(string &line){
    string name, house, hotel, owner;
    int iHouse = 0, iHotel = 0;
    stringstream ss(line);
    
    getline(ss, name, ',');
    getline(ss, house, ',');
    getline(ss, hotel, ',');
    getline(ss, owner, ',');

    try { iHouse = stoi(house); } catch (...) { iHouse = 0; }
    try { iHotel = stoi(hotel); } catch (...) { iHotel = 0; }

    return {name, house, hotel, owner, iHouse, iHotel};
}

//handle money file and conversion
string setMoneyFileName(string& currentplayer){
    return currentplayer + "Money.csv";
}

struct Money {
    int hundred, fifty, twenty, ten, five, one;
};

//converts integer to int and handles all money related stuff.
Money billToInt(string &line) {
    string s100, s50, s20, s10, s5, s1;
    stringstream ss(line);

    getline(ss, s100, ',');
    getline(ss, s50, ',');
    getline(ss, s20, ',');
    getline(ss, s10, ',');
    getline(ss, s5, ',');
    getline(ss, s1, ',');

    auto safe_stoi = [](const string& s) -> int {
        try {
            return stoi(s);
        } catch (const exception&) {
            return 0;
        }
    };

    return Money{
        safe_stoi(s100),
        safe_stoi(s50),
        safe_stoi(s20),
        safe_stoi(s10),
        safe_stoi(s5),
        safe_stoi(s1)
    };
}

//initializes Properties.csv at the start of the program
void initializePropertiesCSV() {
    vector<string> propertyNames = {
        "Go",
        "Redford Avenue",
        "Community Chest",
        "Railroad Station",
        "Roselawn Street",
        "Jail",
        "Greenwich Road",
        "Income Tax",
        "Garden City Lane",
        "Electric Company",
        "Free Parking",
        "Blue Harbor Drive",
        "Chance",
        "Water Works",
        "Bayview Boulevard",
        "Go to Jail",
        "Chance",
        "Sunset Strip",
        "Internet Provider",
        "Community Chest"
    };

    ofstream file("Properties.csv", ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Could not open Properties.csv for writing." << endl;
        return;
    }

    for (const auto& name : propertyNames) {
        file << name << ",0,0," << endl;
    }
    file.close();
}

#endif // !HELP_

