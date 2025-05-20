#include <iostream>
#include <vector>
#include <string>
#include "move.h"
using namespace std;

int main() {
    // Draw the board layout.
    int p1, p2;

    p1 = 2;
    p2 = 3;

    Main game(p1, p2);
    game.drawBoard();

    // Ask a question (for example purposes).
    string response = game.askPlayerQuestion("Do you want to buy? ", 83);

    return 0;
}