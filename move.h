#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "board.h"

using namespace std;

class Main : public Board {
public:
    // Member variable to store player positions.
    // In this example, we assume a two-player game starting at position 0.
    vector<int> playerPositions;

    // Constructor initializes player positions.
    Main(int p1 = 0, int p2 = 0) {
        playerPositions.push_back(Board::posSpecifier(p1));
        playerPositions.push_back(Board::posSpecifier(p2));
    }

    // Draw the board, using the current playerPositions.
    void drawBoard(const string& p1Balance, const string& p2Balance, const string& currentPlayer) {
        // Board layout parameters.
        const int numBoxes       = 6;
        const int cellWidth      = 13;
        const int cellHeight     = 5;
        const int gap            = 0;
        const int specialGap     = 55;
        const int specialInterior= 4;
        const int boxWidth       = 83;

        // 1) Define your tile rows.
        vector<Board::Tile> tilesStandard = {
            { "Free",       "\033[41m\033[97m" },  // RR - red
            { "Harbor",     "\033[38;2;0;0;0;48;2;153;204;255m" },  // B - pale blue
            { "Chance",     "\033[38;2;0;0;0;48;2;255;153;255m" },  // V - pale violet
            { "Water",      "\033[48;5;15m\033[30m" },            // W - pure white
            { "Bayview",    "\033[38;2;0;0;0;48;2;153;204;255m" },  // B again
            { "Go to Jail", "\033[38;2;0;0;0;48;2;255;204;153m" }   // O - pale orange
        };

        vector<Board::Tile> specialTiles = {
            { "Electric", "\033[48;5;15m\033[30m" },                // W - pure white
            { "Chance",   "\033[38;2;0;0;0;48;2;255;153;255m" }       // V - pale violet
        };

        vector<Board::Tile> specialTiles2 = {
            { "Garden City", "\033[38;2;0;0;0;48;2;153;255;153m" },  // G - pale green
            { "Sunset",      "\033[38;2;0;0;0;48;2;255;255;153m" }   // Y - pale yellow
        };

        vector<Board::Tile> specialTiles3 = {
            { "Income Tax",  "\033[48;5;250m\033[30m" },              // PG - pale gray
            { "Internet",    "\033[48;5;15m\033[30m" }                // W - pure white
        };

        vector<Board::Tile> specialTiles4 = {
            { "Greenwich", "\033[38;2;0;0;0;48;2;153;255;153m" },       // G - pale green
            { "Chest",     "\033[48;5;223m\033[30m" }                   // BR - pale brown
        };

        vector<Board::Tile> tilesStandard2 = {
            { "Jail",     "\033[38;2;0;0;0;48;2;255;204;153m" },         // O - pale orange
            { "Roselawn", "\033[38;2;0;0;0;48;2;255;153;153m" },         // R - pale red
            { "Railroad", "\033[48;5;250m\033[30m" },                    // PG - pale gray
            { "Chest",    "\033[38;2;0;0;0;48;2;255;153;255m" },         // V - pale violet
            { "Redford",  "\033[38;2;0;0;0;48;2;255;153;153m" },         // R - pale red
            { "GO!",      "\033[41m\033[97m" }                         // RR - red background with bright white text
        };

        // Dialog declarations.
        string dialog = "Way To Go Business Tycoons!";
        string balances = "P1 Current Balance: " + p1Balance + " | " + "P2 Current Balance: " + p2Balance;
        string currentPlayerMsg = currentPlayer + " turns to play";
        
        // 3) Print the board using your pre-defined functions.
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

    // Function to prompt the player with a centered question.
    string askPlayerQuestion(const string &prompt, int boxWidth) {
        return Board::getInputInBoxCenteredPrompt(prompt, boxWidth);
    }

    // New member function for player movement.
    // This function moves the player at playerIndex by the number of steps, 
    // updates the playerPositions, and then redraws the board.
};

#endif // MOVE_H