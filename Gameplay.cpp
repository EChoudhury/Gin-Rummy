#include "Gameplay.h"
#include "Dealing.h"
#include "Card.h"
#include "ScoreKeeper.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

string names[] = {"Ace", "Two", "Three", "Four", "Five",
 "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

string suits[] = {"Spades", "Hearts", "Clubs", "Diamonds"};

string abrevNames[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char abrevSuits[] = {'S','H','C','D'};

void displayDeck(stack<Card> d) {
	int dnum = d.top().getNumber();
	int dsuit = d.top().getSuit();

	cout << "  ?---?\t\t\t\t\t\t\t\t   " << abrevNames[dnum-1] << "---" << abrevSuits[dsuit-1]<< "\t" << endl;
	cout << "  |   |\t\t\t\t\t\t\t\t   |" << "   " << "|" << "\t" << endl;
	cout << "  |   |\t\t\t\t\t\t\t\t   |" << "   " << "|" << "\t" << endl;
	cout << "  |   |\t\t\t\t\t\t\t\t   |" << "   " << "|" << "\t" << endl;
	cout << "  ?---?\t\t\t\t\t\t\t\t   " << abrevSuits[dsuit-1] << "---" << abrevNames[dnum-1] << "\t" << endl;
	cout << "Draw Pile\t\t\t\t\t\t\tDiscard Pile" << endl;
}

void displayBoard(vector<Card>& h) {	

	cout << endl;

	for (int x = 0; x < h.size(); x++) {
		Card c = h[x];		
		int num = c.getNumber();
		int suit = c.getSuit();
		cout << abrevNames[num-1] << "---" << abrevSuits[suit-1]<< "\t";
	}

	cout << endl;

	for (int i = 0; i < h.size(); i++) {
		cout << "|" << "   " << "|" << "\t";
	}

	cout << endl;

	for (int i = 0; i < h.size(); i++) {
		cout << "|" << " " << i + 1 << " " << "|" << "\t";
	}

	cout << endl;
	
	for (int i = 0; i < h.size(); i++) {
		cout << "|" << "   " << "|" << "\t";
	}
	
	cout << endl;

	for (int x = 0; x < h.size(); x++) {
		Card c = h[x];	
		int num = c.getNumber();
		int suit = c.getSuit();	
		cout << abrevSuits[suit-1] << "---" << abrevNames[num-1] << "\t";
	}
	
	cout << endl;

	for (int x = 0; x < h.size(); x++) {	
		Card c = h[x];
		int num = c.getNumber();
		int suit = c.getSuit();
		cout << names[num-1] << "\t";
	}

	cout << endl;

	for (int x = 0; x < h.size(); x++) {	
		Card c = h[x];
		int suit = c.getSuit();
		cout << "of " << abrevSuits[suit-1] << "\t";
	}
	
	cout << endl;
}

int input(bool v, string s, int max, int min) {
	
	int choice;

	while (!v) {
		
		v = true;
	
		cout << endl << s;
		cin >> choice;
		
		if (cin.fail() || choice > max || choice < min) {
			cin.clear();
			cin.ignore();
			cout << "Sorry, that response was not understood. Please try again." << endl;
			v = false;	
		}

		cout << "You chose " << choice << endl;
		
	}

	return choice;
}

void playerTurn(vector<Card>& player, stack<Card>& draw, stack<Card>& discard, bool& end, ScoreKeeper& pScore) {
	bool valid = false;
	int choice;
	string selectDrawSort = "Select from the draw pile (1) or discard pile (2)! Press (3) to sort! (1-3)\n>";
	string selectDraw = "Select from the draw pile (1) or discard pile (2)!\n";
	string selectKnock = "Select from the draw pile (1) or discard pile (2)! Press (0) to knock!\n";
	string selectDiscard = "Select card to discard! (1-11)\n>";
	
	displayDeck(discard);
	displayBoard(player);
	
	choice = input(valid, selectDrawSort, 3, 1);

		while (choice == 3) {
			system("clear");
			sort(player.begin(), player.end());
			displayDeck(discard);
			displayBoard(player);
			choice = input(valid, selectDraw, 2, 1);
		}

		if (choice == 1) {
			system("clear");
			dealToHands(1, player, draw);
			cout << "You took a card from draw! " << choice << endl;
			displayBoard(player);
			pScore.getPlayerHand(player);
			pScore.scoreHand(player);
			cout <<"Your deadwood value is " << pScore.getDeadwood() << " and you have " << 					pScore.getMelds() << " melds." << endl;

			choice = pScore.checkWin();
			
			if (choice == 6) {
				choice = input(valid, selectKnock, 2, 0);
				if (choice == 0) {
					end = true;
					goto loc;
				}
			}

			if (choice == 5 || choice == 7) {
				end = true;
				goto loc;
			}

			choice = input(valid, selectDiscard, 11, 1);
	
			choice -= 1;
			Card c = player[choice];
			discard.push(c);
			player.erase(player.begin() + choice);

			displayBoard(player);
		}
		
		else {
			system("clear");
			dealToHands(1, player, discard);
			cout << "You took a card from discard! " << choice << endl;
			displayBoard(player);
			pScore.getPlayerHand(player);
			pScore.scoreHand(player);
			cout <<"Your deadwood value is " << pScore.getDeadwood() << " and you have " << 					pScore.getMelds() << " melds." << endl;

			choice = pScore.checkWin();

			if (choice == 6) {
				choice = input(valid, selectKnock, 2, 0);
				if (choice == 0) {
					end = true;
					goto loc;
				}
			}

			if (choice == 5 || choice == 7) {
				end = true;				
				goto loc;
			}

			choice = input(valid, selectDiscard, 11, 1);

			choice -= 1;
			Card c = player[choice];
			discard.push(c);
			player.erase(player.begin() + choice);
			displayDeck(discard);
			displayBoard(player);
		}

	loc:
	cout << endl;
}


void compTurn(vector<Card>& comp, stack<Card>& draw, stack<Card>& discard, bool& end, ScoreKeeper& cScore) {

	int choice;
	
	choice = 1;

	if (draw.size() == 0) {
		choice = 2;
	}

	cout << "Computer's Turn!" << endl;

		if (choice == 1) {
			dealToHands(1, comp, draw);
			cScore.getPlayerHand(comp);
			cScore.scoreHand(comp);

			choice = cScore.checkWin();
			
			if (choice == 6) {
				end = true;
				goto fin;
			}

			if (choice == 5 || choice == 7) {
				end = true;
				goto fin;
			}

			choice = 1;
	
			choice -= 1;
			Card c = comp[choice];
			discard.push(c);
			comp.erase(comp.begin() + choice);
		}
		
		else {
			dealToHands(1, comp, discard);
			cScore.getPlayerHand(comp);
			cScore.scoreHand(comp);

			choice = cScore.checkWin();

			if (choice == 6) {
				end = true;
				goto fin;
			}

			if (choice == 5 || choice == 7) {
				end = true;				
				goto fin;
			}

			choice = 1;

			choice -= 1;
			Card c = comp[choice];
			discard.push(c);
			comp.erase(comp.begin() + choice);
		}
	fin:	
	cout << "My turn! Thinking..." << endl;	
}

void roundStart(vector<Card>& comp, vector<Card>& player, stack<Card>& discard) {
		
		bool valid = false;
		string discPass = "Would you like to draw from discard (1) or pass (2)? (1/2)\n>";
		string selectDiscard = "Select card to discard! (1-11)\n>";
		displayDeck(discard);
		displayBoard(player);
		int choice = input(valid, discPass, 2, 1);
			
			if (choice == 1) {
				dealToHands(1, player, discard);
				displayBoard(player);
				choice = input(valid, selectDiscard, 11, 1);
	
				choice -= 1;
				Card c = player[choice];
				discard.push(c);
				player.erase(player.begin() + choice);

				displayDeck(discard);
				displayBoard(player);
				cout << "Computer's turn!" << endl;
			}
			
			else {
				cout << "You passed. My turn!" << endl;
				
			}
			
		dealToHands(1, comp, discard);
		choice = 1;

		choice -= 1;
		Card c = comp[choice];
		discard.push(c);
		comp.erase(comp.begin() + choice);
}

void roundScoring(ScoreKeeper& wScore, ScoreKeeper& lScore, int win) {
	
	//gin
	if (win == 5) {
		cout << "GIN! +25!" << endl;
		wScore.updateScore(( lScore.getDeadwood() - wScore.getDeadwood()) + 25);
	}

	//knock
	else if (win == 6) {

		if (wScore.getDeadwood() < lScore.getDeadwood()) {
			cout << "Knocked! +25!" << endl;
			wScore.updateScore((lScore.getDeadwood() - wScore.getDeadwood()) + 25);
		}

		else if (wScore.getDeadwood() >= lScore.getDeadwood()) {
			cout << "Knock Failed!" << endl;
			lScore.updateScore(wScore.getDeadwood() - lScore.getDeadwood());
		}
	}

	//big gin
	else if (win == 7) {
		cout << "BIG GIN! +31!" << endl;
		wScore.updateScore(( lScore.getDeadwood() - wScore.getDeadwood()) + 31);
	}
}

