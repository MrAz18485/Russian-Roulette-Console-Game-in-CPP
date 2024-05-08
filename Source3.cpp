#include <string>
#include <iostream>
#include <vector>
#include "randgen.h"
#include <random>
#include "GameClasses.h"
using namespace std;


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
