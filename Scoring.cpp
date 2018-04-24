#include "Scoring.h"
#include "Gameplay.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int scoreHand(vector<Card> h) {

	if (deadwoodPairsRuns(h) > deadwoodRunsPairs(h)) { return deadwoodRunsPairs(h); }
	else if (deadwoodPairsRuns(h) < deadwoodRunsPairs(h)) { return deadwoodPairsRuns(h); }
	else { return deadwoodPairsRuns(h); }
}

int deadwoodPairsRuns(vector<Card> h) {
	
	int deadwood = 0;
	int melds = 0;
	vector<int> vals;

	sort(h.begin(), h.end());	

	//pairs
	for( int i = 0; i < h.size(); i++) {
		
		int num = 0;

		for(int j = 0; j < h.size(); j++) {
			if (h[i].getNumber() == h[j].getNumber()) {
				vals.push_back(j);
			}
		}

		if (vals.size() > 2) {
			melds++;
			for(int x = 0; x < vals.size(); x++) {				
				h.erase(h.begin() + (vals[x - num]));
				num++;
			}
	
		}

		vals.clear();	
	}

	//runs
	int num;	

	for( int i = 0; i < h.size(); i++) {
		
		num = 1;

		vals.push_back(i);	
	
		for(int j = 0; j < h.size(); j++) {
			if ((h[i].getNumber() + num) == h[j].getNumber()) {
				if(h[i].getSuit() == h[j].getSuit()) {				
					vals.push_back(j);
					num++;
				}
			}

		}	

		if (vals.size() > 2) {
			melds++;
			
			for(int e = 0; e < vals.size(); e++) {
				cout << vals[e] << endl;	
				Card c = h[vals[e]];			
				h.erase(h.begin() + (vals[e]));
				h.insert(h.begin(), c);
			}
		
			h.erase(h.begin(), h.begin() + vals.size());

		}

		vals.clear();	
	}


	for(int y = 0; y < h.size(); y++) {
		
		deadwood = deadwood + h[y].getNumber();
		
	}


	return deadwood;

}

int deadwoodRunsPairs(vector<Card> h) {
	
		int deadwood = 0;
	int melds = 0;
	vector<int> vals;

	sort(h.begin(), h.end());	

	//runs
	int num;	

	for( int i = 0; i < h.size(); i++) {
		
		num = 1;

		vals.push_back(i);	
	
		for(int j = 0; j < h.size(); j++) {
			if ((h[i].getNumber() + num) == h[j].getNumber()) {
				if(h[i].getSuit() == h[j].getSuit()) {				
					vals.push_back(j);
					num++;
				}
			}

		}	

		if (vals.size() > 2) {
			melds++;
			
			for(int e = 0; e < vals.size(); e++) {
				cout << vals[e] << endl;	
				Card c = h[vals[e]];			
				h.erase(h.begin() + (vals[e]));
				h.insert(h.begin(), c);
			}
		
			h.erase(h.begin(), h.begin() + vals.size());

		}

		vals.clear();	
	}

	//pairs
	for( int i = 0; i < h.size(); i++) {
		
		int num = 0;

		for(int j = 0; j < h.size(); j++) {
			if (h[i].getNumber() == h[j].getNumber()) {
				vals.push_back(j);
			}
		}

		if (vals.size() > 2) {
			melds++;
			for(int x = 0; x < vals.size(); x++) {				
				h.erase(h.begin() + (vals[x - num]));
				num++;
			}
	
		}

		vals.clear();	
	}

	for(int y = 0; y < h.size(); y++) {
		
		deadwood = deadwood + h[y].getNumber();
		
	}

	return deadwood;

}


