#pragma once

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <limits> 
#include <cstdlib>  
#include <vector>
#include <cctype> 
using namespace std;

//functions
void showInstructions();
void clearScreen(); 
void pauseScreen();   

//function to clear the console screen
void clearScreen() {
    system("cls");
}

//function to pause and wait for user input
void pauseScreen() {
    cout << "Continue [>]"; //enter lang ni
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
    vector<string> sections = {
        "Setup",
        "Taking Turns",
        "Resolving Your Landing",
        "Building Upgrades",
        "Jail Rules",
        "Bankruptcy & Winning",
        "Return to Main Menu"
    };
    vector<string> pages = {
        R"(
===== Setup =====
  - Each player chooses a token and places it on Go.
  - Each begins with $500 in bills:
    - 4 x $100
    - 1 x $50
    - 1 x $20
    - 2 x $10
    - 5 x $1
  - The Chance and Community Chest Cards will be shuffled.
)",
        R"(
===== Taking Turns =====
  - On your turn, roll a die and move your token forward that many spaces,
    wrapping around past space 17 back to Go.
  - If you pass or land on Go, collect $200 immediately.
)",
        R"(
===== Resolving Your Landing =====
  - Unowned Property / Utility / Railroad:
    - You may choose to buy it for its listed price or decline.
  - Owned by Opponent:
    - Pay the owner the appropriate rent or utility fee.
  - Income Tax:
    - Pay $200 to the bank.
  - Chance / Community Chest:
    - Draw the top card, read it, apply its effect, then place it on the bottom.
  - Go to Jail:
    - Move directly to the Jail space; your turn ends without collecting Go.
  - Jail (Just Visiting) / Free Parking:
    - No action required.
)",
        R"(
===== Building Upgrades (Optional After Movement) =====
  - If you own both properties of a color group, you may build on them once per turn.
  - House Costs:
    - Red group: $50 each
    - Green group: $75 each
    - Blue group: $100 each
  - You can place up to 4 houses on each property; each house raises that property’s rent by its build cost.
  - Once a property has 4 houses, you may trade those in for a hotel:
    - Hotel costs:
      - Red: $150
      - Green: $225
      - Blue: $300
    - A hotel replaces all houses and sets rent to the flat hotel rate.
)",
        R"(
===== Jail Rules =====
  - If you land on Go to Jail, you remain there until you either:
    - Pay $50 at the start of your next turn.
    - Use a Get Out of Jail Free card.
  - Once freed, you move according to that turn’s dice roll (or pay first, then roll).
)",
        R"(
===== Bankruptcy & Winning =====
  - If at any time you owe more than you can pay, you are bankrupt and out of the game.
  - The game does not have a mortgage system.
  - The player with a non-negative balance is the winner.
)"
    };

    int choice = 0;
    do {
        clearScreen();
        cout << "===== Game Instructions =====\n";
        cout << "Please choose a section to read:\n";
        for (size_t i = 0; i < sections.size(); ++i) {
            cout << "[" << (i + 1) << "] " << sections[i] << endl;
        }
        cout << "Enter the number of the section you want to read: ";
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= static_cast<int>(sections.size()) - 1) {
            displayInstructionPage(pages[choice - 1]);
        } else if (choice == static_cast<int>(sections.size())) {
            cout << "\nReturning to the main menu...\n";
            pauseScreen();
            break; // Exit the loop and return to main menu
        } else {
            cout << "\nInvalid choice. Please try again.\n";
            pauseScreen();
        }
    } while (true);
}

#endif