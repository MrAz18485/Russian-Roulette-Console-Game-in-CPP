#include <string>
#include <iostream>
#include <vector>
#include "randgen.h"
#include "GameClasses.h"
#include <random>
using namespace std;


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
