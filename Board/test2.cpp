#include <iostream>
#include <string>
#include <vector>  // For handling multiple players
using namespace std;

// Modified Tile structure to track occupants
struct Tile {
    string name;
    string bgColor;
    vector<int> occupants;  // Track which players are here (1 or 2)
};

string centerTexts(const string &text, int width) {
    int padLeft = (width - static_cast<int>(text.size())) / 2;
    int padRight = width - static_cast<int>(text.size()) - padLeft;
    return string(padLeft, ' ') + text + string(padRight, ' ');
}

string getInputInBoxCenteredPrompt(const string &prompt, int boxWidth) {
    // Draw the box:
    // Top border:
    cout << "+" << string(boxWidth, '-') << "+" << "\n";
    // Input row (initially blank):
    cout << "|" << string(boxWidth, ' ') << "|" << "\n";
    // Bottom border:
    cout << "+" << string(boxWidth, '-') << "+" << "\n";
    
    // After printing the box, the cursor is on the line below the box.
    // We need to move up 2 lines to land on the input row.
    cout << "\033[2A";  // Move up two lines.
    
    // Calculate the horizontal starting position in the inner area such that the prompt appears centered.
    // The inner text area is 'boxWidth' characters wide. Since the left border occupies column 1,
    // we add 1 to the calculated left-padding.
    int promptPos = (boxWidth - prompt.size()) / 2 + 1;
    cout << "\033[" << promptPos << "G";  // Move the cursor to column 'promptPos'.
    cout.flush();
    
    // Print the prompt (with a trailing space) and allow the user to type inline.
    cout << prompt << " ";
    string userInput;
    getline(cin, userInput);
    
    return prompt + " " + userInput;
}






string centerText(const string &text, int width) {
    // Strip ANSI codes for length calculation
    size_t visibleLength = 0;
    bool inEscape = false;
    for (char c : text) {
        if (c == '\033') inEscape = true;
        if (!inEscape) visibleLength++;
        if (c == 'm') inEscape = false;
    }

    if (visibleLength >= static_cast<size_t>(width))
        return text.substr(0, width);
    
    int totalSpaces = width - visibleLength;
    int padLeft = totalSpaces / 2;
    return string(padLeft, ' ') + text + string(totalSpaces - padLeft, ' ');
}

// Returns a string filled with spaces of the given gapWidth.
string getGapString(int gapWidth) {
    return string(gapWidth, ' ');
}

// Prints a horizontal border line for a row with a given number of boxes.
// Each box has a fixed width and the boxes are separated by a fixed gap.
void printHorizontalBorder(int numBoxes, int cellWidth, int gap) {
    string gapStr = getGapString(gap);
    cout << "+";
    for (int i = 0; i < numBoxes; i++) {
        cout << string(cellWidth, '-');
        cout << "+";
        if (i < numBoxes - 1)
            cout << gapStr;
    }
    cout << "\n";
}

// Prints the header line (with box titles) for a row of standard boxes.
void printHeaderLine(Tile tiles[], int numBoxes, int cellWidth, int gap) {
    string gapStr = getGapString(gap);
    cout << "|";
    for (int i = 0; i < numBoxes; i++) {
        string text = centerText(tiles[i].name, cellWidth);
        cout << tiles[i].bgColor << text << "\033[0m" << "|";
        if (i < numBoxes - 1)
            cout << gapStr;
    }
    cout << "\n";
}

// Define ANSI color codes for players (before the loop)
static const vector<string> playerColors = {
                "\033[38;5;196m",  // Player 1: Bright Red
                "\033[38;5;33m"    // Player 2: Bright Blue
};

// Modified to show player positions
void printInteriorBlankLines(int numBoxes, int cellWidth, int numLines, int gap, 
                            const vector<int>& playerPositions, int boardSectionStart, 
                            bool isReversed = false) {
    string gapStr = getGapString(gap);
    for (int j = 0; j < numLines; j++) {
        cout << "|";
        for (int i = 0; i < numBoxes; i++) {
            // Calculate actual board index
            int cellIndex;
            if (isReversed) {
                cellIndex = boardSectionStart + (numBoxes - 1 - i);
            } else {
                cellIndex = boardSectionStart + i;
            }

            // Inside the cell rendering logic:
            string marker;
            for (size_t playerIdx = 0; playerIdx < playerPositions.size(); ++playerIdx) {
                if (playerPositions[playerIdx] == cellIndex) {
                    // Append colored asterisk for this player
                    marker += playerColors[playerIdx] + "*\033[0m ";
                }
            }

            // Remove trailing space if needed
            if (!marker.empty()) {
                marker.pop_back();
            }

            string cellContent;
            if (!marker.empty() && j == numLines/2) {  // Center vertically
                cellContent = centerText(marker, cellWidth);
            } else {
                cellContent = string(cellWidth, ' ');
            }

            cout << cellContent << "|";
            if (i < numBoxes - 1) cout << gapStr;
        }
        cout << "\n";
    }
}

        void printSpecialRow(Tile tiles[],
            int cellWidth,
            int gap,
            const vector<int>& playerPositions,
            int boardIndex0,   
            int boardIndex1)   
        {
        // Header line:
        cout << "|"
        << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\033[0m" << "|"
        << getGapString(gap)
        << "|"
        << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\033[0m" << "|"
        << "\n";

        // Number of interior lines (for consistency, 4 here as before):
        int interiorLines = 4;
        int midLine = interiorLines / 2;

        for (int j = 0; j < interiorLines; ++j) {
        // --- LEFT BOX ---
        cout << "|";
        string leftContent(cellWidth, ' ');
        if (j == midLine) {
        // build marker string if a player is on this tile
        string marker;
        for (size_t p = 0; p < playerPositions.size(); ++p) {
        if (playerPositions[p] == boardIndex0) {
        marker += playerColors[p] + "*" + "\033[0m" + " ";
        }
        }
        if (!marker.empty()) {
        marker.pop_back();  // strip trailing space
        leftContent = centerText(marker, cellWidth);
        }
        }
        cout << leftContent << "|";

        // --- GAP ---
        cout << getGapString(gap);

        // --- RIGHT BOX ---
        cout << "|";
        string rightContent(cellWidth, ' ');
        if (j == midLine) {
        string marker;
        for (size_t p = 0; p < playerPositions.size(); ++p) {
        if (playerPositions[p] == boardIndex1) {
        marker += playerColors[p] + "*" + "\033[0m" + " ";
        }
        }
        if (!marker.empty()) {
        marker.pop_back();
        rightContent = centerText(marker, cellWidth);
        }
        }
        cout << rightContent << "|";

        cout << "\n";
        }
        }

        // If you already have printSpecialRow(), you can just alias it:
        void printSpecialRow2(Tile tiles[],
            int cellWidth,
            int gap,
            const vector<int>& playerPositions,
            int boardIndex0,
            int boardIndex1)
        {
            cout << "+"
            << string(cellWidth, '-')
            << "+"
            << getGapString(gap)
            << "+"
            << string(cellWidth, '-')
            << "+"
            << "\n";
            // delegate straight to printSpecialRow()
            printSpecialRow(tiles, cellWidth, gap, playerPositions, boardIndex0, boardIndex1);
        }

        // --- UPDATED printSpecialRow2:
        // identical to printSpecialRow, so you can just call printSpecialRow()
        // but if you really want a standalone, duplicate and pass its own boardIndex0/index1…


        void printSpecialRowWithDialog(
            Tile tiles[],
            int cellWidth,
            int gap,
            const string &dialog,
            const string &subDialog,
            const string &choiceDialog,
            int interiorLines,
            const vector<int>& playerPositions,
            int boardIndex0,
            int boardIndex1)
        {
            // Ensure we have room for at least dialog + sub-dialog
            if (interiorLines < 3) interiorLines = 3;
            int midLine = interiorLines / 2;
        
            // Top border
            cout << "+"
                 << string(cellWidth, '-') << "+"
                 << getGapString(gap)
                 << "+" << string(cellWidth, '-') << "+\n";
        
            // Header row (tile titles)
            cout << "|"
                 << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\033[0m" << "|"
                 << getGapString(gap)
                 << "|"
                 << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\033[0m" << "|\n";
        
            // Interior rows
            for (int j = 0; j < interiorLines; ++j) {
                // Left box
                cout << "|";
                string leftCell(cellWidth, ' ');
                if (j == midLine) {
                    // player marker for left tile
                    string marker;
                    for (size_t p = 0; p < playerPositions.size(); ++p) {
                        if (playerPositions[p] == boardIndex0) {
                            marker += playerColors[p] + "*" + "\033[0m";
                        }
                    }
                    if (!marker.empty()) {
                        leftCell = centerText(marker, cellWidth);
                    }
                }
                cout << leftCell << "|";
        
                // Gap/dialog area
                if (j == 0) {
                    cout << centerText(dialog, gap);
                } else if (j == 1) {
                    cout << centerText(subDialog, gap);
                } else if (j == 2) {
                    cout << centerText(choiceDialog, gap);
                } else {
                    cout << getGapString(gap);
                }
        
                // Right box
                cout << "|";
                string rightCell(cellWidth, ' ');
                if (j == midLine) {
                    // player marker for right tile
                    string marker;
                    for (size_t p = 0; p < playerPositions.size(); ++p) {
                        if (playerPositions[p] == boardIndex1) {
                            marker += playerColors[p] + "*" + "\033[0m";
                        }
                    }
                    if (!marker.empty()) {
                        rightCell = centerText(marker, cellWidth);
                    }
                }
                cout << rightCell << "|\n";
            }
        
            // Bottom border
            cout << "+"
                 << string(cellWidth, '-') << "+"
                 << getGapString(gap)
                 << "+" << string(cellWidth, '-') << "+\n";
        }

        int posSpecifier(int pos) {
            if (pos == 0) {
                return 19;
            }
            else if (pos == 1) {
                return 18;
            }
            else if (pos == 2) {
                return 17;
            }
            else if (pos == 3) {
                return 16;
            }
            else if (pos == 4) {
                return 15;
            }
            else if (pos == 5) {
                return 14;
            }
            else if (pos == 6){
                return 12;
            }
            else if (pos == 7){
                return 10;
            }
            else if (pos == 8){
                return 8;
            }
            else if (pos == 9){
                return 6;
            }
            else if (pos == 10){
                return 0;
            }
            else if (pos == 11){
                return 1;
            }
            else if (pos == 12){
                return 2;
            }
            else if (pos == 13){
                return 3;
            }
            else if (pos == 14){
                return 4;
            }
            else if (pos == 15){
                return 5;
            }
            else if (pos == 16){
                return 7;
            }
            else if (pos == 17){
                return 9;
            }
            else if (pos == 18){
                return 11;
            }
            else if (pos == 19){
                return 13;
            }
        }
        
// ... [Keep printHeaderLine, printSpecialRow, etc. unchanged] ...

int main() {
    // ---- Player Positions ----

    // Give each player a unique starting position:
    int pos1 = 0;  
    int pos2 = 0;  
    
    vector<int> playerPositions = { posSpecifier(pos1), posSpecifier(pos2) };
    
       // ---- Standard (Main) Row Parameters ----
       const int numBoxes = 6;      // number of boxes in the standard row
       const int cellWidth = 13;    // width of each box's interior
       const int cellHeight = 5;    // editable number of interior blank lines for standard row
       int gap = 0;                 // gap between boxes in the standard row
   
       // ANSI color codes for box backgrounds:
       const string R = "\033[38;2;0;0;0;48;2;255;153;153m";  // pale red
       const string O = "\033[38;2;0;0;0;48;2;255;204;153m";  // pale orange
       const string Y = "\033[38;2;0;0;0;48;2;255;255;153m";  // pale yellow
       const string G = "\033[38;2;0;0;0;48;2;153;255;153m";  // pale green
       const string B = "\033[38;2;0;0;0;48;2;153;204;255m";  // pale blue
       const string V = "\033[38;2;0;0;0;48;2;255;153;255m";  // pale violet
       const string BR = "\033[48;5;223m\033[30m";            // pale brown
       const string PG = "\033[48;5;250m\033[30m";            // pale gray
       const string W = "\033[48;5;15m\033[30m";              //pure white
       const string RR = "\033[41m\033[97m";            // red
   
       // Standard row tile array (6 boxes):
       Tile tilesStandard[numBoxes] = {
           { "Free",       RR },
           { "Harbor",  B },
           { "Chance",    V },
           { "Water",  W },
           { "Bayview", B },
           { "Go to Jail",     O }
       };
   
       
       Tile specialTiles[] = {
           { "Electric", 		W },
           { "Chance", 	V }
       };
       
       Tile specialTiles2[] = {
           { "Garden City", 		G },
           { "Sunset", 	Y }
       };
       
       Tile specialTiles3[] = {
           { "Income Tax", 	PG },
           { "Internet", 	W }
       };
   
       Tile specialTiles4[] = {
           { "Greenwich", 	G },
           { "Chest", 	BR }
       };
   
   
   
       Tile tilesStandard2[] = {
           { "Jail", 	O },
           { "Roselawn", 	R },
           { "Railroad",  PG },
           { "Chest", 	V },
           { "Redford", 	R },
           { "GO!", 	RR }
       };
       
       int specialGap = 55;
       int specialInterior = 4;
    // ... [Keep color definitions and tile initialization unchanged] ...

    string dialog = "Welcome!";
    string subDialog = "Choose wisely";
    string choiceDialog = "yes";

    // Modified print calls with player positions
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tilesStandard, numBoxes, cellWidth, gap);
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight-1, gap, playerPositions, 0, false);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printSpecialRow(specialTiles, cellWidth, specialGap, playerPositions, 6, 7);
    printSpecialRowWithDialog(
        specialTiles2,   // { "Income Tax", "Internet" }
        cellWidth,              // cellWidth
        specialGap,              // gap
        dialog,      // dialog
        subDialog,     // subDialog
        choiceDialog, // choiceDialog
        specialInterior,               // interiorLines
        playerPositions, // e.g. {10,11}
        8,              // boardIndex0
        9               // boardIndex1
    );
    printSpecialRow(specialTiles3, cellWidth, specialGap, playerPositions, 10, 11);
    printSpecialRow2(specialTiles4, cellWidth, specialGap, playerPositions, 12, 13);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tilesStandard2, numBoxes, cellWidth, gap);
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight-1, gap, playerPositions, 14, false);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    
    int boxWidth = 83;  // Fixed width for the dialog box.
    string prompt = "Question:";
    string response = getInputInBoxCenteredPrompt(prompt, boxWidth);

    return 0;
}