#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include "operations.h"

using namespace std;


const int TOTAL_WIDTH = 90;
// For a two-column table, there are 3 border characters ("|", "|" and "|")
// So each column’s content (excluding the vertical borders) gets:
const int CELL_WIDTH = 41;

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
        "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
        "RRRRRRRRRRRRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWWRRRWWRRWRRRWRWRRRRRRRRRRRRR",
        "RRRRRRRRRRRRRWWRWWRRWRRWWRWRRWRRRRRWWRWWRWRRWRWWRWRWRRWRWRWRWRRWRWRRRWRWRRRRRRRRRRRRR",
        "RRRRRRRRRRRRRWRWRWRRWRRWRWWRRWRRWWRWRWRWRWRRWRWRWWRWRRWRWWRRWRRWRWRRRRWRRRRRRRRRRRRRR",
        "RRRRRRRRRRRRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWRRRRWWRRWWWRRWRRRRRRRRRRRRRR",
        "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
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
    
    return 0;
}