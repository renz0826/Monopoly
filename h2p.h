#ifndef H2P_H
#define H2P_H

#include <iostream>
#include <limits> 
#include <windows.h> 
#include <cstdlib>  
#include <sstream>
#include <vector>
#include <cctype> //for toupper
#include "colors.h"

using namespace std;

class HOW{
    public: 
        //function to clear the console screen
        void clearScreen() {
            system("cls");
        }
        
        //function to pause and wait for user input
        void pauseScreen() {
            cout << "Press enter to go back [>]"; //enter lang ni
            cin.ignore();
            cin.get();
        }
        
        //function to display a specific instruction page
        void displayInstructionPage(const string& pageContent) {
            clearScreen();
            cout << pageContent << endl;
            pauseScreen();
        }
        
        
        // Function to display the instructions menu and handle user choice
        void showInstructions() {
            vector<string> sections;
            sections.push_back("Setup");
            sections.push_back("Taking Turns");
            sections.push_back("Resolving Your Landing");
            sections.push_back("Building Upgrades");
            sections.push_back("Jail Rules");
            sections.push_back("Bankruptcy & Winning");
            sections.push_back("Return to Main Menu");
            
            Colors c;

            vector<string> pages;
        
            // Page 1: Game Setup
            string page1 = string("--------------------------------------------------\n")
                + c.w + "|                   GAME SETUP                   |" + c.re + "\n"
                + "--------------------------------------------------\n"
                + "+------------------------------------------------+\n"
                + "| " + c.marker + " Each player is assigned a token            |\n"
                + "| " + "    and it is automatically placed on [GO!].   |\n"
                + "|                                                |\n"
                + "| " + c.dollar + " Starting cash: $500                          |\n"
                + "| " + "  |__ 2 x $100                                 |\n"
                + "| " + "  |____ 2 x $50                                |\n"
                + "| " + "  |______ 6 x $20                              |\n"
                + "| " + "  |________ 5 x $10                            |\n"
                + "| " + "  |__________ 5 x $5                           |\n"
                + "| " + "  |____________ 5 x $1                         |\n"
                + "|                                                |\n"
                + "| " + c.c_cc + " Chance & Community Chest Cards           |\n"
                + "| " + "      |____ [Shuffled and Ready]               |\n"
                + "|                                                |\n"
                + "+------------------------------------------------+\n";
        
            pages.push_back(page1);
        
            // Page 2: Taking Turns
            string page2 = string("----------------------------------------------------\n")
                + c.w + "|                   TAKING TURNS                   |" + c.re + "\n"
                + "----------------------------------------------------\n"
                + "+--------------------------------------------------+\n"
                + "| " + c.turn + " On your turn, roll a die and move your token   |\n"
                + "|   forward that many spaces, wrapping around      |\n"
                + "|   past space 19 and returning to [GO!].          |\n"
                + "|                                                  |\n"
                + "| " + c.turn + " If you pass or land on [GO!], collect $200     |\n"
                + "|   immediately.                                   |\n"
                + "|                                                  |\n"
                + "+--------------------------------------------------+\n";
        
            pages.push_back(page2);
        
            // Page 3: Resolving Your Landing
            string page3 = string("-------------------------------------------------------\n")
                + c.w + "|               RESOLVING YOUR LANDING                |" + c.re + "\n"
                + "-------------------------------------------------------\n"
                + "+-----------------------------------------------------+\n"
                + "| " + c.util + " Unowned Property / Utility / Railroad:            |\n"
                + "|   |____You may choose to buy it for its listed      |\n"
                + "|        price or decline.                            |\n"
                + "|                                                     |\n"
                + "| " + c.owned + " Owned by Opponent:                                |\n"
                + "|   |____Pay the owner the appropriate rent or        |\n"
                + "|        utility fee.                                 |\n"
                + "|                                                     |\n"
                + "| " + c.tax + " Income Tax:                                      |\n"
                + "|    |____Pay $200 to the bank.                       |\n"
                + "|                                                     |\n"
                + "| " + c.c_cc + " Chance / Community Chest:                     |\n"
                + "|       |____Read it and apply its effect.            |\n"
                + "|                                                     |\n"
                + "| " + c.jail + " Go to Jail:                                   |\n"
                + "|       |____Move directly to the Jail space.         |\n"
                + "|                                                     |\n"
                + "| " + c.free + " Jail (Just Visiting) / Free Parking:              |\n"
                + "|   |____No action required.                          |\n"
                + "|                                                     |\n"
                + "+-----------------------------------------------------+\n";
        
            pages.push_back(page3);
        
            // Page 4: Building Upgrades
            string page4 = string("---------------------------------------------------------\n")
                + c.w + "|        BUILDING UPGRADES (OPTIONAL AFTER MOVE)        |" + c.re + "\n"
                + "---------------------------------------------------------\n"
                + "+-------------------------------------------------------+\n"
                + "| " + c.owned + " If you own both properties of a color group,        |\n"
                + "|   you may build on them once per turn.                |\n"
                + "|   |____House Costs:                                   |\n"
                + "|         " + c.houser + " Red group:    $50 each                      |\n"
                + "|         " + c.houseg + " Green group:  $75 each                      |\n"
                + "|         " + c.houseb + " Blue group:   $100 each                     |\n"
                + "|         " + c.housey + " Yellow group: $120 each                     |\n"
                + "|                                                       |\n"
                + "| " + c.property + " You can place up to 4 houses on each property;      |\n"
                + "|   each house raises that property's rent by its       |\n"
                + "|   build cost.                                         |\n"
                + "|                                                       |\n"
                + "| " + c.property + " Once there are 4 houses, trade them for a hotel:    |\n"
                + "|   |____Hotel Costs:                                   |\n"
                + "|         " + c.houser + " Red:    $150                                |\n"
                + "|         " + c.houseg + " Green:  $225                                |\n"
                + "|         " + c.houseb + " Blue:   $300                                |\n"
                + "|         " + c.housey + " Yellow: $350                                |\n"
                + "|                                                       |\n"
                + "| " + c.property + " A hotel replaces all houses and sets rent           |\n"
                + "|   to the flat hotel rate.                             |\n"
                + "|                                                       |\n"
                + "+-------------------------------------------------------+\n";
        
            pages.push_back(page4);
        
            // Page 5: Jail Rules
            string page5 = string("----------------------------------------------------------\n")
                + c.w + "|                       JAIL RULES                       |" + c.re + "\n"
                + "----------------------------------------------------------\n"
                + "+--------------------------------------------------------+\n"
                + "| " + c.jail + " If you land on 'Go to Jail', you will            |\n"
                + "|       return to the Jail space.                        |\n"
                + "|                                                        |\n"
                + "| " + c.go + " After leaving jail, roll the dice to move as      |\n"
                + "|      usual.                                            |\n"
                + "|                                                        |\n"
                + "+--------------------------------------------------------+\n";
        
            pages.push_back(page5);
        
            // Page 6: Bankruptcy & Winning
            string page6 = string("------------------------------------------------------\n")
                + c.w + "|                BANKRUPTCY & WINNING                |" + c.re + "\n"
                + "------------------------------------------------------\n"
                + "+----------------------------------------------------+\n"
                + "| " + c.bankrupt + " If you owe more than you can pay, you are      |\n"
                + "|     bankrupt and immediately lose.                 |\n"
                + "|                                                    |\n"
                + "| " + c.free + " The game does not have a mortgage system.        |\n"
                + "|                                                    |\n"
                + "| " + c.win + " The player with a non-negative balance wins.   |\n"
                + "|                                                    |\n"
                + "+----------------------------------------------------+\n";
        
            pages.push_back(page6);
        
            cout << "+---------------------------------------------------------------+\n";
            cout << "|                     GAME INSTRUCTIONS                         |\n";
            cout << "+---------------------------------------------------------------+\n";
            cout << "|    Please enter the number of the section you want to read.   |\n";
            cout << "+---------------------------------------------------------------+\n";
        
            const int totalWidth = 65;           // Total width including borders
            const int innerWidth = totalWidth - 2; // Inner width (excluding the border characters)
            const int leftMargin = 8;
        
            // Loop through the sections, applying the custom left margin
            for (size_t i = 0; i < sections.size(); ++i) {
                ostringstream oss;
                oss << "[" << (i + 1) << "] " << sections[i];
                string content = oss.str();
                
                // Ensure the content fits in the available space after the left margin
                if (content.length() > (innerWidth - leftMargin)) {
                    content = content.substr(0, innerWidth - leftMargin);
                }
                
                // Build the line with the custom left margin
                string line = string(leftMargin, ' ') + content;
                
                // Pad the remainder of the line with spaces so the total is innerWidth
                if (line.length() < innerWidth) {
                    line.append(innerWidth - line.length(), ' ');
                }
                
                cout << "|" << line << "|" << "\n";
            }
            
            // Print the bottom border
            cout << "+" << string(innerWidth, '-') << "+" << "\n";
        
            char choice = '\0';
        
            while (true) {
                cout << "\nEnter choice (1-7): ";
                // Read one non-whitespace character
                if (!(cin >> choice)) {
                    // Something went wrong with cin itself
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout <<" Input error. Please try again.\n";
                    continue;
                }
                // Discard the rest of the line (extra chars)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
                // Validate: must be between '1' and '7'
                if (choice >= '1' && choice <= '7') {
                    break;
                } else {
                    cout << "\nInvalid choice. Please enter a single digit from 1 to 7.\n";
                }
            }
        
        
            try {
                int idx = choice - '1';  // convert to 0-based
                if (idx < (int)pages.size()) {
                    if (choice == '7') {
                        cout << string(leftMargin, ' ') << "\nReturning to the main menu...\n";
                    } else {
                        displayInstructionPage(pages[idx]);
                        showInstructions();  // back to menu
                    }
                }
            } catch (const exception &ex) {
                // Fallback in case something unexpected happened
                cout <<  string(leftMargin, ' ') <<" An unexpected error occurred: " << ex.what() << "\n";
                pauseScreen();
            }
        }  
};

#endif // H2P_H
