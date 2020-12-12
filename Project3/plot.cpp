#include "grid.h"
#include <cctype>
#include <iostream>
#include <string>

//constants
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;


using namespace std;
//prototypes
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);

int main()
{
	setSize(20, 30);
	char currentChar = '*';		//set defaults
	int currentMode = FG;
	for (;;) //endless for loop that only ends with break;
	{
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);		//read input
		if (cmd == "")		// break if blank
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status)
		{
		case 0:			//print error messages depending on return type of performCommands
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}
int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
	int dir = HORIZ;
	int dist = 0;
	int currR = 1;	//declare variables and setup defaults
	int currC = 1;
	int skip = 0;
	for (int i = 0; i < commandString.length(); i++) { //(signed unsigned)
		dir = HORIZ;
		dist = 0;				// resets these variables to these values to make switch statement simpler
		skip = 0;

		switch (toupper(commandString[i])) {
		case'V':
			dir = VERT; //because dir defaults to Horiz, case V can just change dir and then feed into case H
		case'H':
			if (commandString[i + 1] == '-') {
				if (isdigit(commandString[i + 2]) && isdigit(commandString[i + 3])) {				// if the # has two digits, we mult the first one by ten and add it to the second one to get a single integer
					dist += -((commandString[i + 2] - '0') * 10 + ((int)commandString[i + 3] - '0')); //changes the char to an int by subtracting its value from '0' since the integer value of the char '1' is one more than '0' etc
					skip = 3;			//we keep track of an int called skip that we add to i in the for loop to skip over the numbers following h or v or the chars following f or b
				}
				else if (isdigit(commandString[i + 2])) {
					dist += -((commandString[i + 2] - '0'));
					skip = 2;
				}
				else {
					badPos = i + 2;				//sets badpos to where we expected a char
					return 1;
				}
			}
			else if (isdigit(commandString[i + 1]) && isdigit(commandString[i + 2])) {
				dist += (commandString[i + 1] - '0') * 10 + ((int)commandString[i + 2] - '0');
				skip = 2;
			}
			else if (isdigit(commandString[i + 1])) {
				dist += (commandString[i + 1] - '0');
				skip = 1;
			}
			else {
				badPos = i + 1;
				return 1;
			}

			if (!((((dir == HORIZ) && ((currC + dist) <= getCols()) && ((currC + dist) > 0))
				|| ((dir == VERT) && ((currR + dist) <= getRows()) && ((currR + dist) > 0))		// if adding the desired distance in the intended direction to the current position would extend outside the grid, set badpos and return 2
				))) {
				badPos = i;
				return 2;
			}
			plotLine(currR, currC, dist, dir, plotChar, mode);
			if (dir == HORIZ) {
				currC += dist;
			}						//update our current values
			else {
				currR += dist;
			}
			break;

		case'B':
			mode = BG;									// sets mode
			if (!isprint(commandString[i + 1])) {
				badPos = i + 1;
				return 1;					//checks to see if the input char isprint and breaks if it isn't
			}
			plotChar = commandString[i + 1];		//sets char
			skip = 1;
			break;
		case'F':
			mode = FG;
			if (!isprint(commandString[i + 1])) {
				badPos = i + 1;
				return 1;
			}
			plotChar = commandString[i + 1];
			skip = 1;
			break;
		case'C':
			clearGrid();
			currC = 1;
			currR = 1;
			plotChar = '*';
			mode = FG;			//reset to defaults
			break;
			
		default:
			badPos = i;				//sets badpos and returns 1 if the command isnt HVBF or C
			return 1;
		}
		i += skip;		//adds skip to i so we don't try to use numbers as a command, etc
	}
	return 0;
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {
	if (!((dir == HORIZ || dir == VERT)
		&& (fgbg == FG || fgbg == BG)
		&& (isprint(plotChar))									// if a single input parameter is bad, return true
		&& (((dir == HORIZ) && ((c + distance) <= getCols()) && ((c + distance) > 0))
			|| ((dir == VERT) && ((r + distance) <= getRows()) && ((r + distance) > 0))
			))) {
		return false;
	}

	for (int i = 0; i <= abs(distance); i++) {
		if (getChar(r, c) == ' ' || fgbg == FG) {		// only puts a char there if in foreground mode or if the spot is blank
			setChar(r, c, plotChar);
		}
		if (dir == HORIZ) {
			if (distance > 0) {
				c++;
			}
			else if (distance < 0) {
				c--;
			}
		}
		else {
			if (distance > 0) {
				r++;
			}
			else if (distance < 0) {
				r--;
			}
		}
	}
	return true;
}


