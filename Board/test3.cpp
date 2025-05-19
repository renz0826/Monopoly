#include <iostream>
#include <string>
using namespace std;

// A simple structure to hold tile information (name and background color)
struct Tile {
    string name;
    string bgColor; // ANSI escape code for background color
};

// Centers a given text within a fixed width.
// If the text is longer than the width, it is trimmed.
string centerText(const string &text, int width) {
    if (text.length() >= static_cast<size_t>(width))
        return text.substr(0, width);
    int totalSpaces = width - text.length();
    int padLeft = totalSpaces / 2;
    int padRight = totalSpaces - padLeft;
    return string(padLeft, ' ') + text + string(padRight, ' ');
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

// Prints a given number of interior blank lines for a standard row.
void printInteriorBlankLines(int numBoxes, int cellWidth, int numLines, int gap) {
    string gapStr = getGapString(gap);
    for (int j = 0; j < numLines; j++) {
        cout << "|";
        for (int i = 0; i < numBoxes; i++) {
            cout << string(cellWidth, ' ') << "|";
            if (i < numBoxes - 1)
                cout << gapStr;
        }
        cout << "\n";
    }
}

void printSpecialRow(Tile tiles[], int cellWidth, int gap) {
    
    // Header line for the two special boxes
    cout << "|";
    cout << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\x1b[0m" << "|";
    cout << getGapString(gap);
    cout << "|";
    cout << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\x1b[0m" << "|";
    cout << "\n";
    
    // Interior blank lines (3 lines)
    for (int j = 0; j < 4; j++) {
        cout << "|";
        cout << string(cellWidth, ' ') << "|";
        cout << getGapString(gap);
        cout << "|";
        cout << string(cellWidth, ' ') << "|";
        cout << "\n";
    }

}

void printSpecialRow2(Tile tiles[], int cellWidth, int gap) {

    // Header line for the two special boxes
    cout << "|";
    cout << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\x1b[0m" << "|";
    cout << getGapString(gap);
    cout << "|";
    cout << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\x1b[0m" << "|";
    cout << "\n";
    
    // Interior blank lines (3 lines)
    for (int j = 0; j < 4; j++) {
        cout << "|";
        cout << string(cellWidth, ' ') << "|";
        cout << getGapString(gap);
        cout << "|";
        cout << string(cellWidth, ' ') << "|";
        cout << "\n";
    }

}

// Prints a special row with 2 boxes separated by a fixed gap,
// and an editable number of interior lines.
void printSpecialRowWithDialog(Tile tiles[], int cellWidth, int gap, 
                               const string &dialog, const string &subDialog,
                               const string &choiceDialog, int interiorLines) {
    // Ensure at least 2 interior lines for dialog and sub-dialog.
    if (interiorLines < 2)
        interiorLines = 2;
    
    // Top border:
    cout << "+" << string(cellWidth, '-') << "+" 
         << getGapString(gap) 
         << "+" << string(cellWidth, '-') << "+\n";
    
    // Header line (tile titles):
    cout << "|" 
         << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\033[0m" << "|" 
         << getGapString(gap)
         << "|" 
         << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\033[0m" << "|\n";
    
    // Interior lines for the gap area:
    // The first line prints the main dialog, the second prints the sub-dialog.
    // Any extra interior lines (if interiorLines > 2) print as blank.
    for (int j = 0; j < interiorLines; j++) {
        cout << "|" << string(cellWidth, ' ') << "|";
        // Print the dialog content within the fixed gap width.
        if (j == 0)
            cout << centerText(dialog, gap);
        else if (j == 1)
            cout << centerText(subDialog, gap);
        else if (j == 2)
            cout << centerText(choiceDialog, gap);
        else
            cout << getGapString(gap);
        cout << "|" << string(cellWidth, ' ') << "|\n";
    }
    
    // Bottom border:
    cout << "+" << string(cellWidth, '-') << "+" 
         << getGapString(gap) 
         << "+" << string(cellWidth, '-') << "+\n";
}

int main() {
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

    tilesStandard[6];
    
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

    cout << tilesStandard2[5].name;
    
    int specialGap = 55;
    // Print the standard row:
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tilesStandard, numBoxes, cellWidth, gap);
    // Print (cellHeight - 1) interior blank lines (adjust cellHeight as needed)
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printSpecialRow2(specialTiles, cellWidth, specialGap);
    
    // ---- Special Row Parameters ----
    // Special row: 2 boxes with a wide gap.
    // Inside that gap, we want the main dialog on the first interior line,
    // the sub-dialog on the second, and the overall number of interior lines editable.
    
    int specialInterior = 4;   // editable number of interior lines for the special row (minimum of 2)
    string dialog = "You're currently on Water Works (Utility)";
    string subDialog = "Would you like to purchase it for $100? [y/n]";
    string choiceDialog = "Your choice: ";

    
    printSpecialRowWithDialog(specialTiles2, cellWidth, specialGap, dialog, subDialog, choiceDialog, specialInterior);
    printSpecialRow2(specialTiles3, cellWidth, specialGap);
    printSpecialRow2(specialTiles4, cellWidth, specialGap);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tilesStandard2, numBoxes, cellWidth, gap);
    // Print (cellHeight - 1) interior blank lines (adjust cellHeight as needed)
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    
    return 0;
}