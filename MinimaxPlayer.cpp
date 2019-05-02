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

int MinimaxPlayer::utility(OthelloBoard *b)
{
	char p1_symb = b->get_p1_symbol();
	char p2_symb = b->get_p2_symbol();
	int p1_score = b->count_score(p1_symb);
	int p2_score = b->count_score(p2_symb);
	return p1_score - p2_score;		// returns the utility of the leaf node
									// based on difference in scores
}
