#ifndef PIXEL_H
#define PIXEL_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class PIXEL{
    public:
        void pxlArt(){
        const string RESET = "\x1b[0m";
        const string BG_BLACK = "\x1b[40m";
        const string BG_WHITE = "\x1b[107m";
        const string BG_RED = "\x1b[41m";
        
        vector<string> pixelArt = {
            "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
            "RRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWWRRRWWRRWRRRWRWRRR",
            "RRRWWRWWRRWRRWWRWRRWRRRRRWWRWWRWRRWRWWRWRWRRWRWRWRWRRWRWRRRWRWRRR",
            "RRRWRWRWRRWRRWRWWRRWRRWWRWRWRWRWRRWRWRWWRWRRWRWWRRWRRWRWRRRRWRRRR",
            "RRRWRRRWRWWWRWRRWRWWWRRRRWRRRWRRWWRRWRRWRRWWRRWRRRRWWRRWWWRRWRRRR",
            "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
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
}

};

#endif // PIXEL_H
