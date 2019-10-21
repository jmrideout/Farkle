/**
@file:		Dice.cpp
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

// Documentation is provided in the header file: Dice.h

#include "pch.h"
#include "Dice.h"
#include <stdlib.h>
#include <ctime>

Dice::Dice() : value(0)
{
	srand((unsigned int) time(NULL)); // set random seed
}

Dice::~Dice()
{
}

// Rolls die and stores the value
void Dice::roll()
{
	Dice::value = ((rand() % 6) + 1);
}


int Dice::getValue() const
{
	return Dice::value;
}
