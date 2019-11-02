#include <stdbool.h>
#include "minimax.h"

/*finds the next optimal move
for the A.I.*/
typedef struct {
	int row, col;
}Move;

int aiSymbol, playerSymbol;

bool isMovesLeft(int aiGrid[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (aiGrid[i][j] == 0)
				return true;
	return false;
}

// This is the evaluation function as discussed 
// in the previous article ( http://goo.gl/sJgv68 ) 
int evaluate(int aiGrid[3][3])
{
	// Checking for Rows for X or O victory. 
	for (int i = 0; i < 3; i++)
	{
		if (aiGrid[i][0] == aiGrid[i][1] &&
			aiGrid[i][1] == aiGrid[i][2])
		{
			if (aiGrid[i][0] == aiSymbol)
				return +10;
			else if (aiGrid[i][0] == playerSymbol)
				return -10;
		}
	}

	// Checking for Columns for X or O victory. 
	for (int col = 0; col < 3; col++)
	{
		if (aiGrid[0][col] == aiGrid[1][col] &&
			aiGrid[1][col] == aiGrid[2][col])
		{
			if (aiGrid[0][col] == aiSymbol)
				return +10;

			else if (aiGrid[0][col] -aiSymbol)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory. 
	if (aiGrid[0][0] == aiGrid[1][1] && aiGrid[1][1] == aiGrid[2][2])
	{
		if (aiGrid[0][0] == aiSymbol)
			return +10;
		else if (aiGrid[0][0] -aiSymbol)
			return -10;
	}

	if (aiGrid[0][2] == aiGrid[1][1] && aiGrid[1][1] == aiGrid[2][0])
	{
		if (aiGrid[0][2] == aiSymbol)
			return +10;
		else if (aiGrid[0][2] -aiSymbol)
			return -10;
	}

	// Else if none of them have won then return 0 
	return 0;
}

int minimax(int aiGrid[3][3], int depth, bool isMax)
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
	if (isMovesLeft(aiGrid) == false)
		return 0;

	// If this maximizer's move 
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells 
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (aiGrid[i][j] == 0)
				{
					// Make the move 
					aiGrid[i][j] = aiSymbol;

					// Call minimax recursively and choose 
					// the maximum value 
					best = max(best,
						minimax(aiGrid, depth + 1, !isMax));

					// Undo the move 
					aiGrid[i][j] = 0;
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
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (aiGrid[i][j] == 0)
				{
					// Make the move 
					aiGrid[i][j] = -aiSymbol;

					// Call minimax recursively and choose 
					// the minimum value 
					best = min(best,
						minimax(aiGrid, depth + 1, !isMax));

					// Undo the move 
					aiGrid[i][j] = 0;
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the player 
Move findBestMove(int aiGrid[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for 
	// all empty cells. And return the cell with optimal 
	// value. 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Check if cell is empty 
			if (aiGrid[i][j] == 0)
			{
				// Make the move 
				aiGrid[i][j] = aiSymbol;

				// compute evaluation function for this 
				// move. 
				int moveVal = minimax(aiGrid, 0, false);

				// Undo the move 
				aiGrid[i][j] = 0;

				// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}

//runs the minimax algorithm
int* minimaxMain(int aiGrid, int aISymbol)
{
	static int aiPlayCoordinates[2];
	
	aiSymbol = aISymbol;
	playerSymbol = -aISymbol;

	Move bestMove = findBestMove(aiGrid);
	aiPlayCoordinates[0] = bestMove.row;
	aiPlayCoordinates[1] = bestMove.col;

	return aiPlayCoordinates;
}