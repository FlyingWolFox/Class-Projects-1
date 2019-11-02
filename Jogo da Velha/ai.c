#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Jogo da Velha.h"
#include "ai.h"
static int aiSymbol, aiPlayCoordinates[2];
static int aiGrid[3][3];

/*verifica se falta somente um simbolo para
alguém ganhar em uma ou mais posições de vitória
retornando um array com arrays contendo as informções
de vitória. è quase uma cópia do winVerifyer em Jogo da Velha.c*/
int** winPositionVerifyer(int aiGrid[3][3], int symbol)
{
	static int returnValue[8][3] = { 0 };
	int i, j, count1 = 0;

	for (i = 0; i < 3; i++)
	{
		if (aiGrid[i][0] == symbol && aiGrid[i][1] == symbol && aiGrid[i][2] !=-symbol)
		{
			returnValue[count1][0] = 2;
			returnValue[count1][1] = 0;
			returnValue[count1][2] = i;
			count1++;
		}

		if (aiGrid[i][0] == symbol && aiGrid[i][1] !=-symbol && aiGrid[i][2] == symbol)
		{
			returnValue[count1][0] = 1;
			returnValue[count1][1] = 0;
			returnValue[count1][2] = i;
			count1++;
		}

		if (aiGrid[i][0] !=-symbol && aiGrid[i][1] == symbol && aiGrid[i][2] == symbol)
		{
			returnValue[count1][0] = 0;
			returnValue[count1][1] = 0;
			returnValue[count1][2] = i;
			count1++;
		}
	}

	for (j = 0; j < 3; i++)
	{
		if (aiGrid[0][j] == symbol && aiGrid[1][j] == symbol && aiGrid[2][j] !=-symbol)
		{
			returnValue[count1][0] = 2;
			returnValue[count1][1] = 1;
			returnValue[count1][2] = j;
			count1++;
		}

		if (aiGrid[0][j] == symbol && aiGrid[1][j] !=-symbol && aiGrid[2][j] == symbol)
		{
			returnValue[count1][0] = 1;
			returnValue[count1][1] = 1;
			returnValue[count1][2] = j;
			count1++;
		}

		if (aiGrid[0][j] !=-symbol && aiGrid[1][j] == symbol && aiGrid[2][j] == symbol)
		{
			returnValue[count1][0] = 0;
			returnValue[count1][1] = 1;
			returnValue[count1][2] = j;
			count1++;
		}
	}

	i = 0;
	j = 0;
	if (aiGrid[i][j] == symbol && aiGrid[i + 1][j + 1] == symbol && aiGrid[i + 2][j + 2] !=-symbol)
	{
		returnValue[count1][0] = 2;
		returnValue[count1][1] = 1;
		returnValue[count1][2] = j;
		count1++;
	}

	i = 0;
	j = 2;
	if (aiGrid[i][j] == symbol && aiGrid[i + 1][j - 1] == symbol && aiGrid[i + 2][j - 2] !=-symbol)
	{
		returnValue[count1][0] = 2;
		returnValue[count1][1] = 1;
		returnValue[count1][2] = j;
		count1++;
	}
	return returnValue;
}

//inicia as variáveis da I.A.
void aiStart(int symbolToPlay)
{
	srand(time(0));
	aiSymbol = symbolToPlay;
}

/*faz a I.A. jogar, de acordo com a dificuldade
e retorna as coordenadas de seua jogada*/
int* aiPlay(int grid[3][3], int difficulty)
{
	static int aiFreeCells[4][2];
	memcpy(aiGrid, grid, sizeof(aiGrid));
	memcpy(aiFreeCells, freeCells(grid), sizeof(aiFreeCells));

	if (difficulty == 0)
	{
		int randPlay[9] = { 0 };
		int repetionFlag = 0, playFlag = 0;
		int count1 = 0, count2 = 0;
		int i = 0, j = 0;
		int aiPlayCoordinates[2];
		for (count1 = 0; randPlay[8] == 0; count1++)
		{
			randPlay[count1] = 1 + rand() % 9;
			for(count2 = 0; count2 < count1; count2++)
			{
				if (randPlay[count2] == randPlay[count1])
					repetionFlag = 1;
				while (repetionFlag == 1)
				{
					randPlay[count1] = 1 + rand() % 9;
					if (randPlay[count2] != randPlay[count1])
						repetionFlag = 0;
				}
			}
		}
		for (count1 = 0, playFlag = 0; playFlag == 0; count1++)
		{
			if (count1 > 8)
			{
				aiPlayCoordinates[0] = -1;
				aiPlayCoordinates[1] = -1;
				break;
			}
			memcpy(aiPlayCoordinates, convertToCoordinate(randPlay[count1]), sizeof(aiPlayCoordinates));
			if (grid[aiPlayCoordinates[0]][aiPlayCoordinates[1]] != 0)
				continue;
			if (grid[aiPlayCoordinates[0]][aiPlayCoordinates[1]] == 0)
				return aiPlayCoordinates;
		}
		return aiPlayCoordinates;
	}
	
	if (difficulty == 1)
	{
		int possibleWin[8][3];

		//1 - verificar se o player pode vencer na próxima jogada
		memcpy(possibleWin, winPositionVerifyer(aiGrid, -aiSymbol), sizeof(possibleWin));
		if (possibleWin[0][2] != 0)
		{
			if (possibleWin[1][2] == 0)
			{
				if (possibleWin[0][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[0][2];
					aiPlayCoordinates[1] = possibleWin[0][1];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][1];
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
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][1];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][1];
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

		memcpy(possibleWin, winPositionVerifyer(aiGrid, aiSymbol), sizeof(possibleWin));
		if (possibleWin[0][2] != 0)
		{
			if (possibleWin[1][2] == 0)
			{
				if (possibleWin[0][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[0][2];
					aiPlayCoordinates[1] = possibleWin[0][1];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][1];
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
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][1];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][1];
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

		if (possibleWin[0][2] == 0)
		{
			int freeWinPositions[8][3] = { 0 };
			int count = 0, i, j;

			for (i = 0; i < 3; i++)
			{
				if (aiGrid[i][0] == 0 && aiGrid[i][1] == 0 && aiGrid[i][2] != aiSymbol)
				{
					freeWinPositions[count][0] = 2;
					freeWinPositions[count][1] = 0;
					freeWinPositions[count][2] = i;
					count++;
				}

				if (aiGrid[i][0] == 0 && aiGrid[i][1] != aiSymbol && aiGrid[i][2] == 0)
				{
					freeWinPositions[count][0] = 1;
					freeWinPositions[count][1] = 0;
					freeWinPositions[count][2] = i;
					count++;
				}

				if (aiGrid[i][0] != aiSymbol && aiGrid[i][1] == 0 && aiGrid[i][2] == 0)
				{
					freeWinPositions[count][0] = 0;
					freeWinPositions[count][1] = 0;
					freeWinPositions[count][2] = i;
					count++;
				}
			}

			for (j = 0; j < 3; i++)
			{
				if (aiGrid[0][j] == 0 && aiGrid[1][j] == 0 && aiGrid[2][j] != aiSymbol)
				{
					freeWinPositions[count][0] = 2;
					freeWinPositions[count][1] = 1;
					freeWinPositions[count][2] = j;
					count++;
				}

				if (aiGrid[0][j] == 0 && aiGrid[1][j] != aiSymbol && aiGrid[2][j] == 0)
				{
					freeWinPositions[count][0] = 1;
					freeWinPositions[count][1] = 1;
					freeWinPositions[count][2] = j;
					count++;
				}

				if (aiGrid[0][j] != aiSymbol && aiGrid[1][j] == 0 && aiGrid[2][j] == 0)
				{
					freeWinPositions[count][0] = 0;
					freeWinPositions[count][1] = 1;
					freeWinPositions[count][2] = j;
					count++;
				}
			}

			i = 0;
			j = 0;
			if (aiGrid[i][j] == 0 && aiGrid[i + 1][j + 1] == 0 && aiGrid[i + 2][j + 2] != aiSymbol)
			{
				freeWinPositions[count][0] = 2;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = j;
				count++;
			}

			i = 0;
			j = 2;
			if (aiGrid[i][j] == 0 && aiGrid[i + 1][j - 1] == 0 && aiGrid[i + 2][j - 2] != aiSymbol)
			{
				freeWinPositions[count][0] = 2;
				freeWinPositions[count][1] = 1;
				freeWinPositions[count][2] = j;
				count++;
			}

			if (freeWinPositions[1][2] == 0)
			{
				if (possibleWin[0][1] == 0)
				{
					aiPlayCoordinates[0] = possibleWin[0][2];
					aiPlayCoordinates[1] = possibleWin[0][1];
					return aiPlayCoordinates;
				}

				if (possibleWin[0][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[0][0];
					aiPlayCoordinates[1] = possibleWin[0][1];
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

			if (freeWinPositions[1][2] != 0)
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
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][1];
					return aiPlayCoordinates;
				}

				if (possibleWin[winPossibilitiesCount][1] == 1)
				{
					aiPlayCoordinates[0] = possibleWin[winPossibilitiesCount][0];
					aiPlayCoordinates[1] = possibleWin[winPossibilitiesCount][1];
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

	if (difficulty == 2)
	{

	}
}