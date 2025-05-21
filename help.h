#pragma once
#ifndef HELP_H
#define HELP_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Property {
    string name, house, hotel, owner;
};

Property readProperty(string &line){
    string name, house, hotel, owner;
    stringstream ss(line);
    
    getline(ss, name, ',');
    getline(ss, house, ',');
    getline(ss, hotel, ',');
    getline(ss, owner, ',');

    return {name, house, hotel, owner};
}

string setMoneyFileName(string& currentplayer){
    return "FILES/" + currentplayer + "Money.csv";
}

struct  Money {
    int hundred, fifty, twenty, ten, five, one;
};

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
        "Sunrise Strip",
        "Internet Provider",
        "Community Chest"
    };

    ofstream file("FILES/Properties.csv", ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Could not open Properties.csv for writing." << endl;
        return;
    }

    for (const auto& name : propertyNames) {
        file << name << ",,," << endl;
    }
    file.close();
}

#endif // !HELP_

