#ifndef COLORS_H
#define COLORS_H

#include <string>

using namespace std;

class Colors{
    public:
        const string R = "\033[38;2;0;0;0;48;2;255;153;153m";    // pale red bg
        const string O = "\033[38;2;0;0;0;48;2;255;204;153m";    // pale orange bg
        const string Y = "\033[38;2;0;0;0;48;2;255;255;153m";    // pale yellow bg
        const string G = "\033[38;2;0;0;0;48;2;153;255;153m";    // pale green bg
        const string B = "\033[38;2;0;0;0;48;2;153;204;255m";    // pale blue bg
        const string V = "\033[38;2;0;0;0;48;2;255;153;255m";    // pale violet bg
        const string BR = "\033[48;5;223m\033[30m";              // pale brown bg
        const string PG = "\033[48;5;250m\033[30m";              // pale gray bg
        const string W = "\033[48;5;15m\033[30m";                // pure white bg
        const string RR = "\033[41m\033[97m";                    // red bg with black text

        // Text-only colors
        const string r = "\033[38;2;255;153;153m";               // pale red text
        const string o = "\033[38;2;255;204;153m";               // pale orange text
        const string y = "\033[38;2;255;255;153m";               // pale yellow text
        const string g = "\033[38;2;153;255;153m";               // pale green text
        const string b = "\033[38;2;153;204;255m";               // pale blue text
        const string v = "\033[38;2;255;153;255m";               // pale violet text
        const string br = "\033[38;5;223m";                      // pale brown text
        const string pg = "\033[38;5;250m";                      // pale gray text
        const string w = "\033[38;5;15m";                        // pure white text
        
        // Normal tone text colors
        const string rr  = "\033[38;2;255;0;0m";        // normal red text 
        const string oo  = "\033[38;2;255;140;0m";     // normal orange text
        const string yy  = "\033[38;2;255;255;0m";     // normal yellow text
        const string gg  = "\033[38;2;0;128;0m";       // normal green text
        const string bb  = "\033[38;2;0;0;255m";       // normal blue text
        const string vv  = "\033[38;2;148;0;211m";     // normal violet text
        const string brr = "\033[38;2;165;42;42m";     // normal brown text
        const string pgg = "\033[38;2;128;128;128m";   // normal gray text
        const string ww  = "\033[38;2;255;255;255m";   // normal white text


        const string re = "\033[0m";                             // reset color

        // Symbols with color
        const string marker = string(bb + "*" + re + " " + rr + "*" + re);
        const string dollar = string(g + "$" + re);
        const string c_cc = string(v + "?" + re + " " + br + "###" + re);
        const string jail = string(oo + "| | |" + re);
        const string turn = string(rr + ">" + re);
        const string owned = string(rr + "!" + re);
        const string property = string(w + "#" + re);
        const string houser = string(rr + "#" + re);
        const string houseg = string(gg + "#" + re);
        const string houseb = string(bb + "#" + re);
        const string housey = string(yy + "#" + re);
        const string bankrupt = string(r + "--$" + re);
        const string tax = string(rr + "-$" + re);
        const string win = string(g + "$++" + re);
        const string util = string(ww + "#" + re);
        const string free = string(rr + "X" + re);
        const string go = string(rr + ">-->" + re);
    
};

#endif // COLORS_H
