#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ANSI background colors
const string RESET = "\x1b[0m";
const string BG_BLACK = "\x1b[40m";
const string BG_WHITE = "\x1b[107m";
const string BG_RED = "\x1b[41m";

int main() {
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
            else cout << " "; // fallback
        }
        cout << '\n';
    }
    
    char choice;
    
    cout << "+---------------------------------------------------------------+" << endl;
	cout << "|  Please enter the number of the action you want to perform.   |" << endl;
	cout << "+---------------------------------------------------------------+" << endl;
	cout << "|                     [1] Play Game                             |" << endl;
	cout << "|                     [2] How to Play?                          |" << endl;
	cout << "|                     [3] Exit                                  |" << endl;
	cout << "+---------------------------------------------------------------+" << endl;
	cout << endl;
	cout << "     Enter Choice (1-3): "; cin >> choice;
	
    return 0;
}
