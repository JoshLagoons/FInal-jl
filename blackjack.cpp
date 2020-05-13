/**
	Joshua Lagunas
    5/12/20
    blackjack game
    sources that I used for help
    https://docs.microsoft.com/en-us/cpp/cpp/void-cpp?view=vs-2019
    https://www.geeksforgeeks.org/c-classes-and-objects/?ref=lbp
    https://docs.microsoft.com/en-us/cpp/cpp/declarations-and-definitions-cpp?view=vs-2019
    https://support.microsoft.com/en-us/help/99261/how-to-performing-clear-screen-cls-in-a-console-application
    http://www.cplusplus.com/reference/ctime/time/


*/
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
struct Player {
unsigned int score = 0;
unsigned int hand = 0;
}

void menu(bool cardsDeal[], int HouseHand[], int PlayerHand[], int Housecardcount, int Playercardcount, int a);
void computerplayer( bool cardDeal[], int Househand[], int PlayerHand[], int Housecardcount, int Playercardcount, int a);
void player( bool cardDeal[], int Househand[], int PlayerHand[], int Housecardcount, int Playercardcount, int a);
void scores(int a);
void shuffle(bool cardDeal[]);
void displayingcard(int card);
void displayinghand(int hand[], const int cardCount);
void displayingSandH(int HouseHand[], const int housecardCount, int PlayerHand[]. const int Playercardcount);
int nextCard(bool cardsDeal[]);
int scorehand(int hand[], const int cardCount);
using namespace std;



int main()
{
	// For random numbers
	time_t qTime;
	time(&qTime);
	srand(qTime);

	// Declarations
	int count = 0;
	bool cardDeal[52];
	int HouseCardCount = 0;
	int HouseHand[12];
	int Playercardcount = 0;
	int PlayerHand[12];
	int a = 0;
	const int PLAYERS = 2;
	player users[PLAYERS];

	// The menu for which game mode to play in
	menu(cardDeal, HouseHand, PlayerHand, HouseCardCount, Playercardcount, a);
	
	// For windows to show final screen
	system("pause");
	return 0; // Return success
}

void computerplayer(bool cardDeal[], int HouseHand[], int PlayerHand[], int HouseCardCount, int Playercardcount, int a)
{

	bool jokerha = true;
	int choice = 1;


	// Loops the hand
	while (jokerha = true) {

		// Shuffles the cards
		shuffle(cardDeal);

		// Two cards are delt for each player and house
		PlayerHand[0] = nextCard(cardDeal);
		HouseHand[0] = nextCard(cardDeal);
		PlayerHand[1] = nextCard(cardDeal);
		HouseHand[1] = nextCard(cardDeal);
		HouseCardCount = 2;
		Playercardcount = 2;

		char Playerchoice;
		bool Playerhits = true;
		int Playerscore = scoreHand(PlayerHand, Playercardcount);

	
		// The start of a new hand
		cout << "><><><><><><><><><|| Black Jack || ><><><><><><><><><><><" << endl;

		// Get Player's hits. Calculate the score and it displays after each hit.
		do {

			// Displays the dealt cards, but only the House's second card.
			cout << "House's Hand" << endl;
			cout << "** ";
			displayingcard(HouseHand[1]);
			cout << endl;
			cout << "\nPlayer's Hand: Score = " << scoreHand(PlayerHand, Playercardcount) << endl;
			displayinghand(PlayerHand, Playercardcount);

			// Ask the Player whether he wants a hit or stay
			if (PlayerHand > Playerhits) {
				cout << "\nHit stay or double: ";
				cin >> Playerchoice;
			}
			else {
				cout << "\nHit or Stay (type these in lowercase): ";
				cin >> Playerchoice;
			}
			if (Playerchoice == 'hit') {
				PlayerHand[Playercardcount] = nextCard(cardDeal);
				++Playercardcount;
			}
			else if (Playerchoice == 'stay') {
				Playerhits = false;
			}
			else if ((Playerchoice == 'double') && (users[x].score > users[x].bet)) {
				PlayerHand[Playercardcount] = nextCard(cardDeal);
				++Playercardcount;
				Playerhits = false;
			}
			else {
				cout << "Try Again!" << endl;
			}
			cout << endl;

			// Get the Player's current score to update and check for bust.
			Playerscore = scoreHand(PlayerHand, Playercardcount);
		} while (Playerhits && Playerscore < 22);

		// Once the player is done, a check is taken place to see if  busted
		if (Playerscore > 21) {

			// The Player busted. The House wins.
			system("cls");
			scores(a);
			cout << "The House Wins!" << endl;
			cout << "You lost" << endl;
			displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, Playercardcount);
		}
		else {

			// If the player didn't bust, then the house takes hits below 17
			int HouseScore = scoreHand(HouseHand, HouseCardCount);
			while (HouseScore < 17) {
				HouseHand[HouseCardCount] = nextCard(cardDeal);
				++HouseCardCount;
				HouseScore = scoreHand(HouseHand, HouseCardCount);
			}

			bool HouseBusts = (HouseScore > 21);
			if (HouseBusts) {
				// The House busted. Player wins
				system("cls");
				scores(a);
				cout << "You Win!" << endl;
				displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, Playercardcount);
			}
			else {

				// Compare scores and determine the winner
				if (Playerscore == HouseScore) {

					// if you tie
					system("cls");
					scores(a);
					cout << "Tie!" << endl;
					displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, Playercardcount);
				}
				else if (Playerscore > HouseScore) {

					// The Player wins
					system("cls");
					scores(a);
					cout << "You Win!" << endl;
					displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, Playercardcount);
				}
				else {

					// The House wins
					system("cls");
					scores(a);
					cout << "The House Wins!" << endl;
					displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, Playercardcount);
				}
			}
		}

		system("pause");
		system("cls");
		cout << "Would you like to play another game or end? yes or no " << endl;
		cin >> choice;
		while (!((choice == 'yes') || (choice == 'no'))) { // incase they pick differently
			cout << "You entered the wrong choice.\nPlease enter again: ";
			cin >> choice;
		}

		if (choice == no) {
			jokerha = false;
		}
		else {
			jokerha = true;
			system("cls");
		}
	}
}


// This is where the deck is shuffled
void shuffle(bool cardDeal[]) {

	for (int shuffy = 0; shuffy < 52; ++shuffy {
		cardDeal[shuffy] = false;
	}
}

//This shows that the cards are getting displayed to the player
void displayingcard(int Card) {

	// Displays the Rank
	const int ranking = (Card % 13);

	if (ranking == 0) {
		cout << "Ace/";
	}
	else if (ranking < 9) {
		cout << (ranking + 1);
	}
	else if (ranking == 9) {
		cout << "Ten";
	}
	else if (ranking == 10) {
		cout << "Jack/";
	}
	else if (ranking == 11) {
		cout << "Queen/";
	}
	else {
		cout << "King/";
	}

	// Displays the Suit
	const int Suit = (Card / 13);

	if (Suit == 0) {
		cout << "Club";
	}
	else if (Suit == 1) {
		cout << "Diamond";
	}
	else if (Suit == 2) {
		cout << "Heart";
	}
	else {
		cout << "Spade";
	}
}


//When the whole hand is displayed and different ro displaying cards but shows the whole hand
void displayinghand(int Hand[], const int CardCount) {

	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = Hand[CardIndex];
		displayinghard(NextCard);
		cout << " ";
	}
	cout << endl;
}

//When a card is delt to the player and the computer bases on the hit
int nextCard(bool cardDeal[]) {

	bool Carddeal = true;
	int NewCard = -1;
	do {
		NewCard = (rand() % 52);
		if (!cardDeal[NewCard]) {
			cardDeal = false;
		}
	} while (cardDeal);
	return NewCard;
}

//the score hand and if the player gets 1 ace and 1 jack the hand score is going to be 21.
int scoreHand(int Hand[], const int CardCount) {

	int AceCount = 0;
	int Score = 0;
	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = Hand[CardIndex];
		const int ranking = (NextCard % 13);
		if (ranking == 0) {
			++AceCount;
			++Score;
		}
		else if (ranking < 9) {
			Score = Score + (ranking + 1);
		}
		else {
			Score = Score + 10;
		}
	}
	while (AceCount > 0 && Score < 12) {
		--AceCount;
		Score = Score + 10;
	}
	return Score;
}

//Results it shows the handscored of the player and the computer
void displaySandH(int HouseHand[], const int HouseCardCount, int PlayerHand[], const int Playercardcount) {

	cout << "House's Hand: Score = " << scoreHand(HouseHand, HouseCardCount) << endl;
	displayinghand(HouseHand, HouseCardCount);
	cout << "\nPlayer's Hand: Score = " << scoreHand(PlayerHand, Playercardcount) << endl;
	displayinghand(PlayerHand, Playercardcount);
	cout << endl;
}
