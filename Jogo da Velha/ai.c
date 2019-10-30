#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Jogo da Velha.h"
#include "ai.h"

int aiSymbol;
static int aiGrid[3][3];

int** winPositionVerifyer(int aiGrid[3][3])
{
	static int returnValue[3];
	int i, j;

	for (i = 0; i < 3; i++)
	{
		if (aiGrid[i][0] == 1)
		{
			if (aiGrid[i][1] == 1 || aiGrid[i][2] == 1)
			{
				returnValue[0] = 1;
				returnValue[1] = 0;
				returnValue[2] = i;
				return returnValue;
			}
		}
	}

	for (j = 0; j < 3; j++)
	{
		if (aiGrid[0][j] == 1)
		{
			if (aiGrid[1][j] == 1 && aiGrid[2][j] == 1)
			{
				returnValue[0] = 1;
				returnValue[1] = 1;
				returnValue[2] = j;
				return returnValue;
			}
		}
	}

	i = 0;
	j = 0;
	if (aiGrid[i][j] == 1 && aiGrid[i + 1][j + 1] == 1 && aiGrid[i + 2][j + 2] == 1)
	{
		returnValue[0] = 1;
		returnValue[1] = 2;
		returnValue[2] = j;
		return returnValue;
	}

	i = 0;
	j = 2;
	if (aiGrid[i][j] == 1 && aiGrid[i + 1][j - 1] == 1 && aiGrid[i + 2][j - 2] == 1)
	{
		returnValue[0] = 1;
		returnValue[1] = 3;
		returnValue[2] = j;
		return returnValue;
	}

	for (i = 0; i < 3; i++)
	{
		if (aiGrid[i][0] == -1)
		{
			if (aiGrid[i][1] == -1 && aiGrid[i][2] == -1)
			{
				returnValue[0] = 1;
				returnValue[1] = 0;
				returnValue[2] = i;
				return returnValue;
			}
		}
	}

	for (j = 0; j < 3; j++)
	{
		if (aiGrid[0][j] == -1)
		{
			if (aiGrid[1][j] == -1 && aiGrid[2][j] == -1)
			{
				returnValue[0] = 1;
				returnValue[1] = 1;
				returnValue[2] = j;
				return returnValue;
			}
		}
	}

	i = 0;
	j = 0;
	if (aiGrid[i][j] == -1 && aiGrid[i + 1][j + 1] == -1 && aiGrid[i + 2][j + 2] == -1)
	{
		returnValue[0] = 1;
		returnValue[1] = 2;
		returnValue[2] = j;
		return returnValue;
	}

	i = 0;
	j = 2;
	if (aiGrid[i][j] == -1 && aiGrid[i + 1][j - 1] == -1 && aiGrid[i + 2][j - 2] == -1)
	{
		returnValue[0] = 1;
		returnValue[1] = 3;
		returnValue[2] = j;
		return returnValue;
	}

	returnValue[0] = -1;
	returnValue[1] = -1;
	returnValue[2] = -1;
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
		
	}
}