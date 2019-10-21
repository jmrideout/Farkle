/**
@file:		Player.cpp
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

// Documentation is provided in the header file: Player.h

#include "pch.h"
#include "Player.h"

Player::Player() : playerScore(0), hasEnteredGame(false), hasPlayedFinalRound(false)
{
}

Player::Player(string name)
{
	Player::Player();
	Player::setPlayerName(name);
}

Player::~Player()
{
}

int Player::getPlayerScore() const
{
	return Player::playerScore;
}

void Player::setPlayerScore(int score)
{
	Player::playerScore = score;
}

// Adds score to player's score
void Player::addToPlayerScore(int score)
{
	Player::playerScore += score;
}

void Player::setPlayerName(string name)
{
	Player::playerName = name;
}

string Player::getPlayerName() const
{
	return Player::playerName;
}

bool Player::getHasEnteredGame() const
{
	return hasEnteredGame;
}

void Player::setHasEnteredGame(bool enteredStatus)
{
	Player::hasEnteredGame = enteredStatus;
}

bool Player::getHasPlayedFinalRound() const
{
	return hasPlayedFinalRound;
}

void Player::setHasPlayedFinalRound(bool finalRoundStatus)
{
	hasPlayedFinalRound = finalRoundStatus;
}