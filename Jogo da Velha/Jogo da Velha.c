#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jogo da Velha.h"
#include "ai.h"

/*verifica se alguém venceu e retorna um array[3]
caso verdade, retorna {1, W, C},
sendo W o tipo de vitória:
0 = Horizontal, 1 = Vertical
2 = Diagonal 1 (\), 3 = Diagonal 2 (/)
sendo C uma coordenada, i para vitória
horizontal e j para o resto */
int* winVerifyer(int grid[3][3])
{
	static int returnValue[3];
	int i, j;

	for (i = 0; i < 3; i++)
	{
		if (grid[i][0] == 1)
		{
			if (grid[i][1] == 1 && grid[i][2] == 1)
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
		if (grid[0][j] == 1)
		{
			if (grid[1][j] == 1 && grid[2][j] == 1)
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
	if (grid[i][j] == 1 && grid[i + 1][j + 1] == 1 && grid[i + 2][j + 2] == 1)
	{
		returnValue[0] = 1;
		returnValue[1] = 2;
		returnValue[2] = j;
		return returnValue;
	}

	i = 0;
	j = 2;
	if (grid[i][j] == 1 && grid[i + 1][j - 1] == 1 && grid[i + 2][j - 2] == 1)
	{
		returnValue[0] = 1;
		returnValue[1] = 3;
		returnValue[2] = j;
		return returnValue;
	}

	for (i = 0; i < 3; i++)
	{
		if (grid[i][0] == -1)
		{
			if (grid[i][1] == -1 && grid[i][2] == -1)
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
		if (grid[0][j] == -1)
		{
			if (grid[1][j] == -1 && grid[2][j] == -1)
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
	if (grid[i][j] == -1 && grid[i + 1][j + 1] == -1 && grid[i + 2][j + 2] == -1)
	{
		returnValue[0] = 1;
		returnValue[1] = 2;
		returnValue[2] = j;
		return returnValue;
	}

	i = 0;
	j = 2;
	if (grid[i][j] == -1 && grid[i + 1][j - 1] == -1 && grid[i + 2][j - 2] == -1)
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

/*verifica se há até 3 casas livres
e retorna as 3 posições, ou menos*/
int** freeCells(int grid[3][3])
{
	static int freePositions[4][2];
	int count1;

	freePositions[3][0] = -1;
	freePositions[3][1] = -1;
	freePositions[2][0] = -1;
	freePositions[2][1] = -1;
	freePositions[1][0] = -1;
	freePositions[1][1] = -1;
	freePositions[0][0] = -1;
	freePositions[0][1] = -1;
	count1 = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (count1 > 3)
			{
				freePositions[2][0] = -1;
				freePositions[2][1] = -1;
				freePositions[1][0] = -1;
				freePositions[1][1] = -1;
				freePositions[0][0] = -1;
				freePositions[0][1] = -1;
				return freePositions;
			}
			if (grid[i][j] == 0)
			{
				freePositions[count1][0] = i;
				freePositions[count1][1] = j;
				count1++;
			}
		}
	}
	if (freePositions[2][0] == -1 && freePositions[2][1] == -1 && freePositions[1][0] == -1 && freePositions[1][1] == -1 && freePositions[0][0] == -1 && freePositions[0][1] == -1)
	{
		freePositions[3][0] = 0;
		freePositions[3][1] = 0;
		freePositions[2][0] = 0;
		freePositions[2][1] = 0;
		freePositions[1][0] = 0;
		freePositions[1][1] = 0;
		freePositions[0][0] = 0;
		freePositions[0][1] = 0;
	}
	return freePositions;
}


/*retem a gridCopy usada na tieVerifyer
para passá-la para a main*/
int** gridTiedReturner(int gridCopy[3][3], int mod)
{
	static int gridCopyToReturn[3][3];

	if (mod == 0)
		memcpy(gridCopyToReturn, gridCopy, sizeof(gridCopyToReturn));
	if (mod == 1)
		return gridCopyToReturn;
	return 0;
}

/*verifica se o jogo vai empatar daqui 3, 2 ou 1 jogada(s)
caso empate, retorna 1
caso não, retorna 0*/
int tieVerifyer(int grid[3][3], int player, int insertionPreference)
{
	static int gridCopy[3][3];
	int symbol = 0, winVerifyerReturn[4], freeCellsReturn[4][2];
	
	gridTiedReturner(gridCopy, 0);

	memcpy(gridCopy, grid, sizeof(gridCopy));
	memcpy(freeCellsReturn, freeCells(grid), sizeof(freeCellsReturn));
	if (player == 3)
	{
		player = 1;
		symbol = insertionPreference;
	}

	if (player == 2)
		symbol = -insertionPreference;

	if (freeCellsReturn[0][0] == 0 && freeCellsReturn[0][1] == 0 && freeCellsReturn[1][0] == 0 && freeCellsReturn[1][1] == 0)
	{
		gridTiedReturner(gridCopy, 0);
		return 1;
	}

	if (freeCellsReturn[1][0] == -1 && freeCellsReturn[1][1] == -1 && freeCellsReturn[2][0] == -1 && freeCellsReturn[2][1] == -1)
	{
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;
		gridTiedReturner(gridCopy, 0);
		return 1;
	}

	if (freeCellsReturn[1][0] != -1 && freeCellsReturn[1][1] != -1  && freeCellsReturn[2][0] == -1 && freeCellsReturn[2][1] == -1)
	{
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = -symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = -symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));
		if (winVerifyerReturn[0] == 1)
			return 0;
		gridTiedReturner(gridCopy, 0);
		return 1;
	}

	if (freeCellsReturn[1][0] != -1 && freeCellsReturn[1][1] != -1 && freeCellsReturn[2][0] != -1 && freeCellsReturn[2][1] != -1)
	{
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = -symbol;
		gridCopy[freeCellsReturn[2][0]][freeCellsReturn[2][1]] = symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;

		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = symbol;
		gridCopy[freeCellsReturn[2][0]][freeCellsReturn[2][1]] = -symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;

		gridTiedReturner(gridCopy, 0);
		return 1;
	}
	gridTiedReturner(gridCopy, 0);
	return 1;
}

//converte o posicionamento de 1 a 9 por coordenadas
int* convertToCoordinate(int position)
{
	static int coordinate[2];
	if (position == 1)
	{
		coordinate[0] = 0;
		coordinate[1] = 0;
	}
	if (position == 2)
	{
		coordinate[0] = 0;
		coordinate[1] = 1;
	}
	if (position == 3)
	{
		coordinate[0] = 0;
		coordinate[1] = 2;
	}
	if (position == 4)
	{
		coordinate[0] = 1;
		coordinate[1] = 0;
	}
	if (position == 5)
	{
		coordinate[0] = 1;
		coordinate[1] = 1;
	}
	if (position == 6)
	{
		coordinate[0] = 1;
		coordinate[1] = 2;
	}
	if (position == 7)
	{
		coordinate[0] = 2;
		coordinate[1] = 0;
	}
	if (position == 8)
	{
		coordinate[0] = 2;
		coordinate[1] = 1;
	}
	if (position == 9)
	{
		coordinate[0] = 2;
		coordinate[1] = 2;
	}

	return coordinate;
}

//converte as coordenadas da grade para coordenadas da
//super grade
int* coordinatesToSupergrid(int coordinates[2])
{
	static int supergridCoordinates[2];
	if (coordinates[0] == 0)
	{
		supergridCoordinates[0] = 1;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 18;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 36;
	}

	if (coordinates[0] == 1)
	{
		supergridCoordinates[0] = 12;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 18;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 36;
	}

	if (coordinates[0] == 2)
	{
		supergridCoordinates[0] = 23;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 18;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 36;
	}
	return supergridCoordinates;
}

//modifica a super grade, botando X ou O
void superGridModifier(char supergrid[31][51], int grid[3][3])
{
	int supergridCoordinates[2], gridCoordinates[2];
	int symbolI = 0, symbolJ = 0;
	int supergridI, supergridJ;
	char x[8][14] = { {' ','8', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'd', '8', ' '},
					  {' ',' ', 'Y', '8', ',', ' ', ' ', ' ', ' ', ',', '8', 'P', ' ', ' '},
					  {' ',' ', ' ', '`', '8', 'b', ' ', ' ', 'd', '8', '\'', ' ', ' ', ' '},
					  {' ',' ', ' ', ' ', ' ', 'Y', '8', '8', 'P', ' ', ' ', ' ', ' ', ' '},
					  {' ',' ', ' ', ' ', ' ', 'd', '8', '8', 'b', ' ', ' ', ' ', ' ', ' '},
					  {' ',' ', ' ', ',', '8', 'P', ' ', ' ', 'Y', '8', ',', ' ', ' ', ' '},
					  {' ',' ', 'd', '8', '\'', ' ', ' ', ' ', ' ', '`', '8', 'b', ' ', ' '},
					  {' ','8', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Y', '8', ' '} };

	char o[8][14] = { {' ', ' ', ',', 'a', 'd', '8', '8', '8', '8', 'b', 'a', ',', ' ', ' ' },
					  {' ', 'd', '8', '"', '\'', ' ', ' ', ' ', ' ', '`', '"', '8', 'b', ' ' },
					  {'d', '8', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '`', '8', 'b'},
					  {'8', '8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', '8'},
					  {'8', '8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', '8' },
					  {'Y', '8', ',', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ',', '8', 'P'},
					  {' ', 'Y', '8', 'a', '.', ' ', ' ', ' ', ' ', '.', 'a', '8', 'P', ' '},
					  {' ', ' ', '`', '"', 'Y', '8', '8', '8', '8', 'Y', '"', '\'', ' ', ' '} };

	for (gridCoordinates[0] = 0; gridCoordinates[0] < 3; gridCoordinates[0]++)
	{
		for (gridCoordinates[1] = 0; gridCoordinates[1] < 3; gridCoordinates[1]++)
		{
			memcpy(supergridCoordinates, coordinatesToSupergrid(gridCoordinates), sizeof(supergridCoordinates));
			supergridI = supergridCoordinates[0];
			supergridJ = supergridCoordinates[1];
			symbolI = 0;
			for (supergridCoordinates[0] = supergridI; supergridCoordinates[0] < supergridI + 8; supergridCoordinates[0]++)
			{
				symbolJ = 0;
				for (supergridCoordinates[1] = supergridJ; supergridCoordinates[1] < supergridJ + 14; supergridCoordinates[1]++)
				{
					if (grid[gridCoordinates[0]][gridCoordinates[1]] == 1)
						supergrid[supergridCoordinates[0]][supergridCoordinates[1]] = x[symbolI][symbolJ];
					if (grid[gridCoordinates[0]][gridCoordinates[1]] == -1)
						supergrid[supergridCoordinates[0]][supergridCoordinates[1]] = o[symbolI][symbolJ];
					symbolJ++;
				}
				symbolI++;
			}
		}
	}

}

//imprime a grade
void gridPrinter(int grid[3][3], int mod)
{
	static char superGrid[31][51];
	int i, j;
	//cria a super grade
	if (mod == 0)
	{
		for (i = 0; i < 31; i++)
		{
			for (j = 0; j < 51; j++)
			{
				if (j == 15 || j == 16 || j == 33 || j == 34 || i == 10 || i == 21)
				{
					superGrid[i][j] = '#';
				}
				else if (j == 50)
				{
					superGrid[i][j] = '\n';
				}
				else
					superGrid[i][j] = ' ';
			}
		}
		for (i = 0; i < 31; i++)
		{
			superGrid[i][50] = '\n';
		}
	}
	//somente imprime a super grade
	if (mod == 1)
	{
		for (int i = 0; i < 31; i++)
		{
			printf(" ");
			for (int j = 0; j < 51; j++)
			{
				printf("%c", superGrid[i][j]);
			}
		}
	}
	//chama a função que modifica a grade e imprime depois
	if (mod == 2)
	{
		superGridModifier(superGrid, grid);
		for (int i = 0; i < 31; i++)
		{
			printf(" ");
			for (int j = 0; j < 51; j++)
			{
				printf("%c", superGrid[i][j]);
			}
		}
	}
	//imprime a grade com números de 1 a 9 nela
	if (mod == 3)
	{
		printf("\n                ##               ##              \n         88     ##   ad888888b,  ##   ad888888b,  \n       ,d88     ##  d8\"     \"88  ##  d8\"     \"88  \n     888888     ##          a8P  ##          a8P  \n         88     ##       ,d8P\"   ##       aad8\"   \n         88     ##     a8P\"      ##       \"\"Y8,   \n         88     ##   a8P\'        ##          \"8b  \n         88     ##  d8\"          ##  Y8,     a88  \n         88     ##  88888888888  ##   \"Y888888P\' \n                ##               ##               \n ################################################\n                ##               ##                 \n          ,d8   ##  8888888888   ##    ad8888ba,  \n        ,d888   ##  88           ##   8P\'    \"Y8  \n      ,d8\" 88   ##  88  ____     ##  d8           \n    ,d8\"   88   ##  88a8PPPP8b,  ##  88,dd888bb,  \n  ,d8\"     88   ##  PP\"     `8b  ##  88P\'    `8b  \n  8888888888888 ##           d8  ##  88       d8  \n           88   ##  Y8a     a8P  ##  88a     a8P  \n           88   ##   \"Y88888P\"   ##   \"Y88888P\"   \n                ##               ##               \n ################################################\n                ##               ##                  \n  888888888888  ##   ad88888ba   ##   ad88888ba   \n           8P\'  ##  d8\"     \"8b  ##  d8\"     \"88  \n         d8\"    ##  Y8a     a8P  ##  8P       88  \n       ,8P\'     ##    \"Y8aaa8P\"  ##  Y8,    ,d88  \n      d8\"       ##   ,d8\"\"\"8b,   ##   \"PPPPPP\"88  \n    ,8P\'        ##  d8\"     \"8b  ##           8P \n   d8\"          ##  Y8a     a8P  ##  8b,    a8P   \n  8P\'           ##   \"Y88888P\"   ##  `\"Y8888P\'    \n");
	}
	//imprime a grade com as coordenadas de (1,1) até (3,3)
	if (mod == 4)
	{
		printf("\n                ##               ##              \n                ##               ##              \n   /         \\  ##  /      __ \\  ##  /      __ \\ \n  ( /|    /|  ) ## ( /|     _) ) ## ( /|    __) )\n   \\ |  /  | /  ##  \\ |  / /__/  ##  \\ |  / __)/ \n                ##               ##              \n                ##               ##              \n                ##               ##              \n ##############################################\n                ##               ##              \n                ##               ##              \n   /__       \\  ##  /__    __ \\  ##  /__    __ \\ \n  (  _)   /|  ) ## (  _)    _) ) ## (  _)   __) )\n   \\/__ /  | /  ##  \\/__ / /__/  ##  \\/__ / __)/ \n                ##               ##              \n                ##               ##              \n                ##               ##              \n ##############################################\n                ##               ##              \n                ##               ##              \n   /__       \\  ##  /__    __ \\  ##  /__    __ \\ \n  ( __)   /|  ) ## ( __)    _) ) ## ( __)   __) )\n   \\__) /  | /  ##  \\__) / /__/  ##  \\__) / __)/ \n                ##               ##              \n                ##               ##              \n                ##               ##              \n");
	}
	//imprime a grade com o risco de vitória
	if (mod == 5)
	{
		superGridModifier(superGrid, grid);

		int winVerifyerReturn[4];

		memcpy(winVerifyerReturn, winVerifyer(grid), sizeof(winVerifyerReturn));
		printf(" ");
		if (winVerifyerReturn[1] == 0)
		{
			if (winVerifyerReturn[2] == 0)
			{
				for (j = 0; j < 50; j++)
				{
					superGrid[3][j] = ':';
					superGrid[4][j] = ':';
				}
			}

			if (winVerifyerReturn[2] == 1)
			{
				for (j = 0; j < 50; j++)
				{
					superGrid[14][j] = ':';
					superGrid[15][j] = ':';
				}
			}

			if (winVerifyerReturn[2] == 2)
			{
				for (j = 0; j < 50; j++)
				{
					superGrid[25][j] = ':';
					superGrid[26][j] = ':';
				}
			}
		}

		if (winVerifyerReturn[1] == 1)
		{
			if (winVerifyerReturn[2] == 0)
			{
				for (i = 0; i < 31; i++)
				{
					superGrid[i][7] = ':';
					superGrid[i][8] = ':';
				}
			}

			if (winVerifyerReturn[2] == 1)
			{
				for (i = 0; i < 31; i++)
				{
					superGrid[i][25] = ':';
					superGrid[i][26] = ':';
				}
			}

			if (winVerifyerReturn[2] == 2)
			{
				for (i = 0; i < 31; i++)
				{
					superGrid[i][43] = ':';
					superGrid[i][44] = ':';
				}
			}
		}

		if (winVerifyerReturn[1] == 2)
		{
			j = 0;
			int jCopy = -1;
			for (i = 0; i < 31; i++)
			{

				for (jCopy = j; j < jCopy + 3; j++)
				{
					superGrid[i][j] = '\\';
				}
				i++;
				j = jCopy + 1;
				for (jCopy = j; j < jCopy + 3; j++)
				{
					superGrid[i][j] = '\\';
				}
				i++;
				j = jCopy + 1;
				for (jCopy = j; j < jCopy + 3; j++)
				{
					superGrid[i][j] = '\\';
				}
				if (i == 26)
				{
					for (i = 27; i < 31; i++)
					{
						j = jCopy + 1;
						for (jCopy = j; j < jCopy + 3; j++)
						{
							superGrid[i][j] = '\\';
						}
					}

				}
			}
		}

		if (winVerifyerReturn[1] == 3)
		{
			j = 49;
			int jCopy;
			for (i = 0; i < 31; i++)
			{

				for (jCopy = j; j > jCopy - 3; j--)
				{
					superGrid[i][j] = '/';
				}
				i++;
				j = jCopy - 1;
				for (jCopy = j; j > jCopy - 3; j--)
				{
					superGrid[i][j] = '/';
				}
				i++;
				j = jCopy - 1;
				for (jCopy = j; j > jCopy - 3; j--)
				{
					superGrid[i][j] = '/';
				}
				if (i == 26)
				{
					for (i = 27; i < 31; i++)
					{
						j = jCopy - 1;
						for (jCopy = j; j > jCopy - 3; j--)
						{
							superGrid[i][j] = '/';
						}
					}

				}
			}
		}
		
		for (i = 0; i < 31; i++)
		{
			for (j = 0; j < 51; j++)
			{
				printf("%c", superGrid[i][j]);
			}
			printf(" ");
		}
	
	}
}

//imprime os agradecimentos
void thanks()
{
	printf("\nMuito Obrigado por Jogar!\n");
	printf("Agradecimentos especiais para:\n");
	printf("Minha mãe, que, mesmo não sabendo nada de código, me ouviu e ajudou a clarear as idéias,\n");
	printf("Patrick Gillespie (twiiter @patorjk) e seu Text to ASCII Art Generator (http://patorjk.com/software/taag)\n");
	printf("\n");
	printf("Esse projeto é possível graças ao Notepad++ e ao Visual Studio Community 2019\n");
	printf("\n");
	printf("Autoria de Lucas Isaac (@FlyingWolFox)\n");
	system("pause");
}

int main(int argc, char* argv[])
{
	static int grid[3][3] = { 0 };
	int playCoordinates[2] = { 0 }, playPosition, player;
	int insertionPreference, symbolPreference;
	int win = 0, tie = 0;
	int tieFlag = 0;
	int freeCellsReturn[4][2];
	char keepPlaying;
	keepPlaying = 'x';

	printf("Iniciando Jogo da Velha!\n");
	printf("Como gostaria o tabuleiro? (Alerta, muitas linhas! Pressione enter para continuar)\n");
	if(getchar() == '\n');
	printf("1: As posições vão de 1 a 9\n");
	gridPrinter(grid, 3);
	printf("\n2: As posições são coordenadas to tipo (x,y)\n");
	gridPrinter(grid, 4);
	if (scanf("%i", &insertionPreference) == 1);
	printf("Gostaria de jogar o modo: 1- Singleplyer ou 2- Multiplayer\n");
	if (scanf("%i", &player) == 1);
	printf("Com qual gostaria de jogar? 1- X ou 2- O\n");
	if (scanf("%i", &symbolPreference) == 2);
	if (symbolPreference == 2)
		symbolPreference = -1;

	if (player == 2)
	{
		while (keepPlaying != 'n' && keepPlaying != 'N')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					grid[i][j] = 0;
				}
			}
			player = 1;
			gridPrinter(grid, 0);
			win = 0;
			tie = 0;
			tieFlag = 0;
			while (win == 0 && tie == 0)
			{
				printf("\033[2J"); //funciona como system("clear") ou system("cls");
				gridPrinter(grid, 2);
				if (player == 3)
					player = 1;
				printf("Jogue, Jogador %i\n", player);
				if (insertionPreference == 1)
				{
					if (scanf("%i", &playPosition) == 1);
					memcpy(playCoordinates, convertToCoordinate(playPosition), sizeof(playCoordinates));
				}
				if (insertionPreference == 2)
				{
					if (scanf("%i %i", &playCoordinates[0], &playCoordinates[1]) == 2);
					playCoordinates[0]--;
					playCoordinates[1]--;
				}
				if (playCoordinates[0] < 0 || playCoordinates[1] < 0)
					break;
				if (grid[playCoordinates[0]][playCoordinates[1]] != 0)
				{
					printf("\nEssa casa já foi marcada!\n");
					system("pause");
					continue;
				}
				if (player == 1)
					grid[playCoordinates[0]][playCoordinates[1]] = symbolPreference;
				if (player == 2)
					grid[playCoordinates[0]][playCoordinates[1]] = -symbolPreference;
				if ((winVerifyer(grid))[0] == 1)
				{
					gridPrinter(grid, 5);
					printf("\nJogador %i venceu!", player);
					win = 1;
					break;
				}
				player++;
				memcpy(freeCellsReturn, freeCells(grid), sizeof(freeCellsReturn));
				if (freeCellsReturn[0][0] != -1)
				{
					if (tieVerifyer(grid, player, insertionPreference) == 1)
					{
						memcpy(grid, gridTiedReturner(grid, 1), sizeof(grid));
						gridPrinter(gridTiedReturner(grid, 1), 2);
						printf("\nDeu velha...\n");
						tie = 1;
						break;
					}
				}
			}
			printf("\nContinuar Jogando?\n s- Sim  n- Não\n");
			if(getchar() == '\n');
			if (scanf("%c", &keepPlaying) == 1);
			player = 0;
		}
	}
	
	if (player == 1)
	{
		while (keepPlaying != 'n' && keepPlaying != 'N')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					grid[i][j] = 0;
				}
			}
			player = 1;
			gridPrinter(grid, 0);
			win = 0;
			tie = 0;
			tieFlag = 0;
			while (win == 0 && tie == 0)
			{
				printf("\033[2J"); //funciona como system("clear") ou system("cls");
				gridPrinter(grid, 2);
				if (player == 3)
					player = 1;
				printf("Jogue, Jogador %i\n", player);
				if (insertionPreference == 1)
				{
					if (scanf("%i", &playPosition) == 1);
					memcpy(playCoordinates, convertToCoordinate(playPosition), sizeof(playCoordinates));
				}
				if (insertionPreference == 2)
				{
					if (scanf("%i %i", &playCoordinates[0], &playCoordinates[1]) == 2);
					playCoordinates[0]--;
					playCoordinates[1]--;
				}
				if (playCoordinates[0] < 0 || playCoordinates[1] < 0)
					break;
				if (grid[playCoordinates[0]][playCoordinates[1]] != 0)
				{
					printf("\nEssa casa já foi marcada!\n");
					system("pause");
					continue;
				}
				if (player == 1)
					grid[playCoordinates[0]][playCoordinates[1]] = symbolPreference;
				if (player == 2)
					grid[playCoordinates[0]][playCoordinates[1]] = -symbolPreference;
				if ((winVerifyer(grid))[0] == 1)
				{
					gridPrinter(grid, 5);
					printf("\nJogador %i venceu!", player);
					win = 1;
					break;
				}
				player++;
				memcpy(freeCellsReturn, freeCells(grid), sizeof(freeCellsReturn));
				if (freeCellsReturn[0][0] != -1)
				{
					if (tieVerifyer(grid, player, insertionPreference) == 1)
					{
						memcpy(grid, gridTiedReturner(grid, 1), sizeof(grid));
						gridPrinter(gridTiedReturner(grid, 1), 2);
						printf("\nDeu velha...\n");
						tie = 1;
						break;
					}
				}
			}
			printf("\nContinuar Jogando?\n s- Sim  n- Não\n");
			if (getchar() == '\n');
			if (scanf("%c", &keepPlaying) == 1);
		}
	}

	if (keepPlaying == 'n')
		thanks();
}