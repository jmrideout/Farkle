/**
@file:		Player.h
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

/*
Documentation:
The Player class stores the player's name, the score, if they have entered the game and if they have played the final round.
The Player class is used to hold player data for the Farkle program and is used in the Game class.
Player is a separate class to meet the project requirements of dividing logical sections into a minimum of 3 classes.
*/

#pragma once
#include <string>
using namespace std;

class Player
{
private:
	string playerName;
	int playerScore;
	bool hasEnteredGame;
	bool hasPlayedFinalRound;

public:
	Player();
	Player(string name);
	~Player();

	int getPlayerScore() const;
	void setPlayerScore(int score);

	/**
	Adds score to the player's score.
	*/
	void addToPlayerScore(int score);

	void setPlayerName(string name);
	string getPlayerName() const;

	bool getHasEnteredGame() const;
	void setHasEnteredGame(bool enteredStatus);

	bool getHasPlayedFinalRound() const;
	void setHasPlayedFinalRound(bool finalRoundStatus);
};
