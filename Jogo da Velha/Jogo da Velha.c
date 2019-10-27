#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

/*verifica se alguém venceu, caso X vence, retorna 1
Caso O vence, retorna -1
caso não haja vitória, retorna 0*/
int winVerifyer(int grid[3][3])
{
	if (grid[0][0] == 1)
	{
		if (grid[0][1] == 1 && grid[0][2] == 1)
			return 1;
		if (grid[1][0] == 1 && grid[2][0] == 1)
			return 1;
		if (grid[1][1] == 1 && grid[2][2] == 1)
			return 1;
	}
	if (grid[0][1] == 1)
	{
		if (grid[1][1] == 1 && grid[2][1] == 1)
			return 1;
	}
	if (grid[0][2] == 1)
	{
		if (grid[1][2] == 1 && grid[2][2] == 1)
			return 1;
		if (grid[1][1] == 1 && grid[2][0] == 1)
			return 1;
	}
	if (grid[1][0] == 1 && grid[1][1] == 1 && grid[1][2] == 1)
		return 1;
	if (grid[2][0] == 1 && grid[2][1] == 1 && grid[2][2] == 1)
		return 1;

	if (grid[0][0] == -1)
	{
		if (grid[0][1] == -1 && grid[0][2] == -1)
			return -1;
		if (grid[1][0] == -1 && grid[2][0] == -1)
			return -1;
		if (grid[1][1] == -1 && grid[2][2] == -1)
			return -1;
	}
	if (grid[0][1] == -1)
	{
		if (grid[1][1] == -1 && grid[2][1] == -1)
			return -1;
	}
	if (grid[0][2] == -1)
	{
		if (grid[1][2] == -1 && grid[2][2] == -1)
			return -1;
		if (grid[1][1] == -1 && grid[2][0] == -1)
			return -1;
	}
	if (grid[1][0] == -1 && grid[1][1] == -1 && grid[1][2] == -1)
		return -1;
	if (grid[2][0] == -1 && grid[2][1] == -1 && grid[2][2] == -1)
		return -1;
	else
		return 0;
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
		supergridCoordinates[0] = 0;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 16;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 32;
	}

	if (coordinates[0] == 1)
	{
		supergridCoordinates[0] = 9;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 16;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 32;
	}

	if (coordinates[0] == 2)
	{
		supergridCoordinates[0] = 18;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 16;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 32;
	}
	return supergridCoordinates;
}

//modifica a super grade, botando X ou O
void superGridModifier(char supergrid[26][46], int grid[3][3])
{
	int supergridCoordinates[2], gridCoordinates[2];
	int symbolX = 0, symbolY = 0;
	int supergridX, supergridY;
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

	for (gridCoordinates[0] = 0; gridCoordinates[0] < 4; gridCoordinates[0]++)
	{
		for (gridCoordinates[1] = 0; gridCoordinates[1] < 4; gridCoordinates[1]++)
		{
			memcpy(supergridCoordinates, coordinatesToSupergrid(gridCoordinates), sizeof(supergridCoordinates));
			supergridX = supergridCoordinates[0];
			supergridY = supergridCoordinates[1];
			symbolY = 0;
			for (; supergridCoordinates[1] < supergridY + 8; supergridCoordinates[1]++)
			{
				symbolX = 0;
				for (; supergridCoordinates[0] < supergridX + 14; supergridCoordinates[0]++)
				{
					if (grid[gridCoordinates[0]][gridCoordinates[1]] == 1)
						supergrid[supergridCoordinates[0]][supergridCoordinates[1]] = x[symbolX][symbolY];
					if (grid[gridCoordinates[0]][gridCoordinates[1]] == -1)
						supergrid[supergridCoordinates[0]][supergridCoordinates[1]] = o[symbolX][symbolY];
					symbolX++;
				}
				symbolY++;
			}
		}
	}

}

//imprime a grade
void gridPrinter(int grid[3][3], int mod)
{
	static char superGrid[26][46];
	//cria a super grade
	if (mod == 0)
	{
		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 46; j++)
			{
				if (j == 14 || j == 15 || j == 30 || j == 31 || i == 8 || i == 17)
				{
					superGrid[i][j] = '#';
				}
				else if (j == 45)
				{
					superGrid[i][j] = '\n';
				}
				else
					superGrid[i][j] = ' ';
				superGrid[8][45] = '\n';
				superGrid[17][45] = '\n';
			}
		}
	}
	//somente imprime a super grade
	if (mod == 1)
	{
		for (int i = 0; i < 26; i++)
		{
			printf(" ");
			for (int j = 0; j < 46; j++)
			{
				printf("%c", superGrid[i][j]);
			}
		}
	}
	//chama a função que modifica a grade e imprime depois
	if (mod == 2)
	{
		superGridModifier(superGrid, grid);
		for (int i = 0; i < 26; i++)
		{
			printf(" ");
			for (int j = 0; j < 46; j++)
			{
				printf("%c", superGrid[i][j]);
			}
		}
	}
	//imprime a grade com números de 1 a 9 nela
	if (mod == 3)
	{
		printf("\n         88    ##   ad888888b, ##   ad888888b, \n       ,d88    ##  d8\"     \"88 ##  d8\"     \"88 \n     888888    ##          a8P ##          a8P \n         88    ##       ,d8P\"  ##       aad8\"  \n         88    ##     a8P\"     ##       \"\"Y8,  \n         88    ##   a8P\'       ##          \"8b \n         88    ##  d8\"         ##  Y8,     a88 \n         88    ##  88888888888 ##   \"Y888888P\' \n ##############################################\n          ,d8  ##  8888888888  ##    ad8888ba, \n        ,d888  ##  88          ##   8P\'    \"Y8 \n      ,d8\" 88  ##  88  ____    ##  d8          \n    ,d8\"   88  ##  88a8PPPP8b, ##  88,dd888bb, \n  ,d8\"     88  ##  PP\"     `8b ##  88P\'    `8b \n  8888888888888##           d8 ##  88       d8 \n           88  ##  Y8a     a8P ##  88a     a8P \n           88  ##   \"Y88888P\"  ##   \"Y88888P\"  \n ##############################################\n  888888888888 ##   ad88888ba  ##   ad88888ba  \n           8P\' ##  d8\"     \"8b ##  d8\"     \"88 \n         d8\"   ##  Y8a     a8P ##  8P       88 \n       ,8P\'    ##    \"Y8aaa8P\" ##  Y8,    ,d88 \n      d8\"      ##   ,d8\"\"\"8b,  ##   \"PPPPPP\"88 \n    ,8P\'       ##  d8\"     \"8b ##           8P \n   d8\"         ##  Y8a     a8P ##  8b,    a8P  \n  8P\'          ##   \"Y88888P\"  ##  `\"Y8888P\'   \n");
	}
	//imprime a grade com as coordenadas de (1,1) até (3,3)
	if (mod == 4)
	{
		printf("\n               ##              ##              \n               ##              ##              \n   /         \\ ##  /      __ \\ ##  /      __ \\ \n  ( /|    /|  )## ( /|     _) )## ( /|    __) )\n   \\ |  /  | / ##  \\ |  / /__/ ##  \\ |  / __)/ \n               ##              ##              \n               ##              ##              \n               ##              ##              \n ##############################################\n               ##              ##              \n               ##              ##              \n   /__       \\ ##  /__    __ \\ ##  /__    __ \\ \n  (  _)   /|  )## (  _)    _) )## (  _)   __) )\n   \\/__ /  | / ##  \\/__ / /__/ ##  \\/__ / __)/ \n               ##              ##              \n               ##              ##              \n               ##              ##              \n ##############################################\n               ##              ##              \n               ##              ##              \n   /__       \\ ##  /__    __ \\ ##  /__    __ \\ \n  ( __)   /|  )## ( __)    _) )## ( __)   __) )\n   \\__) /  | / ##  \\__) / /__/ ##  \\__) / __)/ \n               ##              ##              \n               ##              ##              \n               ##              ##              \n ");
	}
}

int main(int argc, char* argv[])
{
	static int grid[3][3] = { 0 };
	int playCoordinates[2] = { 0 }, playPosition, player;
	int insertionPreference, symbolPreference;
	int win = 0;

	printf("Iniciando Jogo da Velha!\n");
	printf("Como gostaria o tabuleiro? (Alerta, muitas linhas! Pressione enter para continuar)\n");
	system("pause");
	printf("1: As posições vão de 1 a 9\n");
	gridPrinter(grid, 3);
	printf("\n2: As posições são coordenadas to tipo (x,y)\n");
	gridPrinter(grid, 4);
	if (scanf("%i", &insertionPreference) == 1);
	printf("Gostaria de jogar o modo: 1- Singleplyer ou 2- Multiplayer\n");
	if (scanf("%i", &player) == 1);
	gridPrinter(grid, 0);
	printf("Com qual gostaria de jogar? 1- X ou 2- O\n");
	if (scanf("%i", &symbolPreference) == 2);
	if (symbolPreference == 2)
		symbolPreference = -1;
	player = 1;

	while (win == 0)
	{
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
		if (player == 1)
			grid[playCoordinates[0]][playCoordinates[1]] = insertionPreference;
		if (player == 2)
			grid[playCoordinates[0]][playCoordinates[1]] = -insertionPreference;
		player++;
	}
}