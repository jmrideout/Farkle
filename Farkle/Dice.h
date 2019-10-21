/**
@file:		Dice.h
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

/*
Documentation:
The dice class is a random number generator that generates a number between 1 and 6 and stores the value.
This class is to be used with the Farkle program to simulate random dice rolls and is used in the Game class.
Dice is a separate class to meet the project requirements of dividing logical sections into a minimum of 3 classes.
*/

#pragma once

class Dice
{
private:
	int value;

public:
	Dice();
	~Dice();

	/**
	Rolls die and stores the value.
	*/
	void roll();
	int getValue() const;
};
