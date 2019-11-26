#include "minimax.h"
#include <stdbool.h>

int player;
extern Win winVerifyer(int grid[6][7]);
extern void getTheRow(int grid[6][7], Move* move);

int max(int a, int b)
{
	if (a > b)
		return a;
	if (a < b)
		return b;
	return a;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	if (a > b)
		return b;
	return a;
}

int makeAMove(int aiGrid[6][7], Move move)
{
	if (move.row < 0)
		return 2;
	return aiGrid[move.row][move.col];
}

void layerDefiner(int aiGrid[6][7], Move layer[7], Move move)
{
	if (move.row == -1 && move.col == -1)
	{
		for (int count = 0; count < 7; count++)
		{
			layer[count].col = count;
			getTheRow(aiGrid, &layer[count]);
		}
	}
}

int bestValReturner(int bestVal, int mod)
{
	static int bestValue;
	if (mod == 0)
		bestValue = bestVal;
	if (mod == 1)
		return bestValue;
	return -1;
}

void tiedGridReturner(int aiGrid[6][7], int mod)
{
	static int tiedGrid[6][7];
	if (mod == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
				tiedGrid[i][j] = aiGrid[i][j];
		}
	}
	if (mod == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
				aiGrid[i][j] = tiedGrid[i][j];
		}
	}
}

bool isMovesLeft(int aiGrid[6][7])
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			if (aiGrid[i][j] == 0)
				return true;
	return false;
}

int evaluate(int aiGrid[6][7])
{
	Win winVerifyerReturn;
	winVerifyerReturn = winVerifyer(aiGrid);

	if (winVerifyerReturn.win == true) {
		if (winVerifyerReturn.player == 1)
			return -10;
		else if (winVerifyerReturn.player == 2)
			return +10;
	}
		
	// Else if none of them have won then return 0 
	return 0;
}

int minimax(int aiGrid[6][7], int depth, bool isMax, Move layer[7])
{
	int score = evaluate(aiGrid);

	// If Maximizer has won the game return his/her 
	// evaluated score 
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her 
	// evaluated score 
	if (score == -10)
		return score;

	// If there are no more moves and no winner then 
	// it is a tie 
	if (isMovesLeft(aiGrid) == false) {
		tiedGridReturner(aiGrid, 0);
		return 0;
	}
	
	// If this maximizer's move 
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int count = 0; count < 7; count++)
		{
			// Check if cell is empty
			if (makeAMove(aiGrid, layer[count]) != 2)
			{
				if (aiGrid[layer[count].row][layer[count].col] == 0)
				{
					// Make the move
					aiGrid[layer[count].row][layer[count].col] = player;
					layer[count].row--;

					// Call minimax recursively and choose 
						// the maximum value 
					best = max(best,
						minimax(aiGrid, depth + 1, !isMax, layer));

					// Undo the move 
					aiGrid[layer[count].row][layer[count].col] = 0;
					layer[count].row++;
				}
			}
		}

		return best;
	}

	// If this minimizer's move 
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int count = 0; count < 7; count++)
		{
			// Check if cell is empty
			if (makeAMove(aiGrid, layer[count]) != 2)
			{
				if (aiGrid[layer[count].row][layer[count].col] == 0)
				{
					// Make the move
					aiGrid[layer[count].row][layer[count].col] = -player;
					layer[count].row--;

					// Call minimax recursively and choose 
						// the maximum value 
					best = min(best,
						minimax(aiGrid, depth + 1, !isMax, layer));

					// Undo the move 
					aiGrid[layer[count].row][layer[count].col] = 0;
					layer[count].row++;
				}
			}
		}
		return best;
	}
}

Move findBestMove(int aiGrid[6][7])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	Move layer[7];
	layerDefiner(aiGrid, layer, bestMove);

	// Traverse all cells, evaluate minimax function for 
	// all empty cells. And return the cell with optimal 
	// value. 
	for (int count = 0; count < 7; count++) {
		// Check if the cell is empty
		if (makeAMove(aiGrid, layer[count]) == 0)
		{
			// Make the move
			aiGrid[layer[count].row][layer[count].col] = player;
			layer[count].row--;

			// compute evaluation function for this 
			// move.
			int moveVal = minimax(aiGrid, 0, false, layer);

			// Undo the move
			aiGrid[layer[count].row][layer[count].col] = 0;
			layer[count].row++;

			// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
			if (moveVal > bestVal)
			{
				bestMove.row = layer[count].row;
				bestMove.col = layer[count].col;
				bestVal = moveVal;
			}
		}
	}
	bestValReturner(bestVal, 0);
	return bestMove;
}

void supergridTied(char supergrid[37][98])
{
	Move  circleCoordinates;
	int i, j;
	char circle[5][12] = { { ' ', ' ', ' ', '.', '-', '\"', '\"', '-', '.', ' ', ' ', ' ' },
						{ ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', '\\', ' ', ' ' },
						{ ' ', ';', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', ' ' },
						{ ' ', ' ', '\\', ' ', ' ', ' ', ' ', ' ', ' ', '/', ' ' , ' '},
						{ ' ', ' ', ' ', '\'', '-', '.', '.', '-', '\'', ' ', ' ', ' ' } };
	for (i = 1, circleCoordinates.row = 0; i < 36; i++, circleCoordinates.row++)
	{
		if (i == 5)
		{
			i = 7;
			circleCoordinates.row = 0;
		}

		if (i == 11)
		{
			i = 13;
			circleCoordinates.row = 0;
		}

		if (i == 17)
		{
			i = 19;
			circleCoordinates.row = 0;
		}

		if (i == 23)
		{
			i = 25;
			circleCoordinates.row = 0;
		}

		if (i == 29)
		{
			i = 31;
			circleCoordinates.row = 0;
		}

		for (j = 1, circleCoordinates.col = 0; j < 97; j++, circleCoordinates.col++)
		{
			if (j == 12)
			{
				j = 15;
				circleCoordinates.col = 0;
			}

			if (j == 26)
			{
				j = 29;
				circleCoordinates.col = 0;
			}

			if (j == 40)
			{
				j = 43;
				circleCoordinates.col = 0;
			}

			if (j == 54)
			{
				j = 57;
				circleCoordinates.col = 0;
			}

			if (j == 68)
			{
				j = 71;
				circleCoordinates.col = 0;
			}

			if (j == 82)
			{
				j = 85;
				circleCoordinates.col = 0;
			}

			supergrid[i][j] = circle[circleCoordinates.row][circleCoordinates.col];
		}
	}
}

bool minimaxTie(int grid[6][7], int nextplayer)
{
	if (nextplayer == 1 || nextplayer == 3)
		player = 1;
	if (nextplayer == 2)
		player = -1;
	int aiGrid[6][7];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
			aiGrid[i][j] = grid[i][j];
	}
	findBestMove(aiGrid);
	if (bestValReturner(1, 1) == 0) {
		tiedGridReturner(aiGrid, 1);
		return true;
	}
	else
		return false;
}

Move minimaxPlay(int grid[6][7], int nextplayer)
{
	Move bestMove;
	if (nextplayer == 1 || nextplayer == 3)
		player = 1;
	if (nextplayer == 2)
		player = -1;
	bestMove = findBestMove(grid);
	return bestMove;
}