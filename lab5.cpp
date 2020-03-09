//Name: Autumn Henderson
//Date: September 26th, 2018
//Title: Lab 5
//Description: This program takes scores from players from a bowling game and
//prints out all players and their scores and who did the best and worst in the
//game.

#include <iostream>
#include <vector>

using namespace std;

const int ARRAY_SIZE = 21;

int main() {

	//Array and Vector Variables
	vector<string> names;
	vector<double> totalScores;
	int scores[ARRAY_SIZE];

	//Tracker Variables
	bool actualPlayers = false;
	int frameIterator;
	int i;
	int j;
	double addedScores;

	//CIN Variables
	string playerName;
	double firstRoll, secondRoll, thirdRoll;

	//Min and Max Variables
	string maxName, minName;
	double maxScore, minScore;

	do {
		cout << "Enter player's name (done for no more players): ";
		cin >> playerName;
		
		//If statement explicitly breaks the loop when player enters "done".
		if (playerName == "done") {
			break;
		}

		//If we get to this statement, there is at least one player.
		actualPlayers = true;

		//Adds in name to vector
		names.push_back(playerName);

		//Resets trackers
		frameIterator = 1;
		addedScores = 0;
		
		//For loop initializes/clears scores array.
		for (i = 0; i < ARRAY_SIZE; ++i) {
			scores[i] = 0;
		}

		//For loop to enter basic rolls into array.
		for (i = 0; i < ARRAY_SIZE; ++i) {

			cout << "Enter score for frame " << frameIterator << ", roll 1: ";
			cin >> firstRoll;
			scores[i] = firstRoll;

			++i;

			//if statement checks to see if there is a second roll
			if (firstRoll < 10 || frameIterator == 10) {
				cout << "Enter score for frame " << frameIterator << ", roll 2: ";
				cin >> secondRoll;
				scores[i] = secondRoll;
			}
			else {
				scores[i] = 0;
			}

			//if statement checks for third roll on 10th frame
			if (frameIterator == 10 && ((firstRoll == 10) || (firstRoll + secondRoll == 10))){
				cout << "Enter score for frame " << frameIterator << ", roll 3: ";
				cin >> thirdRoll;
				scores[21] = thirdRoll;
				break;
			}

			++frameIterator;
		}

		//Adds scores together
		for (i = 0; i < (ARRAY_SIZE - 1); ++i) {
			
			//if score was a strike, adds that plus next two actual rolls
			if (scores[i] == 10) {
				addedScores += scores[i];
				if (scores[i+2] == 10){
					addedScores += (scores[i+2] + scores[i+4]);
				}
				else {
					addedScores += (scores[i+2] + scores[i+3]);
				}
			}
			//if score was a spare, adds that plus next roll
			else if ((scores[i] + scores[i + 1] == 10)) {
				addedScores += (scores[i] + scores[i+1] + scores[i+2]);
			}
			//else the score was neither a spare or strike and just adds the two rolls
			else { 
				addedScores += (scores[i] + scores[i+1]);
			}

			++i;
		}

		//Adds in last frame + 10 if perfect bowl
		if (addedScores == 280) 
			addedScores += (scores[21] + 10);
		else
			addedScores += (scores[21]);

		//Inserts total score into vector
		totalScores.push_back(addedScores);

	}while (true);

	//If statement for whether there were players and, if so, prints
	//scores and best and worst.
	if (actualPlayers == false) {
		cout << "No players were entered.\n";
	}
	else {

		cout << "\n";
		//For loop prints names and scores
		for (i = 0; i < names.size(); ++i) {
			cout << names.at(i) << " scored " << totalScores.at(i) << ".\n";
		}

		//For loop compares scores
		for (i = 0; i < names.size(); ++i) {

			if (i == 0) {
				maxName = minName = names.at(i);
				maxScore = minScore = totalScores.at(i);
			}
			else if (totalScores.at(i) < minScore) {
				minScore = totalScores.at(i);
				minName = names.at(i);
			}
			else if (totalScores.at(i) > maxScore) {
				maxScore = totalScores.at(i);
				maxName = names.at(i);
			}
		}
		
		cout << minName << " did the worst by scoring " << minScore << ".\n";
		cout << maxName << " won the game by scoring " << maxScore << ".\n";
	}

	return 0;
}
