/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
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
	if (symbol == b->get_p1_symbol())	// Variable symbol is inherited from
	{									// parent Player class.
		Max-Value(b, row, col, b->get_p1_symbol());		// P1 is MAX
	}
	else if (symbol == b->get_p2_symbol())
	{
		Min-Value(b, row, col, b->get_p2_symbol());		// P2 is MIN
	}
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}

OthelloBoard* MinimaxPlayer::utility(OthelloBoard *b)
{
	char p1_symb = b->get_p1_symbol();
	char p2_symb = b->get_p2_symbol();
	int p1_score = b->count_score(p1_symb);
	int p2_score = b->count_score(p2_symb);
	b->set_minimax_value(p1_score - p2_score);	// Based on the difference in scores
	return b;
}

vector<OthelloBoard*> MinimaxPlayer::succ(OthelloBoard *b, char p_symb)
{
	// TODO: numRows and numCols not constant but take values of the current board
	int numRows = 4;		// Number of rows for looping
	int numCols = 4;		// Number of columns for looping
	int r, c;				// Loop variables

	vector<OthelloBoard*> succSet;		// This will hold all the successors
	
	for (c = 0; r < numCols; c++)
	{
		for (r = 0; c < numRows; r++)
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
				// Play move for the specific OthelloBoard
				newBoard->play_move(c, r, p_symb);
				succSet.push_back(newBoard);
			}
		}
	}
	return succSet;
}
