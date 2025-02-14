/*
 * ReversiBoard.cpp
 *
 *  Created on: 02-Nov-2024
 *      Author: abhim
 */

#include "ReversiBoard.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Define the directions array globally for the class
/**
 * @brief - Moving up is decreasing the row index. Moving down is increasing the
 * index. Moving right is increasing the column index and moving left is
 * decreasing the column index.
 */
const int ReversiBoard::immediateCellDirections[8][2] =
{
{ -1, 0 },  // Up
		{ 1, 0 },   // Down
		{ 0, -1 },  // Left
		{ 0, 1 },   // Right
		{ -1, -1 }, // Up-left (diagonal)
		{ -1, 1 },  // Up-right (diagonal)
		{ 1, -1 },  // Down-left (diagonal)
		{ 1, 1 }    // Down-right (diagonal)
};

ReversiBoard::ReversiBoard()
{
	// TODO Auto-generated constructor stub
	m_pBoard = new char[64];
	for (unsigned short index = 0; index < 64; index++)
	{
		m_pBoard[index] = '*';
	}
	m_pBoard[27] = 'B';
	m_pBoard[28] = 'W';
	m_pBoard[35] = 'W';
	m_pBoard[36] = 'B';
}

ReversiBoard::fieldState ReversiBoard::getIndexState(unsigned short rowIndex,
		unsigned short columnIndex)
{
	unsigned short index = (rowIndex * 8) + columnIndex;
	if (m_pBoard[index] == '*')
	{
		return ReversiBoard::freeField;
	}
	else if (m_pBoard[index] == 'B')
	{
		return ReversiBoard::player1Occupied;
	}
	else if (m_pBoard[index] == 'W')
	{
		return ReversiBoard::player2Occupied;
	}

	return ReversiBoard::freeField;
}

int ReversiBoard::sandwichCoins(unsigned short rowIndex,
		unsigned short columnIndex, unsigned short turn, int cellState)
{
	unsigned short newRow = rowIndex + immediateCellDirections[cellState][0];
	unsigned short newCol = columnIndex + immediateCellDirections[cellState][1];
	char currentPlayer = (turn % 2 == 0) ? 'B' : 'W';

	bool isValidSandwich = false;

	// Traverse in the given direction
	while (newRow < 8 && newCol < 8 && newRow >= 0 && newCol >= 0)
	{
		if (m_pBoard[newRow * 8 + newCol] == '*')
		{
			break;  // Empty cell, stop the search
		}
		if (m_pBoard[newRow * 8 + newCol] == currentPlayer)
		{
			isValidSandwich = true;
			break;  // Valid sandwich endpoint
		}

		// Move further in the direction
		newRow += immediateCellDirections[cellState][0];
		newCol += immediateCellDirections[cellState][1];
	}

	if (!isValidSandwich)
	{
		return -1;  // No valid sandwich in this direction
	}

	// Reset position to initial move and flip coins
	newRow = rowIndex + immediateCellDirections[cellState][0];
	newCol = columnIndex + immediateCellDirections[cellState][1];

	while (m_pBoard[newRow * 8 + newCol] != currentPlayer)
	{
		m_pBoard[newRow * 8 + newCol] = currentPlayer;
//		int count = getCount(currentPlayer);
		newRow += immediateCellDirections[cellState][0];
		newCol += immediateCellDirections[cellState][1];
	}

	return 0;
}

int ReversiBoard::setIndexState(unsigned short rowIndex,
		unsigned short columnIndex, unsigned short turn)
{
	std::vector<int> validDirections = checkOppCoinInImmediateCell(rowIndex,
			columnIndex, turn);
	char currentPlayer = (turn % 2 == 0) ? 'B' : 'W';
	unsigned short index = (rowIndex * 8) + columnIndex;

	if (!validDirections.empty())
	{
		m_pBoard[index] = currentPlayer;

		// Flip coins in all valid sandwich directions
		for (int direction : validDirections)
		{
			sandwichCoins(rowIndex, columnIndex, turn, direction);
		}
	}
	else
	{
		cout << "Invalid move: No valid sandwich found." << endl;
		return -1;
	}

	return 0;
}

std::vector<int> ReversiBoard::checkOppCoinInImmediateCell(
		unsigned short rowIndex, unsigned short columnIndex,
		unsigned short turn)
{
	char currentPlayer = (turn % 2 == 0) ? 'B' : 'W';
	char opponentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
	std::vector<int> validDirections;

	for (int i = 0; i < 8; i++)
	{
		unsigned short newRow = rowIndex + immediateCellDirections[i][0];
		unsigned short newCol = columnIndex + immediateCellDirections[i][1];

		bool opponentFound = false;

		// Traverse in the current direction until out of bounds or an empty cell
		while (newRow < 8 && newCol < 8 && newRow >= 0 && newCol >= 0)
		{
			char cellState = m_pBoard[newRow * 8 + newCol];

			if (cellState == '*')
			{
				// Empty cell, stop searching in this direction
				break;
			}
			else if (cellState == currentPlayer)
			{
				// Found current player piece after opponent pieces, valid sandwich
				if (opponentFound)
				{
					validDirections.push_back(i);
				}
				break;
			}
			else if (cellState == opponentPlayer)
			{
				// Found opponent piece, keep moving in this direction
				opponentFound = true;
				newRow += immediateCellDirections[i][0];
				newCol += immediateCellDirections[i][1];
			}
		}
	}
	return validDirections;
}

char* ReversiBoard::getBoard()
{
	return m_pBoard;
}

std::vector<int> ReversiBoard::getCount()
{
	unsigned short p1Coins = 0;
	unsigned short p2Coins = 0;
	std::vector<int> countPlayers;
	for (unsigned short counter = 0; counter < 64; counter++)
	{
		if (m_pBoard[counter] == 'B')
		{
			p1Coins++;
		}
		else if (m_pBoard[counter] == 'W')
		{
			p2Coins++;
		}
	}
	countPlayers.push_back(p1Coins);
	countPlayers.push_back(p2Coins);
	return countPlayers;
}

bool ReversiBoard::canMove(char player)
{
	for (unsigned short row = 0; row < 8; row++)
	{
		for (unsigned short col = 0; col < 8; col++)
		{
			if (m_pBoard[row * 8 + col] == '*') // Check only empty cells
			{
				unsigned short turn = (player == 'B') ? 0 : 1;
				if (!checkOppCoinInImmediateCell(row, col, turn).empty())
				{
					return true; // Found a valid move
				}
			}
		}
	}
	return false; // No valid moves found
}

ReversiBoard::~ReversiBoard()
{
// TODO Auto-generated destructor stub

	delete m_pBoard;
}
