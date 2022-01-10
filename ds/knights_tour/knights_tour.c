#include <stdlib.h>		
#include <stdio.h>		
#include <time.h>	
#include <assert.h>		
#include "bit_array.h"

#define GET_INDEX(row, col) ((row) * 8 + (col))

enum {ROW = 0, COL = 1};

static int IsInBoard(int row, int col);

int main(void)
{

}

/* initialize the lookup table for possible moves from every index on the board */
static void InitMoves(int moves[64][8+1])
{
	const int knight_moves[8][2] = 
		{{-2, -1}, {-2, 1}, {2, -1}, {2, 1},
		{-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

	int row = 0;
	int col = 0;
	int index = 0;
	int moves_index = 0;
	int moves_counter = 0;

	for (index = 0; index < 64; index++)
	{
		row = index / 8;
		col = index % 8;
		for (moves_index = 0, moves_counter = 0; moves_index < 8; moves_index++)
		{
			if (IsInBoard(row + knight_moves[moves_index][ROW],
			col + knight_moves[moves_index][COL]))
			{	/* stores the legal moves in the table */
				moves[index][moves_counter] =
					GET_INDEX(row + knight_moves[moves_index][ROW], col + knight_moves[moves_index][COL]);
				
                moves_counter++;
			}
		}
        moves[index][moves_counter] = -1;
	}
}

/* returns TRUE if the index is in the board's limits */
static int IsInBoard(int row, int col)
{
	return (row < 8 && row >= 0 && col < 8 && col >= 0);
}



