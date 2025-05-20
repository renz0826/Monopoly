// pregame.h
#ifndef PRE_GAME_H
#define PRE_GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class PreGame {
    public:
        static constexpr int TOTAL_WIDTH = 90;
        static constexpr int CELL_WIDTH = 41;

        // ANSI color codes
        static const string RESET;
        static const string BG_BLACK;
        static const string BG_WHITE;
        static const string BG_RED;

        // Format text for a table cell (without borders), padded to cellWidth
        static string formatCell(const string &label, int cellWidth, int padding = 2);

        // Print two columns side by side with fixed cell width
        static void printSideBySideBoxes(const vector<string>& labels1,
                                        const vector<string>& labels2);

        // Print pixel art background
        static void printPixelArt(const vector<string>& pixelArt);

        // Utility to find max label length
        static int maxLabelLength(const vector<string>& labels);
};

    // Static member definitions
    const string PreGame::RESET    = "\x1b[0m";
    const string PreGame::BG_WHITE = "\x1b[107m";
    const string PreGame::BG_RED   = "\x1b[41m";

    inline string PreGame::formatCell(const string &label, int cellWidth, int padding) {
        int totalSpace = cellWidth - 2; // inside box
        int availableSpace = totalSpace - 2 * padding;
        string trimmed = label.substr(0, min((int)label.size(), availableSpace));
        int extra = availableSpace - (int)trimmed.size();
        return string(padding, ' ') + trimmed + string(padding + extra, ' ');
    }

    inline void PreGame::printSideBySideBoxes(const vector<string>& labels1,
                                            const vector<string>& labels2) {
        string hBorder = "+" + string(CELL_WIDTH, '-') + "+" + string(CELL_WIDTH, '-') + "+";
        cout << hBorder << "";
        size_t rows = min(labels1.size(), labels2.size());
        for (size_t i = 0; i < rows; ++i) {
            cout << "|" << formatCell(labels1[i], CELL_WIDTH)
                << "|" << formatCell(labels2[i], CELL_WIDTH) << "|";
            if (i == 0) cout << hBorder << "";
        }
        cout << hBorder << "";
    }

    inline void PreGame::printPixelArt(const vector<string>& pixelArt) {
        for (const auto &row : pixelArt) {
            for (char c : row) {
                if (c == 'W') cout << BG_WHITE << " " << RESET;
                else if (c == 'B') cout << BG_BLACK << " " << RESET;
                else if (c == 'R') cout << BG_RED << " " << RESET;
                else cout << " ";
            }
            cout << '\n';
        }
    }

    inline int PreGame::maxLabelLength(const vector<string>& labels) {
        int maxLen = 0;
        for (const auto &s : labels) maxLen = max(maxLen, (int)s.length());
        return maxLen;
    }

#endif // PRE_GAME_H
