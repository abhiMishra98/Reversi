// Standard (system) header files
#include <iostream>
#include <cstdlib>

// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"
#include "ReversiBoard.h"
#include "ReversiConsoleView.h"

// Main program

/**
 * @brief Main entry point for the Reversi game.
 *
 * This function initializes the game board and handles user input
 * for placing pieces on the board. It alternates between two players
 * until a valid move cannot be made.
 *
 * @return 0 on successful execution.
 */

int main()
{
	// TODO: Add your program code here
	ReversiBoard gameBoard;
	ReversiConsoleView printGameBoard;
	cout << "Allocated board of dimension x = 8, y = 8 at address "
			<< static_cast<void*>(gameBoard.getBoard()) << endl;
	printGameBoard.printBoard(&gameBoard);

	unsigned short posX = 0;
	unsigned short posY = 0;
	unsigned short turn = 0;
	char currentPlayer;
	char posXAscii;
	char posYAscii;
	int indexState = 0;
	bool player1CanMove = gameBoard.canMove('B');
	bool player2CanMove = gameBoard.canMove('W');
	std::vector<int> playerCount;

	do
	{
		currentPlayer = (turn % 2 == 0) ? 'B' : 'W'; //Alternating between two players.
		cout << "Player " << currentPlayer
				<< ": Please enter a position (x, y): ";
		cin >> posX >> posY;
		posXAscii = posX + '0';
		posYAscii = posY + '0';

		//Validating if the user inputs are between numbers 0 and 7.
		if (posXAscii <= 47 || posXAscii >= 56 || posYAscii <= 47
				|| posYAscii >= 56)
		{
			cout << "Invalid position. Please enter values between 0 and 7."
					<< endl;
			continue; //Skip to the next iteration.
		}

		//Check if the position is occupied.
		char occupied = gameBoard.getIndexState(posX, posY);

		if (occupied != '*')
		{
			cout << endl << "Index occupied by player " << occupied
					<< ". Please enter a new position" << endl;
			continue; //Skip to the next iteration.
		}
		else
		{
			//Set coin for the current player in the set index.
			indexState = gameBoard.setIndexState(posX, posY, turn);
			if (indexState == -1)
			{
				continue;
			}
		}

		if (!player1CanMove && !player2CanMove)
		{
			cout << "No valid moves for both players. Game over." << endl;
			break;
		}

		turn++; //Increment the turn.
		cout << endl;
		printGameBoard.printBoard(&gameBoard);

		playerCount = gameBoard.getCount();
		cout << "Player1 = " << playerCount[0] << endl << "Player2 = "
				<< playerCount[1] << endl;
	} while ((player1CanMove || player2CanMove));
	turn = 0;

	return 0;
}
