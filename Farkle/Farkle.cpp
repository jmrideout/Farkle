/**
@file:		Farkle.cpp
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

/*
Documentation:
This is the starting point for the program.
Farkle.cpp requires the Game class.

PURPOSE:
This program is a text-based version of the game Farkle.
Farkle is played with two or more players.
There are three phases in Farkle: entering the game, earning points, and ending the game.
The first two phases are dependent on the player.
It is possible that one or more players will not be able to enter the game for many turns.
However, when one player reaches the end phase, all players are allowed a final turn.

Points:
Rolling a 1 gives 100 points.
Rolling a 5 gives 50 points.
Rolling three of a kind gives 100 x the face value.
Rolling three 1's gives 1000 points (instead of 100).
Points are recorded for the turn until the turn ends.
If the turn ends successfully, the turn's points are added to the player's total.
If the turn ends with a Farkle, the turn's points are lost.

Farkle:
If there are no dice that are worth points, it is a Farkle.
The player immediately ends their turn and loses the turn's points.
The player's total points are unaffected.

Phase 1 - Entering the Game:
The player rolls all six dice and may set aside dice that are worth points.
The player must set aside at least 1 die per roll.
If all six dice rolled are worth points, they are recorded and rerolled immediately.
If there are no dice that are worth points, it is a Farkle.
If all dice are set aside for points, the score is noted and all six dice are rerolled.
The player must continue rolling dice until they reach 1000 points.
Once a player reaches 1000 points, they have the option to end their turn.
If they choose to end their turn, they have officially entered the game.
The turn's points are added to the player's total.

Phase 2 - Earning Points
The player rolls all six dice and may set aside dice that are worth points.
The player must set aside at least 1 die per roll.
If all six dice rolled are worth points, they are recorded and rerolled immediately.
If there are no dice that are worth points, it is a Farkle.
After dice are set aside for points, the player may end their turn.
If they choose to end their turn, the turn's points are added to the player's total score.

Phase 3 - Ending the Game
If the player's total points after ending their turn meets or exceeds 10,000 points, the final round begins.
The other players get one turn to attempt to beat the highest score.
The highest scoring player wins.
*/

#include "pch.h"
#include "Game.h"
#include <iostream>
using namespace std;

int main()
{
	Game Farkle;
	Farkle.runGame();

	return 0;
}