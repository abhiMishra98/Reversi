/*
 * ReversiConsoleView.cpp
 *
 *  Created on: 04-Nov-2024
 *      Author: abhim
 */

#include "ReversiConsoleView.h"
#include <iostream>

using namespace std;

ReversiConsoleView::ReversiConsoleView()
{

}

ReversiConsoleView::~ReversiConsoleView()
{
	// TODO Auto-generated destructor stub
}

void ReversiConsoleView::printBoard(ReversiBoard *ptBoard)
{
	unsigned short counter = 0;
	for (unsigned short j = 0; j < 64; j++)
	{
		counter++;
		cout << ptBoard->getBoard()[j] << " ";
		if (counter % 8 == 0)
		{
			cout << endl;
		}
	}
}
