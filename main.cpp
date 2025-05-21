#include <iostream>
#include "operations.h"
#include "board.h"
//#include "h2p.h"
#include "help.h"
#include "move.h"

using namespace std;

const vector<string> boardTiles = {
    "GO!", "Redford Avenue", "Community Chest", "Railroad Station", "Roselawn Street",
    "Jail", "Greenwich Road", "Income Tax", "Garden City Lane", "Electric Company",
    "Free Parking", "Blue Harbor Drive", "Chance", "Water Works", "Bayview Boulevard", "Go to Jail",
    "Chance", "Sunset Strip", "Internet Provider", "Community Chest", "Railroad Station"
};

int main() {
    const string RESET = "\x1b[0m";
    const string BG_BLACK = "\x1b[40m";
    const string BG_WHITE = "\x1b[107m";
    const string BG_RED = "\x1b[41m";
    
    vector<string> pixelArt = {
        "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
		"RRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWWRRRWWRRWRRRWRWRRR",
		"RRRWWRWWRRWRRWWRWRRWRRRRRWWRWWRWRRWRWWRWRWRRWRWRWRWRRWRWRRRWRWRRR",
		"RRRWRWRWRRWRRWRWWRRWRRWWRWRWRWRWRRWRWRWWRWRRWRWWRRWRRWRWRRRRWRRRR",
		"RRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWRRRRWWRRWWWRRWRRRR",
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
    };

    for (const string& row : pixelArt) {
        for (char c : row) {
            if (c == 'W') cout << BG_WHITE << " " << RESET;
            else if (c == 'B') cout << BG_BLACK << " " << RESET;
            else if (c == 'R') cout << BG_RED << " " << RESET;
            else cout << " ";
        }
        cout << '\n';
    }
    
    int choice;
    
    while (true) {
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "|  Please enter the number of the action you want to perform.   |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "|                     [1] Play Game                             |" << endl;
        cout << "|                     [2] How to Play?                          |" << endl;
        cout << "|                     [3] Exit                                  |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << endl;
    
        do {
            cout << "     Enter Choice (1-3): "; 
            cin >> choice;
            inputFailure();
    
            if (choice < 1 || choice > 3) {
                cout << "Invalid Input, please input a number from 1-3." << endl;
            }
        } while (choice < 1 || choice > 3);
        
    
        if (choice == 1) {
            initializePropertiesCSV();
            int P1Pos = 0, P2Pos = 0, P1CurrentPos = 0, P2CurrentPos = 0;
            Banker bank;
            Main board;
            lands land;
            utility util;
            cards card;
            currentplayer = p1;

            //dri ko nag gamit pointers
            const int initialBills[6] = {2, 2, 6, 5, 5, 5}; 
            bank.giveMoney(&p1, initialBills);
            bank.giveMoney(&p2, initialBills);
            string p1BalanceStr = "$" + to_string(getPlayerTotal("P1"));
            string p2BalanceStr = "$" + to_string(getPlayerTotal("P2"));
            board.drawBoard(p1BalanceStr, p2BalanceStr, currentplayer);

            while (true) {
                if (currentplayer == "P1") {
                    P1Pos = rollDice();
                    int oldPos = P1CurrentPos;
                    P1CurrentPos = (P1CurrentPos + P1Pos) % boardTiles.size();
                    if (P1CurrentPos <= oldPos) {
                        go(currentplayer);
                    }
                } else {
                    P2Pos = rollDice();
                    int oldPos = P2CurrentPos;
                    P2CurrentPos = (P2CurrentPos + P2Pos) % 20;
                    if (P2CurrentPos < oldPos) {
                        go(currentplayer);
                    }
                }
                
                system("cls");
                board.playerPositions[0] = Board::posSpecifier(P1CurrentPos);
                board.playerPositions[1] = Board::posSpecifier(P2CurrentPos);
                string p1BalanceStr = "$" + to_string(getPlayerTotal("P1"));
                string p2BalanceStr = "$" + to_string(getPlayerTotal("P2"));
                board.drawBoard(p1BalanceStr, p2BalanceStr, currentplayer);

                int currentPlayerPos = (currentplayer == "P1") ? P1CurrentPos : P2CurrentPos;
                
                string tile = boardTiles[currentPlayerPos];
                if (tile == "GO!") {
                    go(currentplayer);
                } else if (tile == "Redford Avenue") {
                    land.redFordAvenue();
                } else if (tile == "Community Chest") {
                    card.chestCard();
                } else if (tile == "Railroad Station") {
                    util.railRoadStation();
                } else if (tile == "Roselawn Street") {
                    land.roseLawnStreet();
                } else if (tile == "Jail") {
                    util.jail("roll");
                } else if (tile == "Greenwich Road") {
                    land.greenwichRoad();
                } else if (tile == "Income Tax") {
                    util.incomeTax();
                } else if (tile == "Garden City Lane") {
                    land.gardenCityLane();
                } else if (tile == "Electric Company") {
                    util.electricCompany();
                } else if (tile == "Free Parking") {
                    util.freeParking();
                } else if (tile == "Blue Harbor Drive") {
                    land.blueHarborDrive();
                } else if (tile == "Water Works") {
                    util.waterWorkss();
                } else if (tile == "Bayview Boulevard") {
                    land.bayviewBoulevard();
                } else if (tile == "Go to Jail") {
                    if (currentplayer == "P1") {
                        P1CurrentPos = 5;
                        util.goToJail(P1CurrentPos);
                    } else {
                        P2CurrentPos = 5;
                        util.goToJail(P2CurrentPos);
                    }

                    system("cls");
                    board.playerPositions[0] = Board::posSpecifier(P1CurrentPos);
                    board.playerPositions[1] = Board::posSpecifier(P2CurrentPos);
                    string p1BalanceStr = "$" + to_string(getPlayerTotal("P1"));
                    string p2BalanceStr = "$" + to_string(getPlayerTotal("P2"));
                    board.drawBoard(p1BalanceStr, p2BalanceStr, currentplayer);
                    continue; 
                } else if (tile == "Chance") {
                    card.chanceCard();
                } else if (tile == "Sunset Strip") {
                    land.sunsetStrip();
                } else if (tile == "Internet Provider") {
                    util.internetProvider();
                } else {
                    cout << "Unknown tile!" << endl;
                }
                separation();
                pressEnterToContinue();
                system("cls");
                board.playerPositions[0] = Board::posSpecifier(P1CurrentPos);
                board.playerPositions[1] = Board::posSpecifier(P2CurrentPos);
                p1BalanceStr = "$" + to_string(getPlayerTotal("P1"));
                p2BalanceStr = "$" + to_string(getPlayerTotal("P2"));
                board.drawBoard(p1BalanceStr, p2BalanceStr, currentplayer);
            }
        } else if (choice == 2){
          // HOW ins;
          // ins.showInstructions();
        } else if (choice == 3){
            system("cls");
            cout << "Exiting the game...";
            pressEnterToContinue();
            exit(0);
        }
    } 
}
