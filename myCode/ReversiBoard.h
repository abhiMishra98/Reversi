/*
 * ReversiBoard.h
 *
 *  Created on: 04-Nov-2024
 *      Author: abhim
 *
 *  @brief - Class implementation to manage the board contents.
 */


#ifndef REVERSIBOARD_H_
#define REVERSIBOARD_H_

#include<vector>
/**
 * @brief Represents a game board for Reversi.
 *
 * This class manages the board's state, applies game rules, and counts coins.
 */
class ReversiBoard
{
private:
	char *m_pBoard;/**<Pointer to a memory location that holds char values.*/
	enum fieldState
	{
		freeField = '*', player1Occupied = 'B', player2Occupied = 'W'
	};
	static const int immediateCellDirections[8][2]; /**<Static array to store the offset in 8 directions. */
public:
	/**
	 * @brief Constructor to create the board and set the initial state.
	 *
	 */
	ReversiBoard();

	/**
	 * Checks if the position on the board is occupied or free.
	 * @param rowIndex - Row where the coin is to be kept.
	 * @param columnIndex - Column where the coin is to be kept.
	 */
	fieldState getIndexState(unsigned short rowIndex,
			unsigned short columnIndex);

	/**
	 *Sets the coin in a given position on the board.
	 * @param rowIndex - Row where the coin is to be kept.
	 * @param columnIndex - Column where the coin is to be kept.
	 */
	int setIndexState(unsigned short rowIndex, unsigned short columnIndex,
			unsigned short turn);

	/**
	 *Counts the number of player1 and player2 coins.
	 */
	std::vector<int> getCount();

	/**
	 * Returns the instance of the board for printing the board.
	 *
	 * @brief This is used for Class ReversiConsoleView to get the instance of
	 * the board for printing.
	 * @return
	 */

	char* getBoard();

	/**
	 *Sandwiches the coins (black or white), given, it is possible to do.
	 * @param rowIndex - row index entered by the user.
	 * @param columnIndex - column index entered by the user.
	 * @param turn - used to determine which player has made the move.
	 */
	int sandwichCoins(unsigned short rowIndex, unsigned short columnIndex,
			unsigned short turn, int cellState);

	/**
	 * used to check the opponent coin in any of the immediate cells, given, the
	 * row and column index as user input.
	 *
	 * @brief - The entered values in the direction array are the row and column
	 * offsets.
	 *
	 * @param rowIndex - row index entered by the user.
	 * @param columnIndex - column index entered by the user.
	 */
	std::vector<int> checkOppCoinInImmediateCell(unsigned short rowIndex,
			unsigned short columnIndex, unsigned short turn);

	/**
	 * Checks if any valid moves can be made.
	 * @param Player - Takes as an input which player to check for valid moves.
	 * @return
	 */
	bool canMove(char Player);
	/**
	 * Destructor to delete the instances of the board and free the memory allocated.
	 */
	virtual ~ReversiBoard();
};

#endif /* REVERSIBOARD_H_ */
