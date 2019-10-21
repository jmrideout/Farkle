/**
@file:		Game.cpp
@author:	Jason Rideout
@version:	1.1 04Oct19
SNHU GAM-495
Date:		14 January 2019 v1.0
Modified:	06 October 2019 v1.1
*/

// Documentation is provided in the header file: Game.h

#include "pch.h"
#include "Game.h"
#include <iostream>
#include <Windows.h> // For Sleep()
#include <fstream>
using namespace std;

Game::Game() : currentPlayer(0), players(nullptr), numberOfPlayers(2), scoreToBeat(WINNING_SCORE_LIMIT),
				finalRound(false), winner(""), turnTotalPoints(0), numberOfDice(6)
{
	for (int i = 0; i < numberOfDice; i++)
	{
		rolledDice[i] = 0;
	}
}

Game::~Game()
{
}

// Prompts the user if they would like to read the instructions.
// Reads and prints the game rules from an external file.
// Prints an error message if the file is not found.
void Game::readFile(string filepath)
{
	ifstream ifile;
	string fileData = "";
	string playerInput = "";

	cout << "Would you like to read the rules (y/n)? ";
	cin >> playerInput;

	// repeat until given valid input
	while ((playerInput.compare("y") != 0) && (playerInput.compare("n") != 0))
	{
		cout << "y or n: " << endl;
		cin >> playerInput;
	}

	if (playerInput.compare("y") == 0) // they want to see the rules
	{
		system("cls");
		// Try to read the file
		try
		{
			ifile.open(filepath, ios::in);

			if (!ifile)
			{
				throw (exception("File not read"));
			}

			while (ifile)
			{
				fileData += ifile.get();
			}
			ifile.close();

			// Print out the file data;
			cout << fileData << endl;
		}
		catch (...)
		{
			cout << "Error reading Farkle.txt. Skipping rulebook." << endl;
			Sleep(1000);
		}
	}
}

// Welcomes the players, displays the rules and gets the number of players and their names.
void Game::setupGame()
{
	string playerInput;

	cout << "WELCOME TO FARKLE!" << endl << endl;

	// Prompt user if they would like to read the rules from FarkleRules.txt
	Game::readFile("FarkleRules.txt");

	// Get player input and handle exceptions
	while (true)
	{
		cout << "How many players: ";
		cin >> playerInput;

		try
		{
			numberOfPlayers = stoi(playerInput);
			if ((numberOfPlayers <= 1) || (numberOfPlayers > 10))
				throw (exception("Invalid number"));
		}
		catch (...)
		{
			cout << "Invalid number" << endl;
			continue;
		}
		break;
	}

	// Repeat number back to user
	cout << "Understood. You have " << numberOfPlayers << " players." << endl << endl;

	// setup Game variables
	players = new Player[numberOfPlayers];

	// Get player names
	for (int i = 0; i < numberOfPlayers; i++)
	{
		string name;
		cout << "Player " << (i + 1) << " enter your name: ";
		cin >> name;
		players[i].setPlayerName(name);
	}

	// Echo input
	cout << "Welcome ";
	for (int i = 0; i < numberOfPlayers-1; i++)
	{
		cout << players[i].getPlayerName() << ", ";
	}
	cout << "and " << players[numberOfPlayers-1].getPlayerName() << "!" << endl;
	Sleep(1500);
}

// Clears the screen and displays the current player's information.
void Game::displayTurnStatus()
{
	system("cls");
	cout << "Player: " << players[currentPlayer].getPlayerName() << endl;
	cout << "Total Points: " << players[currentPlayer].getPlayerScore() << endl;
	cout << "Points this turn: " << turnTotalPoints << endl;
	cout << "Points to win: " << scoreToBeat << endl;
	if (finalRound)
		cout << "FINAL ROUND!" << endl;

	if (players[currentPlayer].getHasEnteredGame() == true)
		cout << "Player has entered the game." << endl;
	else
		cout << "Player has not yet entered the game." << endl;

	cout << endl;
}

// Passes the turn to the next player.
// Resets appropriate data.
void Game::nextPlayer()
{
	currentPlayer++;

	// Cycle back to first player if needed
	if (currentPlayer >= numberOfPlayers)
	{
		currentPlayer = 0;
	}

	// Reset dice
	numberOfDice = 6;

	// Clear the screen and display the new player
	system("cls");
	cout << "Switching to " << players[currentPlayer].getPlayerName() << "'s turn." << endl;
	Sleep(1500);
}

// Rolls remaining dice and stores the occurrences of dice values.
void Game::rollDice()
{
	resetDice(); // clears previous dice data
	cout << "Rolling " << numberOfDice << " dice!" << endl;
	Sleep(1000);

	for (int i = 0; i < numberOfDice; i++)
	{
		die.roll();
		rolledDice[die.getValue()]++;
	}
}

// Prints out the occurrances of dice values
void Game::showDice()
{
	cout << "Dice Values:" << endl;
	for (int i = 1; i <= 6; i++) // check all face values
	{
		cout << "[" << i << " * " << rolledDice[i] << "]" << endl;
	}
	cout << endl;
}

// Resets occurrences of dice values to zero.
void Game::resetDice()
{
	for (int i = 0; i < 7; i++)
		rolledDice[i] = 0;
}

// Checks for Farkle (no point-dice) in remaining dice.
bool Game::farkle()
{
	if (rolledDice[1] > 0) // face value of 1 exists
		return false;
	else if (rolledDice[5] > 0) // face value of 5 exists
		return false;

	for (int i = 1; i <= 6; i++) // check all face values for triples
	{
		if (rolledDice[i] >= 3)
			return false;
	}

	return true;
}

// Performs the player's turn.
void Game::playerTurn()
{
	// Reset turn data
	numberOfDice = 6;
	turnTotalPoints = 0;
	bool hasTurnEnded = false;

	// Clear the screen and display the turn status of the player
	displayTurnStatus();

	// Roll all 6 dice
	rollDice();

	// While the player's turn has not ended
	while (!hasTurnEnded)
	{
		if (numberOfDice == 0) // all dice are set aside for points
		{
			// Update screen
			displayTurnStatus();

			// Roll all 6 dice
			numberOfDice = 6;
			rollDice();
		}
		if (farkle()) // always check for farkle
		{
			showDice();
			cout << "Farkle!" << endl;
			Sleep(1500);
			hasTurnEnded = true;
		}
		else // Not farkle, still dice left
		{
			string playerInput;
			
			// Set aside and score dice
			setAsideDice();
			
			hasTurnEnded = playerCanEndTurn();
		}
	}
}

// Checks to see if conditions are met to end the game.
// Marks that the player has played their final round.
bool Game::endGameCheck()
{
	if (finalRound)
	{
		if (players[currentPlayer].getHasPlayedFinalRound())
		{
			// End game
			return true;
		}
		else
		{
			// Mark that the player has played their final round
			players[currentPlayer].setHasPlayedFinalRound(true);
		}
	}

	return false;
}

// Checks to see if the player can end their turn.
// If they can, it prompts the user if they would like to end their turn.
// Allows the player to roll remaining dice instead.
bool Game::playerCanEndTurn()
{
	bool endTurn = false;
	// Check to see if player has entered the game officially or unofficially
	if (((turnTotalPoints >= 1000) || (players[currentPlayer].getHasEnteredGame())) && (numberOfDice != 0))
	{
		showDice();
		// ask if player wants to roll dice
		std::cout << "Roll remaining dice (y/n): ";
		string playerInput;
		cin >> playerInput;

		// Validate input
		while ((playerInput.compare("y") != 0) && (playerInput.compare("n") != 0))
		{
			std::cout << "y or n" << endl;
			cin >> playerInput;
		}

		if (playerInput.compare("y") == 0) // Yes, roll them.
		{
			// Clear the screen and display the turn status
			displayTurnStatus();

			rollDice();
		}
		else // No, end turn.
		{
			players[currentPlayer].addToPlayerScore(turnTotalPoints); // Add the turn's total score to player's score
			endTurn = true; // end turn
			if (players[currentPlayer].getHasEnteredGame() == false) // Enter the game if needed
			{
				players[currentPlayer].setHasEnteredGame(true);
				std::cout << players[currentPlayer].getPlayerName() << " has entered the game!" << endl;
				Sleep(1000);
			}
		}
	}
	else // Not enough points to stop yet
	{
		if (numberOfDice != 0)
		{
			// Display the turn status
			displayTurnStatus();

			// Roll remaining dice
			rollDice();
		}
		// else... If there are no dice, playerTurn automatically rerolls. There is no need to do that here.
	}

	return endTurn;
}

// Initiates the game.
void Game::runGame()
{
	// Perform game setup
	setupGame();

	// Main game loop
	while (!endGameCheck())
	{
		// Take the player's turn
		playerTurn();

		// Check for initiation of final round
		// scoreToBeat was initially set to WINNING_SCORE_LIMIT
		if (players[currentPlayer].getPlayerScore() >= scoreToBeat)
		{
			// Initiate final round
			finalRound = true;

			// the player's score is the new score to beat
			scoreToBeat = players[currentPlayer].getPlayerScore();

			// The potential winner's name is recorded
			winner = players[currentPlayer].getPlayerName();
			players[currentPlayer].setHasPlayedFinalRound(true);
		}

		// Pass turn to next player
		nextPlayer();
	}

	// Announce and congratulate winner
	cout << "CONGRATULATIONS!" << endl;
	cout << winner << " HAS WON with " << scoreToBeat << " Points!" << endl;

	Sleep(3000);
}

// Displays all dice the player can set aside.
// Returns the number of point dice the player can set aside.
int Game::analyzeDice()
{
	int pointDice = 0;
	cout << "Possible dice values to set aside ( ";
	// Look at dice
	if (rolledDice[1] > 0) // 1 is worth points alone
	{
		cout << "1 ";
		pointDice += rolledDice[1];
	}
	if (rolledDice[2] >= 3)
	{
		cout << "2 ";
		pointDice += 3;
	}
	if (rolledDice[3] >= 3)
	{
		cout << "3 ";
		pointDice += 3;
	}
	if (rolledDice[4] >= 3)
	{
		cout << "4 ";
		pointDice += 3;
	}
	if (rolledDice[5] > 0) // 5 is worth points alone
	{
		cout << "5 ";
		pointDice += rolledDice[5];
	}
	if (rolledDice[6] >= 3)
	{
		cout << "6 ";
		pointDice += 3;
	}
	cout << ")" << endl;

	return pointDice;
}

// Allows the player to set aside dice. Scores dice and sets the turn's points.
// Gets player input regarding which dice to set aside.
// Checks the input against possible dice to set aside.
// Loops until input is correct and the player does not want to keep more dice.
// Ensures at least 1 die is set aside per roll.
void Game::setAsideDice()
{
	string playerInput;
	bool stillGoing = true;
	bool hasSetAsideDie = false; // False until player sets aside at least 1 die

	while (stillGoing)
	{
		// Display point dice and note how many are left
		displayTurnStatus();
		showDice();
		int pointDiceLeft = analyzeDice();

		// Get player input
		cout << "Enter the face value of the die you would like to keep";
		if (hasSetAsideDie)
			cout << " (0 to stop)";
		cout << ": ";
		cin >> playerInput;

		// evaluate input
		try
		{
			int selectedDie = stoi(playerInput); // convert input to integer

			switch (selectedDie)
			{
			case 0: // does not want to keep any more
				if (hasSetAsideDie)
					stillGoing = false;
				else
					throw (exception("You must set aside a die before stopping!"));
				break;
			case 1:
				if (rolledDice[1] >= 3) // remove triple
				{
					cout << "Keeping triple 1's for 1000 points" << endl;
					rolledDice[1] -= 3;
					numberOfDice -= 3;
					pointDiceLeft -= 3;
					turnTotalPoints += 1000; // 1000 points for triple 1's
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else if (rolledDice[1] >= 1) // remove single
				{
					cout << "Keeping single 1 for 100 points" << endl;
					rolledDice[1]--;
					numberOfDice--;
					pointDiceLeft--;
					turnTotalPoints += 100; // 100 points for a single 1
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else
				{
					throw (exception("1 is not valid"));
				}
				break;

			case 2:
				if (rolledDice[2] >= 3) // remove triple
				{
					cout << "Keeping triple 2's for 200 points" << endl;
					rolledDice[2] -= 3;
					numberOfDice -= 3;
					pointDiceLeft -= 3;
					turnTotalPoints += 200; // 200 points for triple 2's
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else
				{
					throw (exception("2 is not valid"));
				}
				break;

			case 3:
				if (rolledDice[3] >= 3) // remove triple
				{
					cout << "Keeping triple 3's for 300 points" << endl;
					rolledDice[3] -= 3;
					numberOfDice -= 3;
					pointDiceLeft -= 3;
					turnTotalPoints += 300; // 300 points for triple 3's
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else
				{
					throw (exception("3 is not valid"));
				}
				break;

			case 4:
				if (rolledDice[4] >= 3) // remove triple
				{
					cout << "Keeping triple 4's for 400 points" << endl;
					rolledDice[4] -= 3;
					numberOfDice -= 3;
					pointDiceLeft -= 3;
					turnTotalPoints += 400; // 400 points for triple 4's
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else
				{
					throw (exception("4 is not valid"));
				}
				break;

			case 5:
				if (rolledDice[5] >= 3) // remove triple
				{
					cout << "Keeping triple 5's for 500 points" << endl;
					rolledDice[5] -= 3;
					numberOfDice -= 3;
					pointDiceLeft -= 3;
					turnTotalPoints += 500; // 500 points for triple 5's
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else if (rolledDice[5] >= 1) // remove single
				{
					cout << "Keeping single 5 for 50 points" << endl;
					rolledDice[5]--;
					numberOfDice--;
					pointDiceLeft--;
					turnTotalPoints += 50; // 50 points for single 5
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else
				{
					throw (exception("5 is not valid"));
				}
				break;

			case 6:
				if (rolledDice[6] >= 3) // remove triple
				{
					cout << "Keeping triple 6's for 600 points" << endl;
					rolledDice[6] -= 3;
					numberOfDice -= 3;
					pointDiceLeft -= 3;
					turnTotalPoints += 600; // 600 points for triple 6's
					hasSetAsideDie = true;
					Sleep(1500);
				}
				else
				{
					throw (exception("6 is not valid"));
				}
				break;

			default:
				throw (exception("Invalid number"));
				Sleep(1500);
			}
		}
		catch (const invalid_argument &) // stoi exceptions
		{
			cout << "Invalid input." << endl;
			Sleep(1000);
		}
		catch (exception const & e)
		{
			cout << e.what() << endl;
			Sleep(1500);
		}

		if (pointDiceLeft == 0) // all dice possible set aside
		{
			stillGoing = false; // done with this roll
		}
		if (turnTotalPoints >= 1000 && !players[currentPlayer].getHasEnteredGame())
		{
			cout << players[currentPlayer].getPlayerName() << " has reached 1,000 points and may end their turn to enter the game." << endl << endl;
			Sleep(2000);
		}
	}
	
}
