#include "ai.h"
#include "tictactoe.h"
#include "minimax.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int aiSymbol, aiPlayCoordinates[2];
static int aiGrid[3][3];

// looks if the AI or player can will win in the next turn
// retunrs an array with "win" info
//	[0]: position of the possible win
//	[1]: win type
//	[2]: row for hotizontal, and column for the rest
// it's almost a copy of winVerifyer in tictactoe.c
int** winPositionVerifyer(int aiGrid[3][3], int symbol)
{
	static int returnValue[8][3] = { 0 };
	int i, j, count1 = 0;

	// horizontal
	for (i = 0; i < 3; i++)
	{
		if (aiGrid[i][0] == symbol && aiGrid[i][1] == symbol && aiGrid[i][2] == 0)
		{
			returnValue[count1][0] = 2;
			returnValue[count1][1] = 0;
			returnValue[count1][2] = i;
			count1++;
		}

		if (aiGrid[i][0] == symbol && aiGrid[i][1] == 0 && aiGrid[i][2] == symbol)
		{
			returnValue[count1][0] = 1;
			returnValue[count1][1] = 0;
			returnValue[count1][2] = i;
			count1++;
		}

		if (aiGrid[i][0] == 0 && aiGrid[i][1] == symbol && aiGrid[i][2] == symbol)
		{
			returnValue[count1][0] = 0;
			returnValue[count1][1] = 0;
			returnValue[count1][2] = i;
			count1++;
		}
	}

	// vertical
	for (j = 0; j < 3; j++)
	{
		if (aiGrid[0][j] == symbol && aiGrid[1][j] == symbol && aiGrid[2][j] == 0)
		{
			returnValue[count1][0] = 2;
			returnValue[count1][1] = 1;
			returnValue[count1][2] = j;
			count1++;
		}

		if (aiGrid[0][j] == symbol && aiGrid[1][j] == 0 && aiGrid[2][j] == symbol)
		{
			returnValue[count1][0] = 1;
			returnValue[count1][1] = 1;
			returnValue[count1][2] = j;
			count1++;
		}

		if (aiGrid[0][j] == 0 && aiGrid[1][j] == symbol && aiGrid[2][j] == symbol)
		{
			returnValue[count1][0] = 0;
			returnValue[count1][1] = 1;
			returnValue[count1][2] = j;
			count1++;
		}
	}

	// '\' diagonal
	i = 0;
	j = 0;
	if (aiGrid[i][j] == symbol && aiGrid[i + 1][j + 1] == symbol && aiGrid[i + 2][j + 2] == 0)
	{
		returnValue[count1][0] = 2;
		returnValue[count1][1] = 2;
		returnValue[count1][2] = (j + 2);
		count1++;
	}

	if (aiGrid[i][j] == symbol && aiGrid[i + 1][j + 1] == 0 && aiGrid[i + 2][j + 2] == symbol)
	{
		returnValue[count1][0] = 1;
		returnValue[count1][1] = 2;
		returnValue[count1][2] = (j + 1);
		count1++;
	}

	if (aiGrid[i][j] == 0 && aiGrid[i + 1][j + 1] == symbol && aiGrid[i + 2][j + 2] == symbol)
	{
		returnValue[count1][0] = 0;
		returnValue[count1][1] = 2;
		returnValue[count1][2] = j;
		count1++;
	}

	// '/' diagonal
	i = 0;
	j = 2;
	if (aiGrid[i][j] == symbol && aiGrid[i + 1][j - 1] == symbol && aiGrid[i + 2][j - 2] == 0)
	{
		returnValue[count1][0] = 2;
		returnValue[count1][1] = 3;
		returnValue[count1][2] = (j - 2);
		count1++;
	}

	if (aiGrid[i][j] == symbol && aiGrid[i + 1][j - 1] == 0 && aiGrid[i + 2][j - 2] == symbol)
	{
		returnValue[count1][0] = 1;
		returnValue[count1][1] = 3;
		returnValue[count1][2] = (j - 1);
		count1++;
	}

	if (aiGrid[i][j] == 0 && aiGrid[i + 1][j - 1] == symbol && aiGrid[i + 2][j - 2] == symbol)
	{
		returnValue[count1][0] = 0;
		returnValue[count1][1] = 3;
		returnValue[count1][2] = j;
		count1++;
	}
	return returnValue;
}

// it'll receive a position on the board that it's not available
// to play and will chose randomly of the other two positions 
int randPostion(int positionNotAvailable)
{
	int freePositions[2] = { 0 };
	if (positionNotAvailable == 0)
	{
		freePositions[0] = 1;
		freePositions[0] = 2;
	}

	if (positionNotAvailable == 1)
	{
		freePositions[0] = 0;
		freePositions[0] = 2;
	}

	if (positionNotAvailable == 2)
	{
		freePositions[0] = 0;
		freePositions[0] = 1;
	}

	return freePositions[rand() % 2];
}

// start the AI variables and gets a random seed to srand
void aiStart(int symbolToPlay)
{
	srand(time(0));
	aiSymbol = symbolToPlay;
}

// makes the AI play, accordingly to the difficulty
// and return its play coordinates
int* aiPlay(int grid[3][3], int difficulty)
{
	memcpy(aiGrid, grid, sizeof(aiGrid));
	 // easy (random) difficulty
	if (difficulty == 0)
	{
		int randPlay[9] = { 0 }; // stores number from 1 to 9 in a random order
		int repetionFlag = 0, playFlag = 0; // flags
		int count1 = 0, count2 = 0; //counters
		int i = 0, j = 0;

		// fill the randPlay array with numbers from 1 to 9 in a random order
		for (count1 = 0; randPlay[8] == 0; count1++)
		{
			randPlay[count1] = 1 + rand() % 9; // puts a random number betwenn 1 and 9
			for(count2 = 0; count2 < count1; count2++) // sees if the number is repeated
			{
				if (randPlay[count2] == randPlay[count1]) // if yes it will set the repetion flag
					repetionFlag = 1;
				while (repetionFlag == 1) // if the repetion flag is set, generates another random number that has to be diferent
				{
					randPlay[count1] = 1 + rand() % 9;
					if (randPlay[count2] != randPlay[count1]) // if sucess lowers the flag
						repetionFlag = 0;
				}
			}
		}

		// AI play
		for (count1 = 0, playFlag = 0; playFlag == 0; count1++)
		{
			// if AI already used its 9 random plays
			// will stop the AI and return negative numbers
			// probably will make the game crash or softlock
			// this should never happen because a Tie shoul be pointed before it happens
			if (count1 > 8)
			{
				aiPlayCoordinates[0] = -1;
				aiPlayCoordinates[1] = -1;
				break;
			}

			// gets a random play from the randPlay array and sees if the cell is available
			// if it is the loop is breaked and the AI plays
			// if not goes to the next element in the randPlay array
			memcpy(aiPlayCoordinates, convertToCoordinate(randPlay[count1]), sizeof(aiPlayCoordinates));
			if (grid[aiPlayCoordinates[0]][aiPlayCoordinates[1]] != 0)
				continue;
			if (grid[aiPlayCoordinates[0]][aiPlayCoordinates[1]] == 0)
				return aiPlayCoordinates;
		}
		return aiPlayCoordinates;
	}
	
	// normal difficulty
	if (difficulty == 1)
	{
		int possibleWin[8][3];

		// gets the possible wins for the AI
		memcpy(possibleWin, winPositionVerifyer(aiGrid, aiSymbol), sizeof(possibleWin));

		// if possibleWin[0][x] isn't zero,
		// the possibleWin function found a possible win
		// x can go up to 8
		// when possibleWin[0][x] is zero, there's any more possible wins
		if (possibleWin[0][2] != 0)
		{
			// if just one possible win was found
			if (possibleWin[1][2] == 0)
			{
				if (possibleWin[0][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[0][2];
					aiPlayCoordinates[1] = possibleWin[0][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][2];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 2)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 3)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][2];
					return aiPlayCoordinates;
				}
			}

			// if more than one possible win was found
			// it will select random possible win to play
			if (possibleWin[1][2] != 0)
			{
				// select a random possible win
				int winPossibilitiesCount = 0;
				for (int count = 0; count < 8; count++)
				{
					if (possibleWin[count][2] != 0)
						winPossibilitiesCount++;
				}
				winPossibilitiesCount = rand() % (++winPossibilitiesCount);

				if (possibleWin[winPossibilitiesCount][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][2];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][2];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 2)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 3)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][2];
					return aiPlayCoordinates;
				}
			}
		}

		// gets the possible wins for the player
		memcpy(possibleWin, winPositionVerifyer(aiGrid, -aiSymbol), sizeof(possibleWin));
		if (possibleWin[0][2] != 0)
		{
			if (possibleWin[1][2] == 0)
			{
				if (possibleWin[0][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[0][2];
					aiPlayCoordinates[1] = possibleWin[0][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][2];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 2)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 3)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][2];
					return aiPlayCoordinates;
				}
			}

			if (possibleWin[1][2] != 0)
			{
				int winPossibilitiesCount = 0;
				for (int count = 0; count < 8; count++)
				{
					if (possibleWin[count][2] != 0)
						winPossibilitiesCount++;
				}
				winPossibilitiesCount = rand() % (++winPossibilitiesCount);

				if (possibleWin[winPossibilitiesCount][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][2];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][2];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 2)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][0];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 3)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][2];
					return aiPlayCoordinates;
				}
			}
		}

		// if there's no possible win for player or AI
		// the Ai will search for places where it played to get a possible win in the next turn
		// --- THE ISSUE OF THE AI ON NORMAL MODE CAN BE HERE ---
		// BECAUSE THE SEARCH FOR A PLAY CAN BE OVERWRITTEN BY ANOTHER
		memcpy(possibleWin, winPositionVerifyer(aiGrid, aiSymbol), sizeof(possibleWin));
		if (possibleWin[0][2] == 0)
		{
			int freeWinPositions[9][3] = { 0 };
			int count = 0, i, j;

			for (int count = 0; count < 9; count++)
				freeWinPositions[count][2] = -1;

			// horizontal
			for (i = 0; i < 3; i++)
			{
				if (aiGrid[i][0] == 0 && aiGrid[i][1] == 0 && aiGrid[i][2] == aiSymbol)
				{
					freeWinPositions[count][0] = 2;
					freeWinPositions[count][1] = 0;
					freeWinPositions[count][2] = i;
					count++;
				}

				if (aiGrid[i][0] == 0 && aiGrid[i][1] == aiSymbol && aiGrid[i][2] == 0)
				{
					freeWinPositions[count][0] = 1;
					freeWinPositions[count][1] = 0;
					freeWinPositions[count][2] = i;
					count++;
				}

				if (aiGrid[i][0] == aiSymbol && aiGrid[i][1] == 0 && aiGrid[i][2] == 0)
				{
					freeWinPositions[count][0] = 0;
					freeWinPositions[count][1] = 0;
					freeWinPositions[count][2] = i;
					count++;
				}
			}

			// vertical
			for (j = 0; j < 3; j++)
			{
				if (aiGrid[0][j] == 0 && aiGrid[1][j] == 0 && aiGrid[2][j] == aiSymbol)
				{
					freeWinPositions[count][0] = 2;
					freeWinPositions[count][1] = 1;
					freeWinPositions[count][2] = j;
					count++;
				}

				if (aiGrid[0][j] == 0 && aiGrid[1][j] == aiSymbol && aiGrid[2][j] == 0)
				{
					freeWinPositions[count][0] = 1;
					freeWinPositions[count][1] = 1;
					freeWinPositions[count][2] = j;
					count++;
				}

				if (aiGrid[0][j] == aiSymbol && aiGrid[1][j] == 0 && aiGrid[2][j] == 0)
				{
					freeWinPositions[count][0] = 0;
					freeWinPositions[count][1] = 1;
					freeWinPositions[count][2] = j;
					count++;
				}
			}

			// '\' diagonal
			i = 0;
			j = 0;
			if (aiGrid[i][j] == 0 && aiGrid[i + 1][j + 1] == 0 && aiGrid[i + 2][j + 2] == aiSymbol)
			{
				freeWinPositions[count][0] = 2;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = (j + 2);
				count++;
			}

			if (aiGrid[i][j] == 0 && aiGrid[i + 1][j + 1] == aiSymbol && aiGrid[i + 2][j + 2] == 0)
			{
				freeWinPositions[count][0] = 1;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = (j + 1);
				count++;
			}

			if (aiGrid[i][j] == aiSymbol && aiGrid[i + 1][j + 1] == 0 && aiGrid[i + 2][j + 2] == 0)
			{
				freeWinPositions[count][0] = 0;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = j;
				count++;
			}

			// '/' diagonal
			i = 0;
			j = 2;
			if (aiGrid[i][j] == 0 && aiGrid[i + 1][j - 1] == 0 && aiGrid[i + 2][j - 2] == aiSymbol)
			{
				freeWinPositions[count][0] = 2;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = (j - 2);
				count++;
			}

			if (aiGrid[i][j] == 0 && aiGrid[i + 1][j - 1] == aiSymbol && aiGrid[i + 2][j - 2] == 0)
			{
				freeWinPositions[count][0] = 1;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = (j - 1);
				count++;
			}

			if (aiGrid[i][j] == aiSymbol && aiGrid[i + 1][j - 1] == 0 && aiGrid[i + 2][j - 2] == 0)
			{
				freeWinPositions[count][0] = 0;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = j;
				count++;
			}

			// if there's just one play
			if (freeWinPositions[1][2] == -1 && freeWinPositions[0][2] != -1)
			{
				if (possibleWin[0][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[0][2];
					aiPlayCoordinates[1] = randPostion(possibleWin[0][0]);

					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 1)
				{
					aiPlayCoordinates[0] = randPostion(possibleWin[0][0]);
					aiPlayCoordinates[1] = possibleWin[0][2];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 2)
				{
					aiPlayCoordinates[0] = randPostion(possibleWin[0][0]);
					aiPlayCoordinates[1] = aiPlayCoordinates[0];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 3)
				{
					aiPlayCoordinates[0] = randPostion(possibleWin[0][0]);
					
					if (aiPlayCoordinates[0] == 0)
						aiPlayCoordinates[1] = (aiPlayCoordinates[0] + 2);
					if (aiPlayCoordinates[0] == 1)
						aiPlayCoordinates[1] = (aiPlayCoordinates[0]);
					if (aiPlayCoordinates[0] == 2)
						aiPlayCoordinates[1] = (aiPlayCoordinates[0] - 2);
					return aiPlayCoordinates;
				}
			}

			// if there's more than one play
			// it will select random possible win to play
			if (freeWinPositions[1][2] != -1)
			{
				int winPossibilitiesCount = 0;
				// gets how many possible wins are
				for (int count = 0; count < 8; count++)
				{
					if (possibleWin[count][2] != 0)
						winPossibilitiesCount++;
				}
				// select one at random
				winPossibilitiesCount = rand() % (++winPossibilitiesCount);

				if (possibleWin[winPossibilitiesCount][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][2];
					aiPlayCoordinates[1] = randPostion(possibleWin[winPossibilitiesCount][0]);
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 1)
				{
					aiPlayCoordinates[0] = randPostion(possibleWin[winPossibilitiesCount][0]);
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][2];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 2)
				{
					aiPlayCoordinates[0] = randPostion(possibleWin[winPossibilitiesCount][0]);
					aiPlayCoordinates[1] = (aiPlayCoordinates[0]);
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 3)
				{
					aiPlayCoordinates[0] = randPostion(possibleWin[winPossibilitiesCount][0]);
					if (aiPlayCoordinates[0] == 0)
						aiPlayCoordinates[1] = (aiPlayCoordinates[0] + 2);
					if (aiPlayCoordinates[0] == 1)
						aiPlayCoordinates[1] = (aiPlayCoordinates[0]);
					if (aiPlayCoordinates[0] == 2)
						aiPlayCoordinates[1] = (aiPlayCoordinates[0] - 2);
					return aiPlayCoordinates;
				}
			}

			// if no play was found
			// play a random position
			if (freeWinPositions[0][2] == 0)
			{
				for (int playFlag = 0; playFlag == 0;)
				{
					aiPlayCoordinates[0] = rand() % 3;
					aiPlayCoordinates[1] = rand() % 3;
					if (aiGrid[aiPlayCoordinates[0]][aiPlayCoordinates[1]] == 0)
						return aiPlayCoordinates;
				}
			}

		}
	}

	// impossible difficulty (minimax algorithm)
	if (difficulty == 2)
	{
		memcpy(aiPlayCoordinates, minimaxMain(aiGrid, aiSymbol), sizeof(aiPlayCoordinates));
		return aiPlayCoordinates;
	}

	// default play, made as failsafe
	aiPlayCoordinates[0] = 2;
	aiPlayCoordinates[1] = 2;
	return aiPlayCoordinates;
}