#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "essentials.h"

using namespace std;

string p1 = "P1", p2 = "P2";
string currentProperty, currentplayer = p1, status;
string moneyFile = "FILES/" + currentplayer + "Money.csv", propertyFile = "FILES/" + currentplayer + "PropertyFile.csv";
string propertiesDetailFile = "FILES/Properties.csv", tempfile = "TEMPORARY.csv";
string propertyName, numOfHouses, numOfHotels, owner;
fstream money,money2, property, file, tempo;
int housePrice, hotelPrice;
int rolledNum;

void switchPlayer() {
    if (currentplayer == p1) {
        currentplayer = p2;
        cout << currentplayer << "'s turn to play" << endl;
    } else if  (currentplayer == p2) {
        currentplayer = p1;
        cout << currentplayer << "'s turn to play" << endl;
    }
}

bool isOwned() {      
   file.open(propertiesDetailFile, ios::in);
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
        fileNotFound();
    }
}

int total (int hundred, int fifty, int twenty, int ten, int one){
    return (hundred * 100) + (fifty * 50) + (twenty * 20) + (ten * 10) + (one * 1);
}

void printPlayerBalance(int hundred, int fifty, int twenty, int ten, int one) {
    cout << " $100: " << hundred
         << "  $50: " << fifty
         << "  $20: " << twenty
         << "  $10: " << ten
         << "   $1: " << one
         << "  Total: " << total(hundred, fifty, twenty, ten, one) << endl;
}

class Banker{
    private:
    int num100, num50, num20, num10, num1;

    public: 
    void bankerGive(int surplus) {
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
    }

    void change(int surplus, int &chundred, int &cfifty, int &ctwenty, int &cten, int &cone) {
        int change = surplus;
        num100 = 0, num50 = 0, num20 = 0, num10 = 0, num1 = 0;
        
        bankerGive(change);

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
    int chundred, cfifty, ctwenty, cten, cone; 
    int phundred, pfifty, ptwenty, pten, pone; 
    
    public:

    bool isPlayerLost(string currentPlayer, int due){
        money.open(moneyFile, ios::out);
        if (money.is_open()) {
            string line;
            getline(money, line);
            stringstream ss(line);
            string s100, s50, s20, s10, s1;
            
            getline(ss, s100, ',');
            getline(ss, s50, ',');
            getline(ss, s20, ',');
            getline(ss, s10, ',');
            getline(ss, s1, ',');

            int ihundred = stoi(s100);
            int ififty = stoi(s50);
            int itwenty = stoi(s20);
            int iten = stoi(s10);
            int ione = stoi(s1);

            return (total(ihundred, ififty, itwenty, iten, ione) < due);

            money.close();
        } else {
            fileNotFound();
        }
    }

    void checkBalance(string player){
        money.open("FILES/" + player + "Money.csv", ios::in);
        if (money.is_open()) {
            string line, h, f, t, te, o;
           
            getline(money, line);
            stringstream ss(line);
            getline(ss, h, ',');
            getline(ss, f, ',');
            getline(ss, t, ',');
            getline(ss, te, ',');
            getline(ss, o, ',');
            
            int H = stoi(h);
            int F = stoi(f);
            int T = stoi(t);
            int TE = stoi(te);
            int O = stoi(o);

            cout << "Balance: " << endl;
            printPlayerBalance(H, F, T, TE, O);
            
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
        
        if (isPlayerLost(currentplayer, price)) {
            cout << currentplayer << " is bankrupt! Game over." << endl;
            switchPlayer();
            cout  << currentplayer << " won the Game! Way to Go, Tycoon!" << endl;

            exit(0);
        }
              
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

            int totalGiven = total(hundred, fifty, twenty, ten, one);
            
            do {
                cout << "Amount Due: $" << price << endl;
                cout << "Practice your math skill! Enter the number of bill you want to give in order to pay for your dues." << endl;
                enterAmount();

                if (totalGiven < price) {
                    cout << "Opss... it looks like your missing some bills to cover your expense. Try Again." << endl;
                }
                
            } while (totalGiven < price);
            
            chundred -= hundred;
            cfifty -= fifty;
            ctwenty -= twenty;
            cten -= ten;
            cone -= one;
            
            if (totalGiven > price) {
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
                        printPlayerBalance(phundred, pfifty, ptwenty, pten, pone);

                        money2.close();
                        tempo.close();
                        
                        remove(moneyFile.c_str());
                        rename(tempfile.c_str(), moneyFile.c_str());

                        switchPlayer();
                    }
                }
            }
            
            cout << "Your new balance is: " << endl;
            printPlayerBalance(chundred, cfifty, ctwenty, cten, cone);
    
            money.clear();
            money.seekp(0, ios::beg);
    
            money << chundred<< ',' << cfifty<< ',' << ctwenty<< ',' << cten<< ',' << cone<< '\n';
            money.close(); 

        } else {
            fileNotFound();
        }
    }

    void receiveMoney(int amount) {
        money.open(moneyFile, ios::out);
        if (money.is_open()) {
            string line, h, f, t, te, o;
            getline(money, line);
            stringstream ss(line);

            getline(ss, h, ',');
            getline(ss, f, ',');
            getline(ss, t, ',');
            getline(ss, te, ',');
            getline(ss, o, '\n');

            int H = stoi(h);
            int F = stoi(f);
            int T = stoi(t);
            int Te = stoi(te);
            int O = stoi(o);    

            bankerGive(amount);

            money << H << ',' << F << ',' << T << ',' << Te << ',' << O << '\n';

            money.close();

            cout << "You recieve $" << amount << " from the bank. Your new balance is: " << endl;
            printPlayerBalance(H, F, T, Te, O);
        } else {
            fileNotFound();
        }    
    }

    void giveMoney() {
        money.open(currentplayer, ios::out);
        if (money.is_open()) {
            money << 4 << ',' << 1 << ','  << 1 << ',' << 2  << ',' <<  5 << '\n';
            money.close();
        } else {
            fileNotFound();
        }
        
        switchPlayer();

        money.open(currentplayer, ios::out);
        if (money.is_open()) {
            money << 4 << ',' << 1 << ','  << 1 << ',' << 2  << ',' <<  5 << '\n';
            money.close();
        } else {
            fileNotFound();
        }

        switchPlayer();

        cout << "Each player now has a balance of: " << endl;
        printPlayerBalance(4,1,1,2,5);
    }

    void buyAsset(string propertyName) {
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
                                cout << "Make the right investments, " << currentplayer << endl;
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
                            pay(totalDue); 
                        }
                    }
    
                    tempo << name << ',' << houses << ',' << hotels << ',' << owner << '\n';
                }
                file.close();
                tempo.close();

                remove(propertiesDetailFile.c_str());
                rename(tempfile.c_str(), propertiesDetailFile.c_str());
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
        propertyName = propName;
        this->housePrice = housePrice;
        this->hotelPrice = hotelPrice;
                
        cout << "You're currently on " << propertyName << endl;
                
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
                cout << "You have missed the chance to own " << propertyName << endl;
            }
         } else {
            if (owner == currentplayer) {
                bank.buyAsset(propertyName);
             } else {
                int rent = rentalCost(baseRent, houseIncrease, hotelIncrease);
                cout << propertyName << " is owned by the other player. Rental cost is " << rent << endl;
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
    
    void sunriseStrip() {
        handleProperty("Sunrise Strip", 240, 125, 350, 24, 125, 700);
    }

};

class utility : public lands {
    private:
        void handleUtility(
        const string& utilName,
        int propertyPrice,
        int baseRent // For Water Works, Electric Company, Internet Provider, pass rolledNum*4
    ) {
        propertyName = utilName;
        cout << "You're currently on " << propertyName << endl;
    
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
                cout << "You have missed the chance to own " << propertyName << endl;
            }
        } else {
            if (owner == currentplayer) {
                cout << "Welcome to your property!" << endl;
            } else {
                cout << propertyName << " is owned by the other player. Rental cost is " << baseRent << endl;
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
        cout << "Tax: $" << tax;
    
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

    void goToJail() {
        string playerlocation = currentplayer + "currentLocation";
        cout << "Your going to jail..." << endl;
        playerlocation = "Jail";
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
    string chance[3] = {"Speeding fine — pay $15", 
                        "Bank pays you a dividend of $50", 
                        "Pay poor tax of $40"};

    string chest[3] = {"Bank error in your favor — collect $100", 
                       "Holiday fund matures — receive $100", 
                       "Life insurance matures — collect $100"};

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
