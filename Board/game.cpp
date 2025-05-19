#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// A simple structure to hold tile information (name and background color)
struct Tile {
    string name;
    string bgColor; // ANSI escape code for background color
};

// Helper function that centers text in a fixed-width space.
string centerText(const string &text, int width) {
    if (text.length() >= static_cast<size_t>(width))
        return text.substr(0, width);
    
    int totalSpaces = width - text.length();
    int padLeft = totalSpaces / 2;
    int padRight = totalSpaces - padLeft;
    return string(padLeft, ' ') + text + string(padRight, ' ');
}

// Function that returns a string made of spaces equal to gapWidth.
string getGapString(int gapWidth) {
    return string(gapWidth, ' ');
}

// Function to print the horizontal border for a row of standard boxes.
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

// Function to print the header line for a row of standard boxes.
void printHeaderLine(Tile tiles[], int numBoxes, int cellWidth, int gap) {
    string gapStr = getGapString(gap);
    cout << "|";
    for (int i = 0; i < numBoxes; i++) {
        string text = centerText(tiles[i].name, cellWidth);
        cout << tiles[i].bgColor << text << "\x1b[0m" << "|";
        if (i < numBoxes - 1)
            cout << gapStr;
    }
    cout << "\n";
}

// Function to print interior blank lines for a row of standard boxes.
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

// Function to print a special row with 2 boxes separated by an adjustable gap.
// This row is designed to have 1 box, then (for example) 4 spaces, then 1 box.
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
    cout << "+";
    cout << string(cellWidth, '-');
    cout << "+";
    cout << getGapString(gap);
    cout << "+";
    cout << string(cellWidth, '-');
    cout << "+\n";

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

const int TOTAL_WIDTH = 69;
// For a two-column table, there are 3 border characters ("|", "|" and "|")
// So each column’s content (excluding the vertical borders) gets:
const int CELL_WIDTH = 31;

// Formats the text for a table cell without including its own borders.
// It pads the content so that the returned string always has length CELL_WIDTH.
string formatCell(const string &label, int cellWidth, int padding = 2) {
    // The space available to display text is everything minus the left/right padding.
    int availableSpace = cellWidth - 2 * padding;
    // Truncate the label if it is too long.
    string trimmedLabel = label.substr(0, min((int)label.size(), availableSpace));
    // Compute additional right padding to fill the space.
    int extraPadding = availableSpace - trimmedLabel.size();
    return string(padding, ' ') + trimmedLabel + string(padding + extraPadding, ' ');
}

// Prints both columns side-by-side in a table of fixed width.
void printSideBySideBoxes(const vector<string>& labels1, const vector<string>& labels2) {
    // Build the horizontal border (top/middle/bottom) for the entire table.
    string hBorder = "+" + string(CELL_WIDTH, '-') + "+" + string(CELL_WIDTH, '-') + "+";
    
    cout << hBorder << endl;
    
    for (size_t i = 0; i < labels1.size(); ++i) {
        cout << "|" 
             << formatCell(labels1[i], CELL_WIDTH)
             << "|" 
             << formatCell(labels2[i], CELL_WIDTH)
             << "|" << endl;
             
        // For example, after the first row you might wish to print another horizontal divider.
        if (i == 0) {
            cout << hBorder << endl;
        }
    }
    
    cout << hBorder << endl;
}

int maxLabelLength(const vector<string>& labels) {
    int maxLen = 0;
    for (const auto& s : labels)
        maxLen = max(maxLen, (int)s.length());
    return maxLen;
}

const string RESET = "\x1b[0m";
const string BG_BLACK = "\x1b[40m";
const string BG_WHITE = "\x1b[107m";
const string BG_RED = "\x1b[41m";

int main() {
    vector<pair<string, int>> players;

    // Input for Player 1
    string name1;
    int balance1;
    cout << "Enter Player 1's name: ";
    getline(cin, name1);
    cout << "Enter Player 1's balance: ";
    cin >> balance1;
    cin.ignore();

    // Input for Player 2
    string name2;
    int balance2;
    cout << "Enter Player 2's name: ";
    getline(cin, name2);
    cout << "Enter Player 2's balance: ";
    cin >> balance2;

    players.push_back({name1, balance1});
    players.push_back({name2, balance2});

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    vector<string> pixelArt = {
        "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
        "RRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWWRRRWWRRWRRRWRWRRRR",
        "RRRWWRWWRRWRRWWRWRRWRRRRRWWRWWRWRRWRWWRWRWRRWRWRWRWRRWRWRRRWRWRRRR",
        "RRRWRWRWRRWRRWRWWRRWRRWWRWRWRWRWRRWRWRWWRWRRWRWWRRWRRWRWRRRRWRRRRR",
        "RRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWRRRRWWRRWWWRRWRRRRR",
        "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
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

    vector<string> p1Labels = {
        "Player 1: " + players[0].first,
        "Balance: $" + to_string(players[0].second)
    };

    vector<string> p2Labels = {
        "Player 2: " + players[1].first,
        "Balance: $" + to_string(players[1].second)
    };

    // With the fixed CELL_WIDTH, print the table.
    printSideBySideBoxes(p1Labels, p2Labels);
    
    // First row: 6 boxes
    const int numBoxes = 6;      // number of cells in the first row
    const int cellWidth = 13;    // fixed interior width per cell
    const int cellHeight = 5;    // total number of interior lines per cell
    int gap = 0;                 // gap between boxes in the first row

    // ANSI color codes (black text on pastel background)
    const string R = "\033[38;2;0;0;0;48;2;255;153;153m"; // pale red
    const string O = "\033[38;2;0;0;0;48;2;255;204;153m"; // pale orange
    const string Y = "\033[38;2;0;0;0;48;2;255;255;153m"; // pale yellow
    const string G = "\033[38;2;0;0;0;48;2;153;255;153m"; // pale green
    const string B = "\033[38;2;0;0;0;48;2;153;204;255m"; // pale blue
    const string V = "\033[38;2;0;0;0;48;2;255;153;255m"; // pale violet

    // First row tile array (6 boxes)
    Tile tiles[numBoxes] = {
        { "Go",       R },
        { "Redford",  O },
        { "Chest",    Y },
        { "Railroad", G },
        { "Roselawn", B },
        { "Jail",     V }
    };

    // Special row tile array: 2 boxes
    Tile specialTiles[] = {
        { "Chance", 		R },
        { "Income Tax", 	O }
    };
    
    Tile specialTiles2[] = {
        { "Water", 		B },
        { "Electric", 	Y }
    };
    
    Tile specialTiles3[] = {
        { "Water", 		B },
        { "Electric", 	Y }
    };

    // Print the first row (6 boxes)
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tiles, numBoxes, cellWidth, gap);
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap);
    printHorizontalBorder(numBoxes, cellWidth, gap);

    // For the special row, we want 1 box, a gap of 4 spaces, and then 1 box.
    int specialGap = 55;
    printSpecialRow(specialTiles, cellWidth, specialGap);
    printSpecialRow2(specialTiles2, cellWidth, specialGap);
    printSpecialRow2(specialTiles2, cellWidth, specialGap);
    printSpecialRow2(specialTiles2, cellWidth, specialGap);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    printHeaderLine(tiles, numBoxes, cellWidth, gap);
    printInteriorBlankLines(numBoxes, cellWidth, cellHeight - 1, gap);
    printHorizontalBorder(numBoxes, cellWidth, gap);
    
    
}