#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "essentials.h"
#include "help.h"

using namespace std;

const string p1 = "P1", p2 = "P2";
string currentProperty, currentplayer, status;
string moneyFile = "FILES/" + currentplayer + "Money.csv", propertyFile = "FILES/" + currentplayer + "PropertyFile.csv";
string propertyFile = "FILES/Properties.csv", tempfile = "FILES/TEMPORARY.csv";
string propertyName, numOfHouses, numOfHotels, owner;
fstream money, property, file, tempo;
int housePrice, hotelPrice;
int rolledNum;
string line;
int changeHundred = 0, changeFifty = 0, changeTwenty = 0, changeTen = 0, changeFive = 0, changeOne = 0;

void switchPlayer() {
    if (currentplayer == p1) {
        currentplayer = p2;
    } else if  (currentplayer == p2) {
        currentplayer = p1;
    }
}

bool isOwned(string &propName) {      
   property.open(propertyFile, ios::in);
   if(property.is_open()){
       while (getline(property, line)) {
           Property property = readProperty(line);
           if (property.name == propName && property.owner != "") {
                return true;
                break;
           } else {
                return false;
                break;
           }
       }
       property.close();
   } else {
     fileNotFound();
   }
}

int total (int hundred, int fifty, int twenty, int ten, int five, int one){
    return (hundred * 100) + (fifty * 50) + (twenty * 20) + (ten * 10) + (five * 10) + (one * 1);
}

void printPlayerBalance(int hundred, int fifty, int twenty, int ten, int five, int one) {
    cout << " $100: " << hundred
         << "  $50: " << fifty
         << "  $20: " << twenty
         << "  $10: " << ten
         << "   $1: " << one
         << "  Total: " << total(hundred, fifty, twenty, ten, five, one) << endl;
}

class Banker{
    private:
    int num100, num50, num20, num10, num1;
    int hundred, fifty, twenty, ten, five, one; 
    int pHundred, pFifty, pTwenty, pTen, pFive, pOne;

    public: 
    void bankerGive(int surplus) {
        changeHundred = changeFifty = changeTwenty = changeTen = changeFive = changeOne = 0;
        while (surplus >= 100) {surplus -= 100; changeHundred +=1;}
        while (surplus >= 50) {surplus -= 50; changeFifty += 1;}
        while (surplus >= 20) {surplus -=20; changeTwenty += 1;}
        while (surplus >= 10) {surplus -= 10; changeTen += 1;}
        while (surplus >= 5) {surplus -= 5; changeFive += 1;}
        while (surplus >= 1) {surplus -= 1; changeOne +=1;}   
    }

    void change(int surplus) {
        bankerGive(surplus);

        cout << "Total Change Received From the Banker: " << surplus << endl;
        cout << "Details: " << endl;
        cout << "$100: " << changeHundred;
        cout << " $50: " << changeFifty;
        cout << " $20: " << changeTwenty;
        cout << " $10: " << changeTen;
        cout << "  $5: " << changeFive;
        cout << "  $1: " << changeOne; 
    }

    bool isPlayerLost(string currentPlayer, int due){
        money.open(moneyFile, ios::out);
        if (money.is_open()) {
            getline(money, line);
            Money bills = billToInt(line);
            
            return (total(bills.hundred, bills.fifty, bills.twenty, bills.ten, bills.five, bills.one) < due);

            money.close();
        } else {
            fileNotFound();
        }
    }

    void checkBalance(string &currentplayer){
        money.open(setMoneyFileName(currentplayer), ios::in);
        if (money.is_open()) {
            getline(money, line);
            Money bills = billToInt(line);

            cout << "Balance: " << endl;
            printPlayerBalance(bills.hundred, bills.fifty, bills.twenty, bills.ten, bills.five, bills.one);
            
            money.close();
        } else {
            fileNotFound();
        }
    }

    void enterAmount(){
        do {
            cout << "$100: ";
            cin >> hundred;
            inputFailure();
    
            if (pHundred < hundred) {
                cerr << "Opss... you don't have enough bills.. please try again";
            }
                
        } while (pHundred < hundred);
        
        do {
            cout << "$50: ";
            cin >> fifty;
            inputFailure();
        
            if (pFifty < fifty) {
                cerr << "Opss... you don't have enough bills.. please try again";
            }
                
        } while (pFifty < fifty);
            
        do {
            cout << "$20: ";
            cin >> twenty;
            inputFailure();
        
            if (pTwenty < twenty) {
                cerr << "Opss... you don't have enough bills.. please try again";
            }
                
        } while (pTwenty < twenty);
        
        do {
            cout << "$10: ";
            cin >> ten;
            inputFailure();
        
            if (pTen < ten) {
                cerr << "Opss... you don't have enough bills.. please try again";
            }
                
        } while (pTen < ten);
        
        do {
            cout << "$10: ";
            cin >> five;
            inputFailure();
        
            if (pFive < five) {
                cerr << "Opss... you don't have enough bills.. please try again";
            }
                
        } while (pFive < five);

        do {
            cout << "$1: ";
            cin >> one;
            inputFailure();
    
            if (pOne < one) {
                cerr << "Opss... you don't have enough bills.. please try again";
            }
                
        } while (pOne < one);
    }
    
    void pay(string &currentplayer, int &price) {
        
        if (isPlayerLost(currentplayer, price)) {
            cout << currentplayer << " is bankrupt! Game over." << endl;
            switchPlayer();
            cout  << currentplayer << " won the Game! Way to Go, Tycoon!" << endl;
        }
        
        money.open(setMoneyFileName(currentplayer), ios::in);
        if (money.is_open()){
            getline(money, line);
            Money bills = billToInt(line);

            cout << "Your Current Balance: " << endl;
            checkBalance(currentplayer);
            pHundred = bills.hundred;
            pFifty = bills.fifty;
            pTwenty = bills.twenty;
            pTen = bills.ten;
            pFive = bills.fifty;
            pOne = bills.one;

            money.close();
        } else {
            fileNotFound();
        }

        money.open(setMoneyFileName(currentplayer), ios::out | ios::trunc);
        if (money.is_open()){
            int totalGiven;
            cout << "Practice your Math Skills! Enter the amount of the bill owed to calculate the correct amount." << endl;

            do {
                cout << "Amount Due: $" << price << endl;
                enterAmount();

                if (total(hundred, fifty, twenty, ten, five, one) < price) {
                    cout << "Opss... it looks like your missing some bills to cover your expense. Try Again." << endl;
                }

                totalGiven = total(hundred, fifty, twenty, ten, five, one);
            } while (totalGiven < price);

            cout << "You have given banker: " << endl;
            printPlayerBalance(hundred, fifty, twenty, ten, five, one);

            pHundred -= hundred;
            pFifty -= fifty;
            pTwenty -= twenty;
            pTen -= ten;
            pFive -= five;
            pOne -= one;

            if (totalGiven > price) {
                int surplus = totalGiven - price;
                change(surplus);

                pHundred += changeHundred;
                pFifty += changeFifty;
                pTwenty += changeTwenty;
                pTen += changeTen;
                pFive += changeFive;
                pOne += changeOne;

                if (status == "Buying") {
                    switchPlayer();
                    fstream money2;
                    money2.open(setMoneyFileName(currentplayer), ios::in);
                    if (money2.is_open()) {
                        getline(money2, line);
                        Money bills = billToInt(line);
                        money2.close();
                        bankerGive(price);
                        
                        changeHundred += bills.hundred;
                        changeFifty += bills.fifty;
                        changeTwenty += bills.twenty;
                        changeTen += bills.ten;
                        changeFive += bills.five;
                        changeOne += bills.one;
                        

                        money2.open(setMoneyFileName(currentplayer), ios::out | ios::trunc);
                        money2 << changeHundred << ',' << changeFifty << ',' << changeTwenty << ',' << changeTen << ',' << changeFive << ',' << changeOne << '\n';
                        money2.close();

                        switchPlayer();
                    } else {
                        fileNotFound();
                    }
                }
            }

            money << pHundred << ',' << pFifty << ',' << pTwenty << ',' << pTen << ',' << pFive << ',' << pOne << '\n';
            money.close();
            
            cout << "Current ";
            checkBalance(currentplayer);
        }
    }

    void receiveMoney(int amount) {
        money.open(moneyFile, ios::out | ios::trunc);
        if (money.is_open()) {
            getline(money, line);
            Money bills = billToInt(line);  
            bankerGive(amount);

            changeHundred += bills.hundred;
            changeFifty += bills.fifty;
            changeTwenty += bills.twenty;
            changeTen += bills.ten;
            changeFive += bills.five;
            changeOne += bills.one;

            money << changeHundred << ',' << changeFifty << ',' << changeTwenty << ',' << changeTen << ',' << changeFive << ',' << changeOne << '\n';
            money.close();

            cout << "You recieve $" << amount << " from the bank. Your new balance is: " << endl;
            printPlayerBalance(changeHundred, changeFifty, changeTwenty, changeTen, changeFive, changeOne);
        } else {
            fileNotFound();
        }    
    }

    void giveMoney() {
        money.open(currentplayer, ios::out);
        if (money.is_open()) {
            money << 2 << ',' << 2 << ','  << 6 << ',' << 5  << ',' <<  5 << ',' <<  5 << '\n';
            money.close();
        } else {
            fileNotFound();
        }
        
        switchPlayer();

        money.open(currentplayer, ios::out);
        if (money.is_open()) {
            money << 2 << ',' << 2 << ','  << 6 << ',' << 5  << ',' <<  5 << ',' <<  5 << '\n';
            money.close();
        } else {
            fileNotFound();
        }

        switchPlayer();

        cout << "Each player now has a balance of: " << endl;
        printPlayerBalance(2,2,6,5,5,5);
    }

    void buyAsset(string &name, int &housePrice, int &hotelPrice) {
        char yn;
        cout << "Would you like to purchase some assets to increase the value of your land? [y/n]: ";
        cin >> yn;
        inputFailure();
        
        if (tolower(yn) == 'y') {
            property.open(propertyFile, ios::in);
            tempo.open(tempfile, ios::out);
    
            if (property.is_open() && tempo.is_open()) {
                while (getline(property, line)) {
                    Property property = readProperty(line);
            
                    if (property.name == name && property.owner == currentplayer) {
                        cout << "Current Property Details" << endl;
                        cout << "Number of Houses: " << property.house << endl;
                        cout << "Number of Hotels: " << property.hotel << endl;
                        cout << "Note that you can only upgrade to HOTELS and you must have 4 houses to do so." << endl;
            
                        if (property.house == "4") {
                            char yn;
                            cout << "Would you like to upgrade your house properties into a hotel? [y/n]: ";
                            cin >> yn;
                            inputFailure();
            
                            if (tolower(yn) == 'y') {
                                property.house = "0";
                                int iHotel = stoi(property.hotel);
                                iHotel += 1;
            
                                property.hotel = to_string(iHotel);
                            } else if (tolower(yn) == 'n') {
                                cout << "Make the right investments, " << currentplayer << "!" << endl;
                            }
                        } else {
                            int housesToPurchase;
                            do {
                                cout << "How many houses would you want to purchase: ";
                                cin >> housesToPurchase;
                                inputFailure();
                                
                                if (housesToPurchase > 4 || housesToPurchase <= 0 ||( housesToPurchase + stoi(property.house) < 4)) {
                                    cerr << "Invalid Input. Note that you're limited to have 4 houses for this property." << endl;
                                }
                                
                            } while (housesToPurchase > 4 || housesToPurchase <= 0 ||( housesToPurchase + stoi(property.house) < 4) );
                            
                            int totalDue = housePrice * housesToPurchase;
                            cout << "For  " << housesToPurchase << " house/s. Your total amount due is: $" << totalDue;
                            pay(currentplayer, totalDue); 
                            property.house += housesToPurchase;
                        }
                    }
    
                    tempo << property.name << ',' << property.house << ',' << property.hotel << ',' << property.owner << '\n';
                }
                file.close();
                tempo.close();

                remove(propertyFile.c_str());
                rename(tempfile.c_str(), propertyFile.c_str());
            } else {
                fileNotFound();
            }
        }
    }
};


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
    } else {
        fileNotFound();
    }
}

int rollDice (string currentPlayer){
    char roll;
    do {
        cout << currentPlayer << "Press [r] to roll your dice or [s] to surrender.";
        cin>>roll;
        inputFailure();

        if (tolower(roll) != 'r' || tolower(roll) != 's'){
            cout << "Invalid input, please try again." << endl;
        }
    } while (tolower(roll) != 'r' || tolower(roll) != 's');
    
    if (tolower(roll == 'r')) {
        rolledNum = 0;
        srand(time(0));
        int random = rand() % 6 + 1;
    
        rolledNum = random;
        return random;
    } else if (tolower(roll) == 's'){
        cout << currentPlayer << " surrendered.";
        switchPlayer();
        cout << currentPlayer << " won the game by default.";

        exit(0);
    }
}

void go(){
    propertyName = "go";
    static bool firstTurnP1 = true;
    static bool firstTurnP2 = true;

    if ((currentplayer == p1 && !firstTurnP1) || (currentplayer == p2 && !firstTurnP2)) {
        cout << currentplayer << " landed on or passed GO! Collect $200." << endl;
        string fileName = "FILES/" + currentplayer + "MoneyFile.csv";
        fstream moneyFileStream;
        moneyFileStream.open(fileName, ios::in);
        if (moneyFileStream.is_open()) {
            string line;
            getline(moneyFileStream, line);
            stringstream ss(line);
            int h, f, t, te, o;
            string s100, s50, s20, s10, s1;
            getline(ss, s100, ',');
            getline(ss, s50, ',');
            getline(ss, s20, ',');
            getline(ss, s10, ',');
            getline(ss, s1, ',');
            h = stoi(s100);
            f = stoi(s50);
            t = stoi(s20);
            te = stoi(s10);
            o = stoi(s1);
            moneyFileStream.close();

            h += 2;

            moneyFileStream.open(fileName, ios::out | ios::trunc);
            moneyFileStream << h << ',' << f << ',' << t << ',' << te << ',' << o << '\n';
            moneyFileStream.close();

            cout << currentplayer << "'s new balance: " << endl;
            cout << " $100: " << h << " $50: " << f << " $20: " << t << " $10: " << te << " $1: " << o << endl;
        } else {
            fileNotFound();
        }
    }
    if (currentplayer == p1) firstTurnP1 = false;
    if (currentplayer == p2) firstTurnP2 = false;

    rollDice(currentplayer);
}

class lands{
    private: 
    int numOfHouse, numOfHotel;
    int propertyPrice, baseRent = propertyPrice * 0.1;
    int housePrice, hotelPrice; 

    void handleProperty(const string& propName, int propPrice, int housePrice, int hotelPrice, int baseRent, int houseIncrease, int hotelIncrease) {
        cout << "You're currently on " << propName << endl;
                
        if (!isOwned()) {
            char choice;
            cout << "This property is for sale for $" << propPrice << endl;
            cout << "Would you like to purchase it? [y/n]: ";
            cin >> choice;
            inputFailure();
                    
            if (tolower(choice) == 'y') {
                status = "Buying";
                bank.pay(propPrice);
                cout << "Congrats!, " << currentplayer << ". You now own this land" << endl;
            } else if (tolower(choice) == 'n') {
                cout << "You have missed the chance to own " << propName << endl;
            }
         } else {
            if (owner == currentplayer) {
                bank.buyAsset(propName);
             } else {
                int rent = rentalCost(baseRent, houseIncrease, hotelIncrease);
                cout << propName << " is owned by the other player. Rental cost is " << rent << endl;
                bank.pay(rent);
            }
         }
            switchPlayer();
    }
    
    public:
    Banker bank;
    
    void redFordAvenue() {
        handleProperty("Redford Avenue", 120, 50, 150, 12, 50, 300);
    }
    
    void roseLawnStreet() {
        handleProperty("Roselawn Street", 140, 50, 150, 14, 50, 300);
    }
    
    void greenwichRoad() {
        handleProperty("Greenwich Road", 160, 75, 225, 16, 75, 450);
    }
    
    void gardenCityLane() {
        handleProperty("Garden City Lane", 180, 75, 225, 18, 75, 450);
    }
    
    void blueHarborDrive() {
        handleProperty("Blue Harbor Drive", 200, 100, 300, 20, 100, 600);
    }
    
    void bayviewBoulevard() {
        handleProperty("Bayview Boulevard", 220, 100, 300, 22, 100, 600);
    }
    
    void sunsetStrip() {
        handleProperty("Sunset Strip", 240, 125, 350, 24, 125, 700);
    }

};

class utility : public lands {
    private:
        void handleUtility(const string& utilName, int propertyPrice, int baseRent) {
        cout << "You're currently on " << utilName << endl;
    
        if (!isOwned()) {
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
                cout << "You have missed the chance to own " << utilName << endl;
            }
        } else {
            if (owner == currentplayer) {
                cout << "Welcome to your property!" << endl;
            } else {
                cout << utilName << " is owned by the other player. Rental cost is " << baseRent << endl;
                bank.pay(baseRent);
            }
        }
        switchPlayer();
    }

    public:
    void railRoadStation() {
        handleUtility("Railroad Station", 200, 25);
    }
    
    void waterWorkss() {
        handleUtility("Water Works", 150, rolledNum * 4);
    }
    
    void electricCompany() {
        handleUtility("Electric Company", 150, rolledNum * 4);
    }
    
    void internetProvider() {
        handleUtility("Internet Provider", 150, rolledNum * 4);
    }

    void incomeTax() {
        propertyName = "Income Tax";
        int tax = 200;
    
        cout << "You're currently on " << propertyName << endl;
        cout << "Pay Tax: $" << tax;
    
        status = tax;
        bank.pay(tax);
        
        switchPlayer();
    }

    void jail(string cause) {
        propertyName = "Jail";
        if (cause == "roll" ) {
            cout << currentplayer << " just visiting jail." << endl;
        } else if (cause == "goToJail") {
            cout << currentplayer << " is currently jailed." << endl;
        }
        switchPlayer();
    }

    void goToJail(int &playerPos) {
        string playerlocation = currentplayer + "currentLocation";
        cout << "Your going to jail..." << endl;
        playerlocation = "Jail";
        playerPos = 5; 
        jail("goToJail");        
    }

    void freeParking() {
        propertyName = "Free Parking";
        cout << "You're currently on " << propertyName << endl;

        switchPlayer();
    }
};

class cards : public lands{
    private:
    int amount;
    string chance[3] = {"Speeding fine: pay $15", 
                        "Bank pays you a dividend of $50", 
                        "Pay poor tax of $40"};

    string chest[3] = {"Bank error in your favor: collect $100", 
                       "Holiday fund matures: receive $100", 
                       "Life insurance matures: collect $100"};

    int randomize(){
        int random;
        srand(time(0));
        return random = rand() % 2 + 1;
    }

    public:
    
    void chanceCard(){
        propertyName = "Chance";
        int index = randomize();
        cout << chance[index] << endl;

        if (index == 0) {
            amount = 15;
            bank.pay(amount);
        } else if (index == 1) {
            amount = 50;
            bank.receiveMoney(amount);
        } else if (index == 2) {
            amount = 40;
            bank.pay(amount);
        }
        
        switchPlayer();
    }

    void chestCard(){
        propertyName = "Chest";
        int index = randomize();
        amount = 100;
        cout << chest[index] << endl;
        bank.receiveMoney(amount);
        switchPlayer();
    }
};


#endif
