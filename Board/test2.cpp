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

void printSpecialRowWithDialog(Tile tiles[], int cellWidth, int gap, 
                               const string &dialog, const string &subDialog, 
                               int interiorLines) {
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
    const int cellHeight = 5;    // total number of interior blank lines to print (editable)
    int gap = 3;                 // gap between boxes in the standard row

    // ANSI color codes for box backgrounds:
    const string R = "\033[38;2;0;0;0;48;2;255;153;153m";  // pale red
    const string O = "\033[38;2;0;0;0;48;2;255;204;153m";  // pale orange
    const string Y = "\033[38;2;0;0;0;48;2;255;255;153m";  // pale yellow
    const string G = "\033[38;2;0;0;0;48;2;153;255;153m";  // pale green
    const string B = "\033[38;2;0;0;0;48;2;153;204;255m";  // pale blue
    const string V = "\033[38;2;0;0;0;48;2;255;153;255m";  // pale violet

    // Standard row tile array (6 boxes):
    Tile tilesStandard[numBoxes] = {
        { "Go",       R },
        { "Redford",  O },
        { "Chest",    Y },
        { "Railroad", G },
        { "Roselawn", B },
        { "Jail",     V }
    };
    
    // Print the standard row:
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tilesStandard, numBoxes, cellWidth, gap);
    // Print (cellHeight - 1) interior blank lines; adjust cellHeight as needed.
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    
    cout << "\n"; // Separation between rows
    
    // ---- Special Row Parameters ----
    // Special row: 2 boxes with a wide gap that includes two dialog lines.
    Tile specialTiles[2] = {
        { "Chance", R },
        { "Income Tax", O }
    };
    
    int specialGap = 55;       // fixed gap width for the special row
    int specialInterior = 4;   // editable number of interior lines for the special row (minimum of 2)
    string dialog = "Welcome to Monopoly";
    string subDialog = "Buy your property!";
    
    printSpecialRowWithDialog(specialTiles, cellWidth, specialGap, dialog, subDialog, specialInterior);
    return 0;
}