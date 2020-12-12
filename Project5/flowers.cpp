#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

const char wordfile[] = "C:\\Users\\Jackc\\Desktop\\CS31\\wordfile.txt";

int playOneRound(const char words[][7], int nWords, int wordnum);

int main() { 
	int total = 0;
	int roundsPlayed = 0;
	double avg = 0.0;
	int min;
	int max;
	int score;

	cout.setf(ios::fixed);
	cout.precision(2);

	char w[9000][7];
	int NUMOFWORDS = getWords(w, 9000, wordfile);
	if (NUMOFWORDS < 1) {
		cout << "No words were loaded, so I can't play the game.";
			return 1;
	}
	cout << "How many rounds do you want to play? ";
	int roundsToPlay = -1;
	cin >> roundsToPlay;
	cin.ignore(10000, '\n');
	if (roundsToPlay < 0) {
		cout << "The number of rounds must be positive.";
		return 1;
	}
	
	for (int i = 0; i < roundsToPlay; i++) {
		cout << "\nRound " << i + 1 << endl;
		int randnum = randInt(0, NUMOFWORDS - 1);
		cout << "The mystery word is " << strlen(w[randnum]) << " letters long." << endl;
//		cout << "The word is: " << w[randnum] << endl;
		score = playOneRound(w, NUMOFWORDS, randnum);
		roundsPlayed++;
		total += score;
		avg = (double)total / (double)roundsPlayed;
		if (i == 0) {
			max = score;
			min = score;
		}
		if (score > max) {
			max = score;
		}
		if (score < min) {
			min = score;
		}

		if (score == 1) {
			cout << "You got it in 1 try." << endl;
		}
		else {
			cout << "You got it in " << score << " tries." << endl;
		}
		cout << "Average: " << avg << ", minimum: " << min << ", maximum: " << max << endl;
	}

}

int playOneRound(const char words[][7], int nWords, int wordnum) {
	int tries = 0;
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords) {
		return -1;
	}
	while (true) {
		char trial[10000];
		char word[7];
		strcpy(word, words[wordnum]);		//Copy the secret word into a new array that we can manipulate
		int flowers = 0;
		int bees = 0;
		cout << "Trial word: ";
		cin.getline(trial, 10000);

		bool isLCLetters = true;
		for (int i = 0; i < strlen(trial); i++) {
			if (!islower(trial[i])) {
				isLCLetters = false;
			}
		}
		if (strlen(trial) > 6 || strlen(trial) < 4 || !isLCLetters) {
			cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
		}
		else {
			bool isInArr = false;
			for (int i = 0; i < nWords; i++) {
				if (strcmp(trial, words[i]) == 0) {
					isInArr = true;
				}
			}
			if (!isInArr) {
				cout << "I don't know that word." << endl;
			}
			else {
				for (int i = 0; i < strlen(trial); i++) {		//Run through the whole word only looking for flowers first because flowers take priority over bees
					if (trial[i] == word[i]) {
						flowers++;
						trial[i] = ' ';						//Replace matched letters with illegal chars to prevent duplicate bees
						word[i] = '.';							//Make the chars different so they can't be counted towards bees
					}
				}
				for (int i = 0; i < strlen(trial); i++) {
					for (int i2 = 0; i2 < strlen(word); i2++) {
						if (trial[i] == word[i2]) {
							bees++;
							trial[i] = ' ';						//Replace chars again to avoid duplicating bees
							word[i2] = '.';
						}
					}
				}
				tries++;
				if (flowers == strlen(word)) {
					return tries;
				}
				else {
					cout << "Flowers: " << flowers << ", Bees: " << bees << endl;
				}
			}
		}
	}
}