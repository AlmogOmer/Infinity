#include <stdlib.h>		
#include <stdio.h>		
#include <time.h>	
#include <assert.h>		
#include "bit_array.h"

#define NUM_OF_ROWS 8
#define NUM_OF_COLS 8
#define BOARD_SIZE ((NUM_OF_COLS) * (NUM_OF_ROWS))
#define GET_ROW(x) ((x) / NUM_OF_COLS)
#define GET_COL(x) ((x) % NUM_OF_COLS)
#define GET_INDEX(row, col) ((row) * NUM_OF_COLS + (col))

enum {ROW = 0, COL = 1};

static int IsInBoard(int row, int col);
static void PrintLUT(int moves[BOARD_SIZE][8+1]);
static void PrintBoard(int *board);
static void InitMoves(int moves[BOARD_SIZE][8+1]);
static int Solve(int *board, int index, bitarray_t taken, int counter, int moves[BOARD_SIZE][8+1]);
static int GetNextMove(int board_index, bitarray_t wrong_moves, int moves[BOARD_SIZE][8+1]);
static int CountMoves(int board_index, bitarray_t wrong_moves, int moves[BOARD_SIZE][8+1]);

int main(void)
{
	int moves[BOARD_SIZE][8+1] = {0};
	static int board[BOARD_SIZE] = {0};

	InitMoves(moves);
	
    PrintLUT(moves);
	
	if (Solve(board, rand() % BOARD_SIZE, BitArrayResetAll(), 0, moves))
	{
		PrintBoard(board);
	}
	else
	{
		puts("no solution");
	}

	return 1;
}

/* initialize the lookup table for possible moves from every index on the board */
static void InitMoves(int moves[BOARD_SIZE][8+1])
{
	const int knight_moves[8][2] = 
		{{-2, -1}, {-2, 1}, {2, -1}, {2, 1},
		{-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

	int row = 0;
	int col = 0;
	int index = 0;
	int moves_index = 0;
	int moves_counter = 0;

	for (index = 0; index < BOARD_SIZE; index++)
	{
		row = GET_ROW(index);
		col = GET_COL(index);
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

/* returns 1 if the index is in the board's limits */
static int IsInBoard(int row, int col)
{
	return (row < NUM_OF_ROWS && row >= 0 && col < NUM_OF_COLS && col >= 0);
}

static void PrintLUT(int moves[BOARD_SIZE][8+1])
{
	size_t i = 0;
	size_t j = 0;

	for (i = 0, j = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j <= 8; j++)
		{
			printf("%d\t", moves[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

static void PrintBoard(int *board)
{
	size_t i = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (0 == (i % NUM_OF_COLS))
		{
			putchar('\n');
			putchar('\n');
		}
		printf("%d\t", board[i]);
	}
	putchar('\n');
}



static int Solve(int *board, int index, bitarray_t taken, int counter, int moves[BOARD_SIZE][8+1])
{
	bitarray_t wrong_moves = 0;	/* bit array that represents the already visited indexes and moves failed */
	int next_index = 0;
	board[index] = counter;
	if (counter == (BOARD_SIZE - 1))
	{	/* we finish successfuly */
		return 1;
	}

	taken = BitArraySetOn(taken, index);
	wrong_moves = taken;

	while (-1 != (next_index = GetNextMove(index, wrong_moves, moves)))
	{
		if (Solve(board, next_index, taken, counter + 1, moves))
		{
			return 1;
		}

		wrong_moves = BitArraySetOn(wrong_moves, next_index);
	}

	return 0;
}

static int GetNextMove(int board_index, bitarray_t wrong_moves, int moves[BOARD_SIZE][8+1])
{
	
	int next_index = 0;
	int moves_index = 0;
	int current_moves = 0;
	int min_index = -1;
	int min_moves = 8 + 1;

	while (-1 != (next_index = moves[board_index][moves_index]))
	{
		if (0 == BitArrayGetValue(wrong_moves, next_index))
		{
			current_moves = CountMoves(next_index, wrong_moves, moves);
			if (current_moves < min_moves)
			{
				min_index = next_index;
				min_moves = current_moves;
			}
		}
		moves_index++;
	}

	return min_index;
	
	
	/*************for backtracking without heuristics*************/
	
	/*int next_index = -1;
	int moves_index = 0;

	while (-1 != (next_index = moves[board_index][moves_index]))
	{
		if (0 == BitArrayGetValue(wrong_moves, next_index))
		{
			next_index = moves[board_index][moves_index];
			break;
		}
		++moves_index;
	}

	return next_index;*/
}

/* returns number of possible moves from a given index to not yet visited indexes */
static int CountMoves(int board_index, bitarray_t wrong_moves, int moves[BOARD_SIZE][8+1])
{
	int next_index = 0;
	int moves_index = 0;
	int counter = 0;
	
	while (-1 != (next_index = moves[board_index][moves_index]))
	{
		if (0 == BitArrayGetValue(wrong_moves, next_index))
		{
			++counter;
		}
		++moves_index;
	}

	return counter;
}

