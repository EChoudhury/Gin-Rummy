#include "Card.h"
#include "Dealing.h"
#include "Gameplay.h"
#include "ScoreKeeper.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main() {

	system("clear");

	srand(time(0));

	vector<Card> deck;

	stack<Card> draw;
	stack<Card> discard;
	vector<Card> playerHand;
	vector<Card> compHand;

	createDeck(draw, deck);
	
	//********************************************

	dealToHands(10, playerHand, draw);
	dealToHands(10, compHand, draw);
	dealToDiscard(1, discard, draw);

	//cout << draw.size() << " " << playerHand.size() << " " << compHand.size() <<  " " << discard.size() << endl;
	
	//********************************************
	
	ScoreKeeper pScore;
	ScoreKeeper cScore;

	bool end = false;
	bool valid = false;
	int turn = 1;
	int round = 1;
	int winType;
	int begin;

cout << "Welcome to" << endl << endl;                                                                                                      
cout << "  ,ad8888ba,  88                88888888ba                                                               " << endl;
cout << " d8''    `'8b ''                88      '8b                                                              " << endl;
cout << "d8'                             88      ,8P                                                              " << endl;
cout << "88            88 8b,dPPYba,     88aaaaaa8P' 88       88 88,dPYba,,adPYba,  88,dPYba,,adPYba,  8b       d8" << endl;
cout << "88      88888 88 88P'   `'8a    88''''88'   88       88 88P'   '88'    '8a 88P'   '88'    '8a `8b     d8'" << endl;
cout << "Y8,        88 88 88       88    88    `8b   88       88 88      88      88 88      88      88  `8b   d8' " << endl;
cout << " Y8a.    .a88 88 88       88    88     `8b  '8a,   ,a88 88      88      88 88      88      88   `8b,d8'  " << endl;
cout << "  `'Y88888P'  88 88       88    88      `8b  `'YbbdP'Y8 88      88      88 88      88      88     Y88'   " << endl;
cout << "                                                                                                  d8'    " << endl;
cout << "   Erich, Thomas, and Grant                                                                      d8'     " << endl;	
         
        sleep(3);
	cout << endl << "Press ENTER to continue..." << endl;

	getchar(); 
	system("clear");

	string title ="Hello! Welcome to Gin Rummy! To play, please select (1), to read the instructions, please type (2)! (1/2):\n>";
	begin = input(valid,title,2,1);

	if (begin == 2) {  
		system("clear");
		cout << "This is how to play!" << endl;
		cout << "Press ENTER to play!" << endl;
		cin.clear();
		cin.ignore();
		getchar();
		cout << "Ok! Lets play!" << endl;
		sleep(1);
	}                                      
	
	system("clear");

	while (pScore.getScore() < 100 && cScore.getScore() < 100) {

		winType = 0;

		cout << "ROUND " << round << endl;

		while (end == false && draw.size() != 0) {

			cout << "Turn: " << turn << endl << endl;		

			if (turn == 1) {
				roundStart(compHand, playerHand, discard);
				system("clear");
				turn++;
			}
		
			else {
				playerTurn(playerHand, draw, discard, end, pScore);
				system("clear");
				compTurn(compHand, draw, discard, end, cScore);
				sleep(3);
				system("clear");
				turn++;
			}

		}
			
		if (cScore.checkWin() < 10 || pScore.checkWin() < 10) {
			
			//Computer Win
			if (cScore.checkWin() != 10) {
				cout << "COMPUTER WINS ROUND " << round	<< endl;			
				winType = cScore.checkWin();
				roundScoring(cScore, pScore, winType);
				cScore.updateWins();
			}

			//Player Win
			else if (pScore.checkWin() != 10) {
				cout << "PLAYER WINS ROUND " << round	<< endl;
				winType = pScore.checkWin();
				roundScoring(pScore, cScore, winType);
				pScore.updateWins();
			}	

		}

		else {
						
			cout << "Draw Pile is Empty!" << endl;
			//Computer Win
			if (cScore.getDeadwood() < pScore.getDeadwood()) {
				cout << "COMPUTER WINS ROUND " << round	<< endl;			
				cScore.updateScore(pScore.getDeadwood() - cScore.getDeadwood());
				cScore.updateWins();
			}

			//Player Win
			else {
				cout << "PLAYER WINS ROUND " << round << endl;
				pScore.updateScore(cScore.getDeadwood() - pScore.getDeadwood());
				pScore.updateWins();
			}

		}

		cout << "Player Deadwood: " << pScore.getDeadwood() << " Computer Deadwood: " << cScore.getDeadwood() 				<< endl;

		cout << "Total Scores " << ": Player - " <<pScore.getScore() << ", Computer - " << cScore.getScore() << endl;
		
		cout << "Press ENTER to continue!" << endl;
		cin.clear();
		cin.ignore();
		getchar();
		cout << "Starting Round " << round+1 << endl;
		sleep(3);
		
		system("clear");

		reset(deck, draw, discard, playerHand, compHand);
		dealToHands(10, playerHand, draw);
		dealToHands(10, compHand, draw);
		dealToDiscard(1, discard, draw);
		end = false;
		turn = 1;
		round++;
	}

	cout << "Game Over!" << endl;

	cout << draw.size() << " " << playerHand.size() << " " << compHand.size() <<  " " << discard.size() << endl;
	
	cout << endl;

return 0;
}
