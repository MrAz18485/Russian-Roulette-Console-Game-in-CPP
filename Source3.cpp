#include <string>
#include <iostream>
#include <vector>
#include "randgen.h"
#include <random>
using namespace std;

// A simple Console Game, Russian Roulette

class Revolver {
	public:
		RandGen Rand;
		void setCylinder(int bcount);
		vector<int> cylinder;
	private:
		int bulletcount;
};




class Player{
	public:
		void setInitialValues(string name);
		int displayScore();
		void changeScore(int val);
	private:
		string name;
		int score = 0;
};




class Game {
	public:
		RandGen Rand;
		void playRound(string& choice, Revolver& Weapon, Player& plr, Player& bot);
		bool checkStatus(int roundNo, Player plr, Player bot);
	private:
		int roundNo;
};



// Setter functions
void Player::setInitialValues(string name) {
	Player::name = name;
	Player::score = 0;
}


void Player::changeScore(int val) {
	Player::score += val;
}


int Player::displayScore() {
	return Player::score;
}



void Revolver::setCylinder(int bcount) {
	vector<int> cylinder;
	for (int i = 0; i < bcount; i++) { // insert bullets (bcount bullets)
		cylinder.push_back(1);
	}
	for (int i = 0; i < 6 - bcount; i++) { // insert empty chambers (no bullets, empty)
		cylinder.push_back(0);
	}
	random_shuffle(cylinder.begin(), cylinder.end());
	Revolver::cylinder = cylinder;
}



bool Game::checkStatus(int bcount, Player plr, Player bot) {
	if (bcount == plr.displayScore() + bot.displayScore()) {
		return false;
	}
	return true;
}


void Game::playRound(string& turn, Revolver& Weapon, Player& plr, Player& bot) {
	random_shuffle(Weapon.cylinder.begin(), Weapon.cylinder.end());
	if (Weapon.cylinder[0] == 1) { // One dies, round ends
		Weapon.cylinder[0] = 0; // Empty the chamber
		if (turn == "Y") {
			cout << "You died!" << endl;
			bot.changeScore(1);
		}
		else {
			cout << "Bot died!" << endl;
			plr.changeScore(1);
		}
	}
	else {
		cout << "Empty!" << endl; // No bullets were in chamber, round ends
	}


	// Changing the turn, otherwise game logic becomes faulty
	if (turn == "Y") {
		turn = "N";
	}
	else {
		turn = "Y";
	}
}




int main() {
	Player Player1;
	Player Bot;
	Revolver Revolver1;
	Game Game1;


	string name;
	int bcount = -1;

	cout << "Welcome to console russian roulette game\n";
	cout << "Enter your name:" << endl;
	cin >> name;
	Player1.setInitialValues(name);
	Bot.setInitialValues("BOT");
	

	cout << "Enter number of bullets (6 max): ";
	while (0 >= bcount || bcount > 6) {
		cin >> bcount;
	}
	Revolver1.setCylinder(bcount);

	// Starting the round.
	string choice;
	cout << "Who should start at first? You(Y) or Bot(B): ";
	while (choice != "Y" && choice != "B") {
		cin >> choice;
	}

	// Looping the game.
	string decision;
	while (decision != "N" && Game1.checkStatus(bcount, Player1, Bot)) {
		Game1.playRound(choice, Revolver1, Player1, Bot);
		cout << "Player score: " << Player1.displayScore() << " Bot score: " << Bot.displayScore() << endl;
		if (Game1.checkStatus(bcount, Player1, Bot)) {
			cout << "Continue? (Y/N): " << endl;
			cin >> decision;
		}
	}

	cout << "----FINAL RESULTS----" << endl;
	cout << "Player score: " << Player1.displayScore() << " Bot score: " << Bot.displayScore() << endl;
}