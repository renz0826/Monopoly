#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "help.h"
#include "board.h"
#include "move.h"

using namespace std;

const string p1 = "P1", p2 = "P2";
string currentplayer, status;
string propertyFile = "Properties.csv", tempfile = "TEMPORARY.csv";
string propertyName, owner;
fstream money, property, file, tempo;
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

bool isOwned(const string &propName) {      
   property.open(propertyFile, ios::in);
   if(property.is_open()){
       while (getline(property, line)) {
           Property prop = readProperty(line);
           if (prop.name == propName) {
               owner = prop.owner;                
               property.close();
               return !prop.owner.empty();
           }
       }
       property.close();
       owner = "";
       return false;
   } else {
     fileNotFound();
     return false;
   }
}

int total (int hundred, int fifty, int twenty, int ten, int five, int one){
    return (hundred * 100) + (fifty * 50) + (twenty * 20) + (ten * 10) + (five * 5) + (one * 1);
}

void printPlayerBalance(int hundred, int fifty, int twenty, int ten, int five, int one) {
    cout << "$100: " << hundred << " | "
         << "$50: " << fifty << " | "
         << "$20: " << twenty << " | "
         << "$10: " << ten << " | "
         << "$5: " << five << " | "
         << "$1: " << one << " | " 
         << "Total: " << total(hundred, fifty, twenty, ten, five, one) << " | " <<  endl;
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

    void creditToPlayer(const string& player, int amount) {
        money.open(setMoneyFileName(currentplayer));
        if (money.is_open()){
            getline(money, line);
            Money bills = billToInt(line);
            money.close();
    
            int amt = amount;
            while (amt >= 100) { bills.hundred++; amt -= 100; }
            while (amt >= 50) { bills.fifty++; amt -= 50; }
            while (amt >= 20) { bills.twenty++; amt -= 20; }
            while (amt >= 10) { bills.ten++; amt -= 10; }
            while (amt >= 5) { bills.five++; amt -= 5; }
            while (amt >= 1) { bills.one++; amt -= 1; }
    
            money.open(setMoneyFileName(currentplayer), ios::out | ios::trunc);
            money << bills.hundred << ',' << bills.fifty << ',' << bills.twenty << ',' << bills.ten << ',' << bills.five << ',' << bills.one << '\n';
            money.close();
        }
    }

    void change(int surplus) {
        bankerGive(surplus);
        breakline();
        cout << "Total Change Received From the Banker: " << surplus << endl;
        cout << "Details: " << endl;
        cout << "$100: " << changeHundred;
        cout << " $50: " << changeFifty;
        cout << " $20: " << changeTwenty;
        cout << " $10: " << changeTen;
        cout << "  $5: " << changeFive;
        cout << "  $1: " << changeOne << endl; 
    }

    bool isPlayerLost(string currentPlayer, int due){
        money.open(setMoneyFileName(currentPlayer), ios::in);
        if (money.is_open()) {
            getline(money, line);
            Money bills = billToInt(line);
            
            return (total(bills.hundred, bills.fifty, bills.twenty, bills.ten, bills.five, bills.one) < due);

            money.close();
        } else {
            fileNotFound();
            return false;
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
            cout << "$5: ";
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
            separation();
            cout << currentplayer << " is bankrupt! Game over." << endl;
            switchPlayer();
            cout  << currentplayer << " won the Game! Way to Go, Tycoon!" << endl;
            pressEnterToContinue();
            exit(0);
        }
        
        money.open(setMoneyFileName(currentplayer), ios::in);
        if (money.is_open()){
            getline(money, line);
            Money bills = billToInt(line);
            breakline();
            cout << "Your Current ";
            checkBalance(currentplayer);
            pHundred = bills.hundred;
            pFifty = bills.fifty;
            pTwenty = bills.twenty;
            pTen = bills.ten;
            pFive = bills.five;
            pOne = bills.one;

            money.close();
        } else {
            fileNotFound();
        }

        money.open(setMoneyFileName(currentplayer), ios::out | ios::trunc);
        if (money.is_open()){
            int totalGiven;
            breakline();
            cout << "Practice your Math Skills! Enter the amount of the bill owed to calculate the correct amount." << endl;

            do {
                cout << "Amount Due: $" << price << endl;
                enterAmount();

                if (total(hundred, fifty, twenty, ten, five, one) < price) {
                    cout << "Opss... it looks like your missing some bills to cover your expense. Try Again." << endl;
                    breakline();
                }

                totalGiven = total(hundred, fifty, twenty, ten, five, one);
            } while (totalGiven < price);
            breakline();
            cout << "You have given banker: " << endl;
            printPlayerBalance(hundred, fifty, twenty, ten, five, one);
            pressEnterToContinue();

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

                if (status == "Rent") {
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
            breakline();
        }
    }

    void receiveMoney(int amount) {
        money.open(setMoneyFileName(currentplayer), ios::in);
        if (money.is_open()) {
            getline(money, line);
            Money bills = billToInt(line);
            money.close();

            bankerGive(amount);

            changeHundred += bills.hundred;
            changeFifty += bills.fifty;
            changeTwenty += bills.twenty;
            changeTen += bills.ten;
            changeFive += bills.five;
            changeOne += bills.one;

            money.open(setMoneyFileName(currentplayer), ios::out | ios::trunc);
            money << changeHundred << ',' << changeFifty << ',' << changeTwenty << ',' << changeTen << ',' << changeFive << ',' << changeOne << '\n';
            money.close();

            breakline();
            cout << "You receive $" << amount << " from the bank. Your new balance is: " << endl;
            printPlayerBalance(changeHundred, changeFifty, changeTwenty, changeTen, changeFive, changeOne);
        } else {
            fileNotFound();
        }
    }

    void giveMoney(const string* player, const int* bills) {
        if (!player || !bills) return;
        string fileName = *player + "Money.csv";
        fstream moneyFile(fileName, ios::out | ios::trunc);
        if (moneyFile.is_open()) {
            moneyFile << bills[0] << ',' << bills[1] << ',' << bills[2] << ',' << bills[3] << ',' << bills[4] << ',' << bills[5] << '\n';
            moneyFile.close();
            cout << *player << " now has a balance of: " << endl;
            printPlayerBalance(bills[0], bills[1], bills[2], bills[3], bills[4], bills[5]);
        } else {
            fileNotFound();
        }
    }

    void buyAsset(const string &name, int &housePrice, int &hotelPrice) {
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
                        breakline();
                        cout << "Current Property Details" << endl;
                        cout << "Number of Houses: " << property.house << endl;
                        cout << "Number of Hotels: " << property.hotel << endl;
                        cout << "Note that you can only upgrade to HOTELS and you must have 4 houses to do so." << endl;
                        breakline();
                        if (property.house == "4") {
                            char yn;
                            cout << "Would you like to upgrade your house properties into a hotel? [y/n]: ";
                            cin >> yn;
                            inputFailure();
                            
                            if (tolower(yn) == 'y') {
                                pay(currentplayer,hotelPrice);
                                property.house = "0";
                                int iHotel = property.iHotel;
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
                                
                                if (housesToPurchase > 4 && housesToPurchase <= 0 && ( housesToPurchase + property.iHouse < 4)) {
                                    cerr << "Invalid Input. Note that you're limited to have 4 houses for this property." << endl;
                                }
                                
                            } while (housesToPurchase > 4 && housesToPurchase <= 0 &&( housesToPurchase + property.iHouse < 4) );
                            
                            int totalDue = housePrice * housesToPurchase;
                            cout << "For  " << housesToPurchase << " house/s. Your total amount due is: $" << totalDue << endl;
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
        } else if (tolower(yn) == 'n') {
            cout << "Maybe next time!, " << currentplayer << endl;
        }
    }
};


int rentalCost(const string name, int baseRent, int houseIncrease, int HotelIncrease) {
    property.open(propertyFile, ios::in) ;
    if (property.is_open()) {
        int totalCost;
        while (getline(property, line)) {
            Property property = readProperty(line);

            if (property.name == name && property.owner != currentplayer) {
                return totalCost = baseRent + (property.iHouse*houseIncrease) + (property.iHotel*HotelIncrease);
            }
        }
        property.close();
    } else {
        fileNotFound();
    }
    return 0;
}

int rollDice() {
    char roll;
    do {
        cout << currentplayer << " Press [r] to roll your dice or [s] to surrender.";
        cin>>roll;
        inputFailure();

        if (tolower(roll) != 'r' && tolower(roll) != 's'){
            cout << "Invalid input, please try again." << endl;
        }
    } while (tolower(roll) != 'r' && tolower(roll) != 's');

    if (tolower(roll) == 'r') {
        srand(time(0));
        int random = rand() % 6 + 1;
        rolledNum = random;
        return rolledNum;
    } else if (tolower(roll) == 's') {
        cout << currentplayer << " surrendered." << endl;
        switchPlayer();
        cout << currentplayer << " won the game by default." << endl;
        pressEnterToContinue();
        exit(0);
    }
    return 0;
}

void go(string &currentplayer){
    Banker bank;
    propertyName = "go";

    cout << currentplayer << " landed on or passed GO! Collect $200." << endl;
    money.open(setMoneyFileName(currentplayer), ios::in);
    if (money.is_open()) {
        getline(money, line);
        Money bills = billToInt(line);
        money.close();

        bills.hundred += 2;

        money.open(setMoneyFileName(currentplayer), ios::out | ios::trunc);
        money << bills.hundred << ',' << bills.fifty << ',' << bills.twenty << ',' << bills.ten << ',' << bills.five << ',' << bills.one << '\n';
        money.close();

        cout << "Your Current ";
        bank.checkBalance(currentplayer);

        pressEnterToContinue();

    } else {
        fileNotFound();
    }
}

class lands{
    private:

    void handleProperty(const string& propName, int propPrice, int housePrice, int hotelPrice, int baseRent, int houseIncrease, int hotelIncrease) {
        cout << "You're currently on " << propName << endl;
                
        if (!isOwned(propName)) {
            char choice;
            cout << "This property is for sale for $" << propPrice << endl;
            cout << "Would you like to purchase it? [y/n]: ";
            cin >> choice;
            inputFailure();
                    
            if (tolower(choice) == 'y') {
                bank.pay(currentplayer ,propPrice);

                property.open(propertyFile, ios::in);
                tempo.open(tempfile, ios::out);
                if (property.is_open() && tempo.is_open()){
                   while (getline(property, line)) {
                        Property prop = readProperty(line);
                        if (prop.name == propName) {
                            tempo << prop.name << "," << prop.house << "," << prop.hotel << "," << currentplayer << "\n";
                        } else {
                            tempo << line << "\n";
                        }
                   }
                   property.close();
                   tempo.close();
                   remove(propertyFile.c_str());
                   rename(tempfile.c_str(), propertyFile.c_str());
                }
                cout << "Congrats!, " << currentplayer << ". You now own " << propName << endl;
            } else if (tolower(choice) == 'n') {
                cout << "You have missed the chance to own " << propName << endl;
            }
         } else {
            if (owner == currentplayer) {
                bank.buyAsset(propName, housePrice, hotelPrice);
                cout << "Congrats on your purchase!." << endl;
             } else {
                int rent = rentalCost(propName, baseRent, houseIncrease, hotelIncrease);
                status = "Rent";
                cout << propName << " is owned by the other player. Rental cost is $" << rent << endl;
                bank.pay(currentplayer, rent);
                cout << "Your rival said thanks! :)" << endl;
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
        void handleUtility(const string& utilName, int utilPrice, int baseRent) {
        cout << "You're currently on " << utilName << endl;
    
        if (!isOwned(utilName)) {
            char choice;
            cout << "This property is for sale for $" << utilPrice << endl;
            cout << "Would you like to purchase it? [y/n]: ";
            cin >> choice;
            inputFailure();
    
            if (tolower(choice) == 'y') {
                status = "Buying";
                bank.pay(currentplayer, utilPrice);
                property.open(propertyFile, ios::in);
                tempo.open(tempfile, ios::out);
                if (property.is_open() && tempo.is_open()){
                   while (getline(property, line)) {
                        Property util = readProperty(line);
                        if (util.name == utilName) {
                            tempo << util.name << "," << util.house << "," << util.hotel << "," << currentplayer << "\n";
                        } else {
                            tempo << line << "\n";
                        }
                   }
                   property.close();
                   tempo.close();
                   remove(propertyFile.c_str());
                   rename(tempfile.c_str(), propertyFile.c_str());
                }
                cout << "Congrats!, " << currentplayer << ". You now own " << utilName << endl;
            } else if (tolower(choice) == 'n') {
                cout << "You have missed the chance to own " << utilName << endl;
            }
        } else {
            if (owner == currentplayer) {
                cout << "Welcome to your property!" << endl;
            } else {
                cout << utilName << " is owned by the other player. Rental cost is " << baseRent << endl;
                bank.pay(currentplayer, baseRent);
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
        cout << "Pay Tax: $" << tax << endl;
    
        status = tax;
        bank.pay(currentplayer,tax);

        cout << "Remember to always pay your taxes! :)" << endl;
        
        switchPlayer();
    }

    void jail(string cause) {
        propertyName = "Jail";
        if (cause == "roll" ) {
            cout << currentplayer << " just visiting jail." << endl;
        } else if (cause == "goToJail") {
            cout << currentplayer << " is currently jailed." << endl;
            pressEnterToContinue();
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
        srand(time(0));
        return rand() % 3;
    }

    public:
    
    void chanceCard(){
        propertyName = "Chance";
        int index = randomize();
        cout << chance[index] << endl;

        if (index == 0) {
            amount = 15;
            bank.pay(currentplayer, amount);
        } else if (index == 1) {
            amount = 50;
            bank.receiveMoney(amount);
            breakline();
        } else if (index == 2) {
            amount = 40;
            bank.pay(currentplayer, amount);
        }
        
        cout << "There is more chances waiting for you..." << endl;
        switchPlayer();
    }

    void chestCard(){
        propertyName = "Chest";
        int index = randomize();
        amount = 100;
        cout << chest[index] << endl;
        cout << "Enjoy our gift :)" << endl;
        bank.receiveMoney(amount);
        switchPlayer();
    }
};


#endif
