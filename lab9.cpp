//Name: Autumn Henderson
//Date: October 31st, 2018
//Title: Lab 9
//Description: Program simulates a Blackjack game where you and a dealer are
//randomly dealt two cards and play Blackjack until one of you wins.

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

//Functions created in program
int GetRandom (int minimum, int maximum);
string DealCard (int cards[], int player);
int ScoreHand (int cards[], int player);
void InitializeCards (int cards[]);	

int main() {
	
	//Seeds rand
	srand(time(NULL));

	//Variables for game
	int cards[52];
	string answer;
	bool decided = false;

	//Player Variables
	int playerNum = 1;
	string playerCardType;
	int playerScore;
	
	//Dealer Variables
	int dealerNum = 2;
	string dealerCardType;
	int dealerScore;


	//Initializes array of cards to 0
	InitializeCards(cards);
	
	//Starts the game for the player and dealer (ONLY RUNS ONCE!)
	dealerCardType = DealCard(cards, dealerNum) + " " + DealCard(cards, dealerNum);
	dealerScore = ScoreHand(cards, dealerNum);

	cout << "Dealer has cards: " << left << setw(20) << dealerCardType << "(" << dealerScore
		<< ")" << "\n";

	playerCardType = DealCard(cards, playerNum) + " " + DealCard(cards, playerNum);
	playerScore = ScoreHand(cards, playerNum);

	cout << "You have cards  : " << left << setw(20) << playerCardType << "(" << playerScore
		<< ")" << "\n";

	//Player Loop
	do {
		//Will ask player to hit or stand until valid response given
		do {
			cout << "Hit or stand     ? ";
			cin >> answer;
		} while (!(answer == "hit" || answer == "stand"));

		cout << "\n";

		//If statement allows player to either keep playing or adds score
		if (answer == "stand") {
			break;
		}
		
		//Else statement adds scores and determines whether to ask hit or stand again.
		else {
			playerCardType += " " + DealCard(cards, playerNum);
			playerScore = ScoreHand(cards, playerNum);
			cout << "Dealer has cards: " << left << setw(20) << dealerCardType << "(" << dealerScore
				<< ")" << "\n";
			cout << "You have cards  : " << left << setw(20) << playerCardType << "(" << playerScore
				<< ")" << "\n";

			//Player has automatically lost
			if (playerScore > 21) {
				cout << "Player busts, dealer wins! \n";
				decided = true;
				break;
			}
			//Player has automatically won
			else if (playerScore == 21) {
				cout << "Player wins!\n";
				decided = true;
				break;
			}
		}

	} while(true);

	//Dealer loop
	if ((answer == "stand") && (decided == false)) {
		do {
			//Dealer will hit
			if (dealerScore < 18) {
				dealerCardType += " " + DealCard(cards, dealerNum);
				dealerScore = ScoreHand(cards, dealerNum);
				cout << "Dealer hits     : " << left << setw(20) << dealerCardType << "(" <<
					dealerScore << ")\n";
			}
			//Dealer will stand
			else if ((dealerScore > 17) && (dealerScore < 21)) {
				cout << "Dealer stands   : " << left << setw(20) << dealerCardType << "(" <<
					dealerScore << ")\n";
				break;
			}
			//Dealer has automatically won
			else if (dealerScore == 21) {
				cout << "Dealer wins!\n";
				decided = true;
				break;
			}
			//Dealer has automatically lost
			else {
				cout << "Dealer busts, player wins!\n";
				decided = true;
				break;
			}

		} while(true);
	}

	//Decide winner 
	if (decided == false) {
		if (dealerScore == playerScore) {
			cout << "Player and dealer draw.\n";
		}
		else if (dealerScore > playerScore) {
			cout << "Dealer wins!\n";
		}
		else {
			cout << "Player wins!\n";
		}
	}

	return 0;
}

//Initializes array to 0
void InitializeCards (int cards[]) {

	for (unsigned int i = 0; i < 52; ++i)
		cards[i] = 0;
}

//GetRandom generates a number between 0 and 51
int GetRandom (int minimum, int maximum) {

	return rand() % ((maximum - minimum) + 1);
}

//DealCard takes an array of 52 cards and whichever player the program is on
//and deals two cards to the player.
string DealCard (int cards[], int player) {

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
	cards[randomCard] = player;
	
	//Converts index into string of card types
	return cardValue[(randomCard + 13) % 13] + cardSuit[randomCard / 13];
}

//ScoreHand takes an array of 52 cards and whichever player the program
//is on and adds the player's cards together to generate a score.
int ScoreHand (int cards[], int player) {

	int score = 0;

	//For loop runs through the array to find where the player number is.
	for (unsigned int i = 0; i < 52; ++i) {
		if (cards[i] == player) {

			//If the card is 10, J, Q, or K, gets the value 10.
			if ((((i+13) % 13) +1) > 9) { 
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
