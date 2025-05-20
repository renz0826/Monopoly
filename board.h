#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Board {
public:
    // Tile structure to track occupants
    struct Tile {
        string name;
        string bgColor;
        vector<int> occupants;
    };

    // Centers text without ANSI codes for centering prompts
    static string centerTexts(const string &text, int width) {
        int padLeft = (width - static_cast<int>(text.size())) / 2;
        int padRight = width - static_cast<int>(text.size()) - padLeft;
        return string(padLeft, ' ') + text + string(padRight, ' ');
    }

    // Draws an input box, centers the prompt, and reads user input
    static string getInputInBoxCenteredPrompt(const string &prompt, int boxWidth) {
        // Draw the box
        cout << "+" << string(boxWidth, '-') << "+\n";
        cout << "|" << string(boxWidth, ' ') << "|\n";
        cout << "+" << string(boxWidth, '-') << "+\n";
        
        // Move cursor up to input row
        cout << "\033[2A";
        int promptPos = (boxWidth - prompt.size()) / 2 + 1;
        cout << "\033[" << promptPos << "G";
        cout.flush();

        // Print prompt and read
        cout << prompt << " ";
        string userInput;
        getline(cin, userInput);
        return prompt + " " + userInput;
    }

    // Centers ANSI-styled text
    static string centerText(const string &text, int width) {
        size_t visibleLength = 0;
        bool inEscape = false;
        for (char c : text) {
            if (c == '\033') inEscape = true;
            if (!inEscape) visibleLength++;
            if (c == 'm') inEscape = false;
        }
        if (visibleLength >= (size_t)width)
            return text.substr(0, width);
        int totalSpaces = width - visibleLength;
        int padLeft = totalSpaces / 2;
        return string(padLeft, ' ') + text + string(totalSpaces - padLeft, ' ');
    }

    // Returns spaces of given width
    static inline string getGapString(int gapWidth) {
        return string(gapWidth, ' ');
    }

    // Prints horizontal border for a row of boxes
    static void printHorizontalBorder(int numBoxes, int cellWidth, int gap) {
        cout << "+";
        for (int i = 0; i < numBoxes; i++) {
            cout << string(cellWidth, '-') << "+";
            if (i < numBoxes - 1) cout << getGapString(gap);
        }
        cout << "\n";
    }

    // Prints header line with tile titles
    static void printHeaderLine(const vector<Tile> &tiles, int numBoxes, int cellWidth, int gap) {
        cout << "|";
        for (int i = 0; i < numBoxes; i++) {
            cout << tiles[i].bgColor
                 << centerText(tiles[i].name, cellWidth)
                 << "\033[0m"
                 << "|";
            if (i < numBoxes - 1) cout << getGapString(gap);
        }
        cout << "\n";
    }

    // ANSI colors for players
    static const vector<string> playerColors;

    // Prints interior blank lines and player markers
    static void printInteriorBlankLines(int numBoxes, int cellWidth, int numLines, int gap,
                                        const vector<int>& playerPositions, int boardSectionStart,
                                        bool isReversed = false) {
        string gapStr = getGapString(gap);
        for (int j = 0; j < numLines; j++) {
            cout << "|";
            for (int i = 0; i < numBoxes; i++) {
                int cellIndex = isReversed
                                ? boardSectionStart + (numBoxes - 1 - i)
                                : boardSectionStart + i;
                string marker;
                for (size_t p = 0; p < playerPositions.size(); ++p) {
                    if (playerPositions[p] == cellIndex) {
                        marker += playerColors[p] + "*\033[0m ";
                    }
                }
                if (!marker.empty()) marker.pop_back();

                if (!marker.empty() && j == numLines/2)
                    cout << centerText(marker, cellWidth);
                else
                    cout << string(cellWidth, ' ');

                cout << "|";
                if (i < numBoxes - 1) cout << gapStr;
            }
            cout << "\n";
        }
    }

    // Prints a special two-box row
    static void printSpecialRow(const vector<Tile> &tiles, int cellWidth, int gap,
                                const vector<int>& playerPositions,
                                int boardIndex0, int boardIndex1) {
        cout << "|" << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\033[0m" << "|"
             << getGapString(gap)
             << "|" << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\033[0m" << "|\n";
        int interiorLines = 4, midLine = interiorLines/2;
        for (int j = 0; j < interiorLines; ++j) {
            cout << "|";
            if (j == midLine) {
                string m;
                for (size_t p = 0; p < playerPositions.size(); ++p)
                    if (playerPositions[p] == boardIndex0)
                        m += playerColors[p] + "*\033[0m";
                cout << centerText(m, cellWidth);
            } else cout << string(cellWidth, ' ');
            cout << "|" << getGapString(gap) << "|";
            if (j == midLine) {
                string m;
                for (size_t p = 0; p < playerPositions.size(); ++p)
                    if (playerPositions[p] == boardIndex1)
                        m += playerColors[p] + "*\033[0m";
                cout << centerText(m, cellWidth);
            } else cout << string(cellWidth, ' ');
            cout << "|\n";
        }
    }

    static void printSpecialRow2(const vector<Tile> &tiles, int cellWidth, int gap,
                                 const vector<int>& playerPositions,
                                 int boardIndex0, int boardIndex1){
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

    // Prints special row with dialog in gap
    static void printSpecialRowWithDialog(const vector<Tile> &tiles, int cellWidth, int gap,
                                          const string &dialog, const string &subDialog,
                                          const string &choiceDialog, int interiorLines,
                                          const vector<int>& playerPositions,
                                          int boardIndex0, int boardIndex1) {
        if (interiorLines < 3) interiorLines = 3;
        int midLine = interiorLines/2;
        printHorizontalBorder(2, cellWidth, gap);
        cout << "|" << tiles[0].bgColor << centerText(tiles[0].name, cellWidth) << "\033[0m" << "|"
             << getGapString(gap)
             << "|" << tiles[1].bgColor << centerText(tiles[1].name, cellWidth) << "\033[0m" << "|\n";
        for (int j = 0; j < interiorLines; ++j) {
            cout << "|";
            if (j == midLine) {
                string m;
                for (size_t p = 0; p < playerPositions.size(); ++p)
                    if (playerPositions[p] == boardIndex0)
                        m += playerColors[p] + "*\033[0m";
                cout << centerText(m, cellWidth);
            } else cout << string(cellWidth, ' ');
            cout << "|";
            if (j == 0) cout << centerText(dialog, gap);
            else if (j == 1) cout << centerText(subDialog, gap);
            else if (j == 2) cout << centerText(choiceDialog, gap);
            else cout << getGapString(gap);
            cout << "|";
            if (j == midLine) {
                string m;
                for (size_t p = 0; p < playerPositions.size(); ++p)
                    if (playerPositions[p] == boardIndex1)
                        m += playerColors[p] + "*\033[0m";
                cout << centerText(m, cellWidth);
            } else cout << string(cellWidth, ' ');
            cout << "|\n";
        }
        printHorizontalBorder(2, cellWidth, gap);
    }

    // Map linear to display index
    static int posSpecifier(int pos) {
        static int mapping[20] = {19,18,17,16,15,14,12,10,8,6,0,1,2,3,4,5,7,9,11,13};
        return (pos >= 0 && pos < 20) ? mapping[pos] : -1;
    }
};

// Player ANSI colors
const vector<string> Board::playerColors = {
    "\033[38;5;196m",
    "\033[38;5;33m"
};

#endif // BOARD_H
