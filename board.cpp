// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include "board.h"

using namespace std;


int main() {
    // Board layout parameters
    const int numBoxes     = 6;  
    const int cellWidth    = 13;
    const int cellHeight   = 5;
    const int gap          = 0;
    const int specialGap   = 55;
    const int specialInterior = 4;
    const int specialLines = 4;
    const int boxWidth     = 83;

       // ANSI color codes for box backgrounds:
       const string R = "\033[38;2;0;0;0;48;2;255;153;153m";    // pale red
       const string O = "\033[38;2;0;0;0;48;2;255;204;153m";    // pale orange
       const string Y = "\033[38;2;0;0;0;48;2;255;255;153m";    // pale yellow
       const string G = "\033[38;2;0;0;0;48;2;153;255;153m";    // pale green
       const string B = "\033[38;2;0;0;0;48;2;153;204;255m";    // pale blue
       const string V = "\033[38;2;0;0;0;48;2;255;153;255m";    // pale violet
       const string BR = "\033[48;5;223m\033[30m";              // pale brown
       const string PG = "\033[48;5;250m\033[30m";              // pale gray
       const string W = "\033[48;5;15m\033[30m";                //pure white
       const string RR = "\033[41m\033[97m";                    // red

    // 1) Define your tile rows
       vector <Board::Tile> tilesStandard = {
           { "Free",       RR },
           { "Harbor",  B },
           { "Chance",    V },
           { "Water",  W },
           { "Bayview", B },
           { "Go to Jail",     O }
       };
   
       
       vector <Board::Tile> specialTiles = {
           { "Electric", 		W },
           { "Chance", 	V }
       };
       
       vector <Board::Tile> specialTiles2 = {
           { "Garden City", 		G },
           { "Sunset", 	Y }
       };
       
       vector <Board::Tile> specialTiles3 = {
           { "Income Tax", 	PG },
           { "Internet", 	W }
       };
   
       vector <Board::Tile> specialTiles4 = {
           { "Greenwich", 	G },
           { "Chest", 	BR }
       };
   
       vector <Board::Tile> tilesStandard2 = {
           { "Jail", 	O },
           { "Roselawn", 	R },
           { "Railroad",  PG },
           { "Chest", 	V },
           { "Redford", 	R },
           { "GO!", 	RR }
       };


    // 2) Set up player positions
    int p1 = 0, p2 = 0;                     // diri ang sa dice nga sa position ni player starting from 0 which is gow
    vector<int> playerPositions = {
        Board::posSpecifier(p1),
        Board::posSpecifier(p2)
    };

    // Diri ang dialog sa tunga bale dialog top subdialog center choice dialog bottom
    string dialog = "Welcome!";
    string subDialog = "Choose wisely";
    string choiceDialog = "yes";

    Board::printHorizontalBorder(numBoxes, cellWidth, gap);
    Board::printHeaderLine(tilesStandard, numBoxes, cellWidth, gap);
    Board::printInteriorBlankLines(numBoxes, cellWidth, cellHeight-1, gap, playerPositions, 0, false);
    Board::printHorizontalBorder(numBoxes, cellWidth, gap);
    Board::printSpecialRow(specialTiles, cellWidth, specialGap, playerPositions, 6, 7);
    Board::printSpecialRowWithDialog(specialTiles2, cellWidth, specialGap, dialog, subDialog, choiceDialog, specialInterior, playerPositions, 8, 9);
    Board::printSpecialRow(specialTiles3, cellWidth, specialGap, playerPositions, 10, 11);
    Board::printSpecialRow2(specialTiles4, cellWidth, specialGap, playerPositions, 12, 13);
    Board::printHorizontalBorder(numBoxes, cellWidth, gap);
    Board::printHeaderLine(tilesStandard2, numBoxes, cellWidth, gap);
    Board::printInteriorBlankLines(numBoxes, cellWidth, cellHeight-1, gap, playerPositions, 14, false);
    Board::printHorizontalBorder(numBoxes, cellWidth, gap);
    
    string prompt = "Question:"; // sample lang ni nga do you want to buy?
    string response = Board::getInputInBoxCenteredPrompt(prompt, boxWidth); // mag run ini may corresponding cin click mo lang after ka ":" which is ang choice sangplayer


    return 0;
}
