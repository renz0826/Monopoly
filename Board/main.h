#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Main {
    public:
        // Constants for board layout
        static const int numBoxes = 6;      // number of boxes in the standard row
        static const int cellWidth = 13;    // width of each box's interior
        static const int cellHeight = 5;    // number of interior blank lines for standard row
        static const int gap = 0;                     // gap between boxes in the standard row
        static const int specialGap = 55;
        static const int specialInterior = 4;
        static const int boxWidth = 83;             // Fixed width for the dialog box.

        // Color constants
        inline static const string R = "\033[38;2;0;0;0;48;2;255;153;153m";   // pale red
        inline static const string O = "\033[38;2;0;0;0;48;2;255;204;153m";   // pale orange
        inline static const string Y = "\033[38;2;0;0;0;48;2;255;255;153m";   // pale yellow
        inline static const string G = "\033[38;2;0;0;0;48;2;153;255;153m";   // pale green
        inline static const string B = "\033[38;2;0;0;0;48;2;153;204;255m";   // pale blue
        inline static const string V = "\033[38;2;0;0;0;48;2;255;153;255m";   // pale violet
        inline static const string BR = "\033[48;5;223m\033[30m";             // pale brown
        inline static const string PG = "\033[48;5;250m\033[30m";             // pale gray
        inline static const string W = "\033[48;5;15m\033[30m";               // white
        inline static const string RR = "\033[41m\033[97m";                   // red

        void boardInfo();


};

#endif // MAIN_H