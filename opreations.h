#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "essentials.h"

using namespace std;

string p1 = "P1", p2 = "P2";
string currentProperty, currentplayer, status;
string moneyFile = "FILES/" + currentplayer + "MoneyFile.csv", propertyFile = "FILES/" + currentplayer + "PropertyFile.csv";
string propertiesDetailFile = "FILES/Properties.csv", tempfile = "TEMPORARY.csv";
string propertyName, numOfHouses, numOfHotels, owner;
fstream money,money2, property, file, tempo;
int housePrice, hotelPrice;

void switchPlayer() {
    if (currentplayer == p1) {
        currentplayer = p2;
    } else if  (currentplayer == p2) {
        currentplayer = p1;
    }
}

bool isOwned() {      
   file.open(propertiesDetailFile, ios::out);
   if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);

            getline(ss, propertyName, ',');
            getline(ss, numOfHouses, ',');
            getline(ss, numOfHotels, ',');
            getline(ss, owner, '\n');
            
            if (currentProperty == propertyName && owner == currentplayer) {
                return true;
            } else if (currentProperty == propertyName && owner != currentplayer) {
                return true;
            } else {
                return false;
            }
        }
        file.close();
    } else {
        cerr << "File cannot be opened or found." << endl;
    }
   
}

int total (int hundred, int fifty, int twenty, int ten, int one){
    return (hundred * 100) + (fifty * 50) + (twenty * 20) + (ten * 10) + (one * 1);
}

class Banker{
    private:
    int num100, num50, num20, num10, num1;

    public: 
    void change(int surplus, int &chundred, int &cfifty, int &ctwenty, int &cten, int &cone) {
        int change = surplus;
        num100 = 0, num50 = 0, num20 = 0, num10 = 0, num1 = 0;
        
        while (surplus >= 100) {
            surplus -= 100;
            num100 += 1;
            chundred +=1;
        }

        while (surplus >= 50) {
            surplus -= 50;
            num50 += 1;
            cfifty += 1;
        }

        while (surplus >= 20) {
            surplus -=20;
            num20 += 1;
            ctwenty += 1;
        }

        while (surplus >= 10) {
            surplus -= 10;
            num10 += 1;
            cten += 1;
        }

        while (surplus >= 1) {
            surplus -= 1;
            num1 += 1;
            cone +=1;
        }    

        cout << "Total Change Received From the Banker: " << change << endl;
        cout << "Breakdown: " << endl;
        cout << "$100: " << num100;
        cout << " $50: " << num50;
        cout << " $20: " << num20;
        cout << " $10: " << num10;
        cout << "  $1: " << num1; 
    }

    private:
    int hundred, fifty, twenty, ten, one; 
    int chundred, cfifty, ctwenty, cten, cone; //currentplayer
    int phundred, pfifty, ptwenty, pten, pone; //payee

    public:
    void enterAmount(){
         do {
                cout << "$100: ";
                cin >> hundred;
                inputFailure();
    
                if (chundred < hundred) {
                    cerr << "Opss... you don't have enough bills.. please try again";
                }
                
            } while (chundred < hundred);
        
            do {
                cout << "$50: ";
                cin >> fifty;
                inputFailure();
        
                if (cfifty < fifty) {
                    cerr << "Opss... you don't have enough bills.. please try again";
                }
                
            } while (cfifty < fifty);
            
            do {
                cout << "$20: ";
                cin >> twenty;
                inputFailure();
        
                if (ctwenty < twenty) {
                    cerr << "Opss... you don't have enough bills.. please try again";
                }
                
            } while (ctwenty < twenty);
        
            do {
                cout << "$10: ";
                cin >> ten;
                inputFailure();
        
                if (cten < ten) {
                    cerr << "Opss... you don't have enough bills.. please try again";
                }
                
            } while (cten < ten);
            
            do {
                cout << "$1: ";
                cin >> one;
                inputFailure();
    
                if (cone < one) {
                    cerr << "Opss... you don't have enough bills.. please try again";
                }
                
            } while (cone < one);
    }
    
    void pay (int price) {      
        money.open(moneyFile, ios::in | ios::out);
        if (money.is_open()){
            string line;
            getline(money, line);
            stringstream ss(line);
            string s100, s50, s20, s10, s1;
            
            getline(ss, s100, ',');
            getline(ss, s50, ',');
            getline(ss, s20, ',');
            getline(ss, s10, ',');
            getline(ss, s1, ',');
            
            chundred = stoi(s100);
            cfifty = stoi(s50);
            ctwenty = stoi(s20);
            cten = stoi(s10);
            cone = stoi(s1);
            
            cout << "Amount Due: $" << price << endl;
            cout << "Practice your math skill! Enter the number of bill you want to give in order to pay for your dues." << endl;
            
            enterAmount();
    
            chundred -= hundred;
            cfifty -= fifty;
            ctwenty -= twenty;
            cten -= ten;
            cone -= one;
    
            int totalGiven = total(hundred, fifty, twenty, ten, one); 
    
            if (totalGiven == price)  {
                /* code */
            } else if (totalGiven > price) {
                int surplus = totalGiven - price;
                if (status == "Buying" || status == "Tax") {
                    change(surplus, chundred, cfifty, ctwenty, cten, cone);
                } else if (status == "Payment") {
                   change(surplus, chundred, cfifty, ctwenty, cten, cone);
                   switchPlayer();
                   money2.open(moneyFile, ios::in);
                   tempo.open(tempfile, ios::out);
                   if (money2.is_open()) {
                        string line;
                        string s2100, s250, s20, s10, s1;
                        getline(money2, line);
                        stringstream ss(line);

                        getline(ss, s2100, ',');
                        getline(ss, s250, ',');
                        getline(ss, s20, ',');
                        getline(ss, s10,',');
                        getline(ss, s1, '\n');

                        phundred = stoi(s2100);
                        pfifty = stoi(s250);
                        ptwenty = stoi(s20);
                        pten = stoi(s10);
                        pone = stoi(s1);
                                
                        phundred += num100;
                        pfifty += num50;
                        ptwenty += num20;
                        pten += num10;
                        pone += num1;   

                        tempo << phundred << ',' << pfifty << ',' << ptwenty << ',' << pten << ',' << pone << '\n';

                        cout << currentplayer << "'s updated funds: " << endl;
                        cout << " $100: " << phundred;
                        cout << "  $50: " << pfifty;
                        cout << "  $20: " << ptwenty;
                        cout << "  $10: " << pten;
                        cout << "   $1: " << pone; 
                        cout << "Total:" << total(phundred, pfifty, ptwenty, pten, pone);

                        money2.close();
                        tempo.close();
                        
                        remove(moneyFile.c_str());
                        rename(tempfile.c_str(), moneyFile.c_str());

                        switchPlayer();
                    }
                }
            }
            
            cout << "Your new balance is: " << endl;
            cout << " $100: " << chundred;
            cout << "  $50: " << cfifty;
            cout << "  $20: " << ctwenty;
            cout << "  $10: " << cten;
            cout << "   $1: " << cone; 
            cout << "Total:" << total(chundred, cfifty, ctwenty, cten, cone);
    
            money.clear();
            money.seekp(0, ios::beg);
    
            money << chundred<< ',' << cfifty<< ',' << ctwenty<< ',' << cten<< ',' << cone<< '\n';
            money.close(); 

        } else {
            cerr << "File cannot be found or does not exist" << endl;
        }
    }
};

void buyasset(string propertyName) {
    Banker bank;
    char yn;
    cout << "Would you like to purchase some assets to increase the value of your land? [y/n]: ";
    cin >> yn;
    inputFailure();
    
    if (tolower(yn) == 'y') {
        file.open(propertiesDetailFile, ios::in);
        tempo.open(tempfile, ios::out);

        if (file.is_open() && tempo.is_open()) {
            string line;
            string name, houses, hotels, owner;
            while (getline(file, line)) {
                stringstream ss(line);
                
                getline(ss, name, ',');
                getline(ss, houses, ',');
                getline(ss, hotels, ',');
                getline(ss, owner, '\n');
        
                if (name == propertyName && owner == currentplayer) {
                    cout << "Number of Houses: " << houses << endl;
                    cout << "Number of Hotels: " << hotels << endl;
                    cout << "Note that you can only upgrade to HOTELS and you must have 4 houses to do so." << endl;
        
                    if (houses == "4") {
                        char yn;
                        cout << "Would you like to upgrade your house properties into a hotel? [y/n]: ";
                        cin >> yn;
                        inputFailure();
        
                        if (tolower(yn) == 'y') {
                            houses = "0";
                            int iHotel = stoi(hotels);
                            iHotel += 1;
        
                            hotels = to_string(iHotel);
                        } else if (tolower(yn) == 'n') {
                            continue;
                        }
                    } else {
                        int housesToPurchase;
                        
                        do {
                            cout << "How many houses would you want to purchase: ";
                            cin >> housesToPurchase;
                            inputFailure();
                            
                            if (housesToPurchase > 4 || housesToPurchase <= 0) {
                                cerr << "Invalid Input. Note that you're limited to have 4 houses for this property." << endl;
                            }
                            
                        } while (housesToPurchase > 4 || housesToPurchase <= 0);
                        
                        int totalDue = housePrice * housesToPurchase;
                        cout << "For  " << housesToPurchase << " house/s. Your total amount due is: $" << totalDue;
                        bank.pay(totalDue); 
                    }
                }

                tempo << name << ',' << houses << ',' << hotels << 'n' << owner << '\n';
                
                file.close();
                tempo.close();

                remove(propertiesDetailFile.c_str());
                rename(tempfile.c_str(), propertiesDetailFile.c_str());
            }
        }
    }
}

int rentalCost(int baseRent, int houseIncrease, int HotelIncrease) {
    file.open(propertiesDetailFile, ios::in) ;
    if (file.is_open()) {
        string line;
        int totalCost;
        string name, houses, hotels, owner;
        while (getline(file, line)) {
            stringstream ss(line);
                
            getline(ss, name, ',');
            getline(ss, houses, ',');
            getline(ss, hotels, ',');
            getline(ss, owner, '\n');

            if (name == propertyName && owner != currentplayer) {
                int iHouse = stoi(houses);
                int iHotel = stoi(hotels);

                return totalCost = baseRent + (iHouse*houseIncrease) + (iHotel*HotelIncrease);
            }
                
        }
    }
}

void redFordAvenue() {
    Banker bank;
    int propertyPrice = 120, baseRent = propertyPrice * 0.1;
    int houseIncrease = 50, hotelIncrease = 300; 
    int numOfHouse, numOfHotel;
    propertyName = "Red Ford Avenue";
    housePrice = 50, hotelPrice = 150;

    cout << "You're currently on Red Ford Avenue" << endl;

    if (isOwned() == false) {
        char choice;
        cout << "This property is for sale for $" << propertyPrice << endl;
        cout << "Would you like to purchase it? [y/n]: ";
        cin >> choice;
        inputFailure();

        if (tolower(choice) == 'y') {
            status = "Buying";
            bank.pay(propertyPrice);
            
            cout << "Congrats!, " << currentplayer << ". You now own this land" << endl;
        } else if (tolower(choice) == 'n') {
            switchPlayer();
        }
    } else if (isOwned()) {
        if (owner == currentplayer) {
            buyasset(propertyName);
        } else {
            cout << propertyName << " is owned by the other player. Rental cost is " << rentalCost(baseRent, houseIncrease, hotelIncrease) << endl;
            bank.pay(rentalCost(baseRent, houseIncrease, housePrice));
        }
    }

    switchPlayer();
}

#endif
