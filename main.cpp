#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

int randomInt();

class Card {
public:
    vector<char> type = {'H', 'D', 'C', 'S'};
    vector<string> rank = {"A", "K", "Q", "J", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    vector<string> cards;

    void deck() {
        for (int i = 0; i < type.size(); i++) {
            for (int j = 0; j < rank.size(); j++) {
                cards.push_back(string(1, type[i]) + "-" + rank[j]);
            }
        }
    }

    void showDeck() {
        for (int i = 0; i < cards.size(); i++) {
            cout << cards[i] + " ";
        }
        cout << endl;
    }
};

class Player 
{
	public:
	Card card;

	bool bust;
	vector<string> hands;
	Player(){
		card.deck();
	}
	void dealHands()
	{
		for(int i = 0; i< 2; i++)
		{
			hands.push_back(card.cards[randomInt()]);
		}
	}
	void hit(){
		hands.push_back(card.cards[randomInt()]);
	}
	void showHands()
	{
		for(const auto& hand : hands) {
			cout << hand << " ";
		}
		cout<< endl;
	}

};

class Dealer {
public:
    Card card;

    bool bust;
    vector<string> hands;


    Dealer() {
        card.deck();
    }
    void dealHands()
    {
	    for(int i = 0; i< 2; i++){
		    hands.push_back(card.cards[randomInt()]);
	    }
    }
    void hit() {
        hands.push_back(card.cards[randomInt()]);
    }

    void showHands() {
        for (const auto& hand : hands) {
            cout << hand << " ";
        }
        cout << endl;
    }
};

int randomInt() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 51); 

    return distr(gen);
}

int totalRank(vector<string> hand) {
    int val = 0;
    int valAce = 0;

    for (const string& card : hand) {
        string rank = card.substr(2); 

        if (rank == "A") {
            val += 1;
	    valAce += 11;
        } else if (rank == "K" || rank == "Q" || rank == "J") {
            val += 10; 
	    valAce += 10;
        } else {
            val += stoi(rank);
	  valAce += stoi(rank);  
        }
    }

    if(val > 21 && valAce > 21){
	    return -1;
    }

    return (val > valAce)? val: valAce;
}

void gameLoop()
{
	int rank;

	Dealer dealer;
	Player player;
	dealer.dealHands();
		dealer.showHands();
	player.dealHands();
	player.showHands();


	while(rank <= 21)
	{
		player.hit();
			player.showHands();
			rank = totalRank(player.hands);
			cout<<rank<<endl;

	}



};


int main() {
    gameLoop();
    return 0;
}
