/*
 * ReversiConsoleView.h
 *
 *  Created on: 04-Nov-2024
 *      Author: abhim
 *
 *  @brief - Class implementation to print the board contents.
 *  It receives a pointer to the board, and prints the current state.
 */

#ifndef REVERSICONSOLEVIEW_H_
#define REVERSICONSOLEVIEW_H_
#include "ReversiBoard.h"


/**
 * @brief Used to print Reversi Board.
 *
 * This class consists of members used to print the board.
 */
class ReversiConsoleView
{
private:
	ReversiBoard *ptBoard;/**Pointer to the ReversiBoard.*/
public:
	/**
	 * @brief - Constructor to the class ReversiConsoleView.
	 *
	 */
	ReversiConsoleView();

	/**
	 * @brief - Destructor the the class ReversiConsoleView.
	 */
	virtual ~ReversiConsoleView();

	/**
	 * brief - Prints the entire board
	 * @param board - Accepts a pointer of type ReversiBoard.
	 */
	void printBoard(ReversiBoard *board);
};

#endif /* REVERSICONSOLEVIEW_H_ */
