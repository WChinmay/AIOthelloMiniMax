/*
 * MinimaxPlayer.cpp
 *
 *  Created on: May 1st, 2019
 *      Author: Chinmay Wadgaonkar
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) 
{
    // Using this function as the MINIMAX-DECISION function from the algorithm
	// Hence this funciton is used to trigger MIN or MAX based on alternating at
	// each level. Functionality would have to be modified for more than 2 player 
	// game.
	// std::cout << "In get_move" << std::endl;	
	symbol == b->get_p1_symbol() ? maxValue(b, row, col, b->get_p1_symbol()) : minValue(b, row, col, b->get_p2_symbol());
  	// if (symbol == b->get_p1_symbol())	// Variable symbol is inherited from
	// {									// parent Player class.
	// 	// std::cout << "Chose max in get move" << std::endl;
	//    	maxValue(b, row, col, b->get_p1_symbol());		// P1 is MAX
	// }
	// else if (symbol == b->get_p2_symbol())
	// {
	// 	// std::cout << "Chose min in get_move" << std::endl;
	//    	// std::cout << "Row is: " << row << std::endl;
	// 	// std::cout << "Col is: " << col << std::endl;
	// 	minValue(b, row, col, b->get_p2_symbol());		// P2 is MIN
	// 	// std::cout << "LALALALALALLALALALALLALALALLALALALALLALALA. I should go to player move after this. " << std::endl;
	// 	// std::cout << "Row is: " << row << std::endl;
	// 	// std::cout << "Col is: " << col << std::endl;
	// }
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}

int MinimaxPlayer::utility(OthelloBoard *b)
{
	// std::cout << "Calculating utilit for leaf node" << std::endl;;
   	char p1_symb = b->get_p1_symbol();
	char p2_symb = b->get_p2_symbol();
	int p1_score = b->count_score(p1_symb);
	int p2_score = b->count_score(p2_symb);
	// std::cout << "Utility value is: " << p1_score- p2_score << std::endl;
	// b->set_minimax_value(p1_score - p2_score);	// Based on the difference in scores
	// std::cout << "The utility value I have put in the object is: " << b->get_minimax_value() << std::endl;
	// std::cout << "Done calculating utility" << std::endl;
	return p1_score - p2_score;
}

vector<OthelloBoard*> MinimaxPlayer::succ(OthelloBoard *b, char p_symb)
{
	// TODO: numRows and numCols not constant but take values of the current board
	// std::cout << "Started trying to find successors" << std::endl;
   	int numRows = 4;		// Number of rows for looping
	int numCols = 4;		// Number of columns for looping
	int r, c;				// Loop variables

	vector<OthelloBoard*> succSet;		// This will hold all the successors
	
	for (c = 0; c < numCols; c++)
	{
		for (r = 0; r < numRows; r++)
		{
			// Using pre-built function to check if it is a valid move
			if (b->is_legal_move(c, r, p_symb))
			{
				// Create this tested board and add to succSet as one of the possible
				// successors
				// How do I create such an OthelloBoard? 
				// Create a new board such that the state has been copied using the 
				// copy constructor
				OthelloBoard* newBoard = new OthelloBoard(*(b));
				newBoard->pcol = c;		// Preserve this column
				newBoard->prow = r;		// Preserve this row
				// Play move for the specific OthelloBoard
				newBoard->play_move(c, r, p_symb);
				succSet.push_back(newBoard);
			}
		}
	}
	// std::cout << "Finished finding successors" << std::endl;
	return succSet;
}

int MinimaxPlayer::maxValue(OthelloBoard *b, int &row, int &col, char p_symb)
{
	// Initial Variables
	vector<OthelloBoard*> currentSet;
	// std::cout << "computing max value" << std::endl;
	int v = std::numeric_limits<int>::min();
	// OthelloBoard* bestDecisionBoard = new OthelloBoard(*(b));
	// OthelloBoard* evalBoard = new OthelloBoard(*(b));
	// Looping
	int i, currRow, currCol, currMin;

	// Get successors
	currentSet = succ(b, b->get_p1_symbol());

	// Check if Terminal State 
	if (currentSet.size() == 0)
	{
		// std::cout << "Utility value that max thinks it is: " << b->get_minimax_value() << std::endl;
		return utility(b);
	}

	// Now choose the baord with the highest minimax value after computing minValue.
	for (i = 0; i < currentSet.size(); i++)
	{
		currMin = minValue(currentSet[i], row, col, p_symb);
		// Update if this board is better scenario than previous best state
		if(currMin > v)
		{
			v = currMin;
			currCol = currentSet[i]->pcol;
			currRow = currentSet[i]->prow;
		}
	}
	// std::cout << "Finished computing a max value" << std::endl;
	row = currRow;
	col = currCol;
	return v;	
}

int MinimaxPlayer::minValue(OthelloBoard *b, int &row, int &col, char p_symb)
{
	// Initial Variables
	vector<OthelloBoard*> currentSet;
	// std::cout << "computing min value" << std::endl;
	int v = std::numeric_limits<int>::max();
	// OthelloBoard* bestDecisionBoard = new OthelloBoard(*(b)); 
	// OthelloBoard* evalBoard = new OthelloBoard(*(b));
	// Looping
	int i, currRow, currCol, currMax;

	// Get successors
	currentSet = succ(b, b->get_p2_symbol());

	// Check if Terminal State 
	if (currentSet.size() == 0)
	{
		// std::cout << "Utility value that min thinks it is: " << b->get_minimax_value() << std::endl;
		return utility(b);
	}

	// Now choose the baord with the highest minimax value after computing minValue.
	for (i = 0; i < currentSet.size(); i++)
	{
		currMax = maxValue(currentSet[i], row, col, p_symb);
		// Update if this board is better scenario than previous best state
		if(currMax < v)
		{
			v = currMax;
			currCol = currentSet[i]->pcol;
			currRow = currentSet[i]->prow;
		}
	}
	// std::cout << "Finished computing a min value" << std::endl;
	row = currRow;
	col = currCol;
	return v;	
}