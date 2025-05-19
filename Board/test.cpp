#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string RESET = "\x1b[0m";
const string BG_BLACK = "\x1b[40m";
const string BG_WHITE = "\x1b[107m";
const string BG_RED = "\x1b[41m";

struct Tile {
	string name;
	int cost;
	int rent;
	string color;
};

	vector <tile> tiles = {
	        "Go",
	        "Redford Avenue",
	        "Community Chest",
	        "Railroad Station",
	        "Roselawn Street",
	        "Jail",
	        "Greenwich Road",
	        "Income Tax",
	        "Garden City Lane",
	        "Electric Company",  // (Utility)
	        "Free Parking",
	        "Blue Harbor Drive",
	        "Chance",
	        "Water Works",       // (Utility)
	        "Bayview Boulevard",
	        "Go to Jail",
	        "Chance",
	        "Sunrise Strip",
	        "Internet Provider", // (Utility)
	        "Community Chest"
	    };
	
	vector <string> createTile(const string&name){
		vector <string> tile;
		tile.push_back("+---------+");
		tile.push_back("|         |")
	} 
int main() {

}