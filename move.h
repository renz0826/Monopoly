#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "board.h"
#include "colors.h"

using namespace std;

class Main : public Board, public Colors {
    public:

        // Member variable to store player positions.
        vector<int> playerPositions;

        // Constructor initializes player positions.
        Main(int p1 = 0, int p2 = 0) {
            playerPositions.push_back(Board::posSpecifier(p1));
            playerPositions.push_back(Board::posSpecifier(p2));
        }

        // Draw the board, using the current playerPositions.
        void drawBoard(const string& p1Balance, const string& p2Balance, const string& currentPlayer) {

            Colors c;

            // Board layout parameters.
            const int numBoxes       = 6;
            const int cellWidth      = 13;
            const int cellHeight     = 5;
            const int gap            = 0;
            const int specialGap     = 55;
            const int specialInterior= 4;
            const int boxWidth       = 83;

            // Define your tile rows.
            vector<Board::Tile> tilesStandard = {
                { "Free",       c.RR}, 
                { "Harbor",     c.B},  
                { "Chance",     c.V},
                { "Water",      c.W},           
                { "Bayview",    c.B}, 
                { "Go to Jail", c.O}
            };

            vector<Board::Tile> specialTiles = {
                { "Electric", c.W},             
                { "Chance",   c.V}     
            };

            vector<Board::Tile> specialTiles2 = {
                { "Garden City", c.G}, 
                { "Sunset",      c.Y}  
            };

            vector<Board::Tile> specialTiles3 = {
                { "Income Tax",  c.PG},            
                { "Internet",    c.W}            
            };

            vector<Board::Tile> specialTiles4 = {
                { "Greenwich", c.G},     
                { "Chest",     c.BR}                  
            };

            vector<Board::Tile> tilesStandard2 = {
                { "Jail",     c.O},      
                { "Roselawn", c.R},     
                { "Railroad", c.PG},         
                { "Chest",    c.V},        
                { "Redford",  c.R},         
                { "GO!",      c.RR}                   
            };

            // Dialog declarations.
            string dialog = "Way To Go Business Tycoons!";
            string balances = "P1 Current Balance: " + p1Balance + " | " + "P2 Current Balance: " + p2Balance;
            string currentPlayerMsg = currentPlayer + " turns to play";
            
            // Print the board using your pre-defined functions.
            Board::printHorizontalBorder(numBoxes, cellWidth, gap);
            Board::printHeaderLine(tilesStandard, numBoxes, cellWidth, gap);
            Board::printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap, playerPositions, 0, false);
            Board::printHorizontalBorder(numBoxes, cellWidth, gap);
            Board::printSpecialRow(specialTiles, cellWidth, specialGap, playerPositions, 6, 7);
            Board::printSpecialRowWithDialog(
                specialTiles2, cellWidth, specialGap, dialog, balances, currentPlayerMsg,
                specialInterior, playerPositions, 8, 9
            );
            Board::printSpecialRow(specialTiles3, cellWidth, specialGap, playerPositions, 10, 11);
            Board::printSpecialRow2(specialTiles4, cellWidth, specialGap, playerPositions, 12, 13);
            Board::printHorizontalBorder(numBoxes, cellWidth, gap);
            Board::printHeaderLine(tilesStandard2, numBoxes, cellWidth, gap);
            Board::printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap, playerPositions, 14, false);
            Board::printHorizontalBorder(numBoxes, cellWidth, gap);
        }
};

#endif // MOVE_H