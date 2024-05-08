#include <string>
#include <iostream>
#include <vector>
#include "randgen.h"
#include <random>
using namespace std;


class Revolver {
public:
	RandGen Rand;
	void setCylinder(int bcount);
	vector<int> cylinder;
private:
	int bulletcount;
};




class Player {
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