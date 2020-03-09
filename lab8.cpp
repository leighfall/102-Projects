//Name: Autumn Henderson
//Date: October 17th, 2018
//Title: Lab 8
//Description: Program takes in number of players and deals two unique cards
//to each player. It then adds the value of the cards and outputs which cards
//each player has and what their score is.

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

//Functions created in program
int GetRandom (int minimum, int maximum);
string DealCard (int cards[], int playerNum);
int ScoreHand (int cards[], int player);
		
int main() {
	
	//Seeds rand
	srand(time(NULL));

	//Variables for game
	int players;
	int playerNum;
	int arrayCards[52] = {0};
	string cardType1;
	string cardType2;
	int playerScore;

	//Determines how many players are playing the game
	cout << "How many players? ";
	cin >> players;

	//For loop that will run for each player
	for (unsigned int i = 1; i <= players; ++i) {
		
		playerNum = i;

		//Determines the two card types the player has
		cardType1 = DealCard(arrayCards, playerNum);
		cardType2 = DealCard(arrayCards, playerNum);

		//Determines the player's score
		playerScore = ScoreHand(arrayCards, playerNum);

		//Outputs the player's cards and score
		cout << "Player " << i << " has cards: " << left << setw(20) <<
			( cardType1 + " " + cardType2) << "(" << playerScore << ")\n";
	}

	return 0;
}

//GetRandom generates a number between 0 and 51
int GetRandom (int minimum, int maximum) {

	return rand() % ((maximum - minimum) + 1);
}

//DealCard takes an array of 52 cards and whichever player the program is on
//and deals two cards to the player.
string DealCard (int cards[], int playerNum) {

	int randomCard;
	int minimum = 0;
	int maximum = 51; 
	const string cardValue[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	const string cardSuit[4] = {"H", "D", "S", "C"};

	//Checks to see if card has been dealt
	do {		
		randomCard = GetRandom(minimum, maximum);
		
		if (cards[randomCard] == 0) 
			break;

	} while (true);

	//Assigns player to an index
	cards[randomCard] = playerNum;
	
	//Converts index into string of card types
	return cardValue[(randomCard + 13) % 13] + cardSuit[randomCard / 13];
}

//ScoreHand takes an array of 52 cards and whichever player the program
//is on and adds the player's cards together to generate a score.
int ScoreHand (int cards[], int player) {

	int score = 0;

	//For loop runs through the array to find where the player number is.
	for (unsigned int i = 0; i < 51; ++i) {
		if (cards[i] == player) {

			//If the card is 10, J, Q, or K, gets the value 10.
			if (((i+13) % 13) > 9) {
				score += 10;
			}
			//Else the value is 1 - 9
			else {
				score += (((i + 13) % 13) + 1);
			}
		}
	}	

	return score;
}
