/**
@file:		Game.h
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

/*
Documentation:
The Game class performs the game logic for Farkle and is used in Farkle.cpp.
runGame is the starting point for the game.
Game uses the Player and Dice classes.
Game reads the Farkle instructions from a separate file to meet project requirements.
*/

#pragma once
#include "Player.h"
#include "Dice.h"

class Game
{
private:
	const int WINNING_SCORE_LIMIT = 10000;
	int currentPlayer;
	Player* players;
	Dice die;
	int rolledDice[7]; // Stores the dice rolls by index. Example: Roll of 3 will increment rolledDice[3].
	int numberOfPlayers;
	int scoreToBeat; // Used in the final round to determine the winner.
	int numberOfDice;
	bool finalRound;
	string winner;
	int turnTotalPoints; // The turn's points. Discarded if there is a Farkle.

private:
	/**
	Prompts the user if they would like to read the instructions.
	Reads and prints the game rules from an external file.
	Prints an error message if the file is not found.

	@param filepath the file path to the instructions text file.
	*/
	void readFile(string filepath);

	/**
	Welcomes the players, displays the rules and gets the number of players and their names.
	*/
	void setupGame();

	/**
	Displays the current player's information.
	*/
	void displayTurnStatus();

	/**
	Passes the turn to the next player.
	Resets appropriate data.
	*/
	void nextPlayer();

	/**
	Performs the player's turn.
	Calls displayTurnStatus, rollDice, showDice, setAsideDice, and playerCanEndTurn.
	*/
	void playerTurn();

	/**
	Rolls remaining dice and stores the occurrences of dice values.
	*/
	void rollDice();

	/**
	Displays the occurrences of dice values.
	*/
	void showDice();

	/**
	Resets occurrences of dice values to zero.
	*/
	void resetDice();

	/**
	Checks for Farkle (no point-dice) in remaining dice.

	@return True if there is a Farkle. False if not.
	*/
	bool farkle();

	/**
	Displays all dice the player can set aside.

	@return The number of point dice available.
	*/
	int analyzeDice();

	/**
	Allows the player to set aside dice. Scores dice and sets the turn's points.
	Gets player input regarding which dice to set aside.
	Checks the input against possible dice to set aside.
	Loops until input is correct and the player does not want to keep more dice.
	Ensures at least 1 die is set aside per roll.
	Calls displayTurnStatus, showDice, and analyzeDice.
	*/
	void setAsideDice();

	/**
	Checks to see if conditions are met to end the game.
	If it is the final round and the player has not yet played, their hasPlayedFinalRound status is changed to true.
	If a player is reached that has already played their final round, the game is over.

	@return Whether or not the game should end.
	*/
	bool endGameCheck();

	/**
	Checks to see if the player can end their turn.
	If they can, it prompts the user if they would like to end their turn.
	Allows the player to roll remaining dice instead.
	Calls displayTurnStatus and rollDice.

	@return True if the player chooses to end their turn.
	*/
	bool playerCanEndTurn();

public:
	Game();
	~Game();

	/**
	Initiates the game.
	Calls setupGame, endGameCheck, and nextPlayer.
	*/
	void runGame();

};
