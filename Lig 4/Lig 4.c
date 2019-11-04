#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "ai.h"
#include "ansi_escapes.h"
#include "Lig 4.h"


extern void setupConsole(void);
extern void restoreConsole(void);

Win winVerifyer(int grid[6][7])
{

}

void supergridGenerator(char supergrid[37][98])
{
	for (int i = 0; i < 37; i++)
	{
		for (int j = 0; j < 97; j++)
		{
			if (j != 0 && j != 13 && j != 14 && j != 27 && j != 28 && j != 41 && j != 42 && j != 55 && j != 56 && j != 69 && j != 70 && j != 83 && j != 84 && j != 97)
				supergrid[i][j] = ' ';
		}
		supergrid[i][0] = '|';
		supergrid[i][13] = '|';
		supergrid[i][14] = '|';
		supergrid[i][27] = '|';
		supergrid[i][28] = '|';
		supergrid[i][41] = '|';
		supergrid[i][42] = '|';
		supergrid[i][55] = '|';
		supergrid[i][56] = '|';
		supergrid[i][69] = '|';
		supergrid[i][70] = '|';
		supergrid[i][83] = '|';
		supergrid[i][84] = '|';
		supergrid[i][97] = '|';
		if (i == 0 || i == 6 || i == 12 || i == 18 || i == 24 || i == 30 || i == 36)
		{
			for (int j = 0; j < 98; j++)
			{
				if (supergrid[i][j] != '|')
					supergrid[i][j] = ':';
			}
		}
	}
}

void supergridPrinter(char supergrid[37][98], int grid[6][7])
{
	for (int i = 0, gridI = 0; i < 37; i++)
	{
		printf(" ");
		if (i > 5)
			gridI = 1;
		if (i > 11)
			gridI = 2;
		if (i > 17)
			gridI = 3;
		if (i > 23)
			gridI = 4;
		if (i > 29)
			gridI = 5;

		for (int j = 0, gridJ = 0; j < 98; j++)
		{
			if (j > 12)
				gridJ = 1;
			if (j > 26)
				gridJ = 2;
			if (j > 40)
				gridJ = 3;
			if (j > 54)
				gridJ = 4;
			if (j > 68)
				gridJ = 5;
			if (j > 82)
				gridJ = 6;

			if (supergrid[i][j] != ':' && supergrid[i][j] != '|')
			{
				if (grid[gridI][gridJ] == 1)
				{
					setTextColorBright(BLUE_TXT);
					printf("%c", supergrid[i][j]);
					setTextColor(WHITE_TXT);
				}
				if (grid[gridI][gridJ] == -1)
				{
					setTextColorBright(RED_TXT);
					printf("%c", supergrid[i][j]);
					setTextColor(WHITE_TXT);
				}
				if (grid[gridI][gridJ] == 0)
					printf("%c", supergrid[i][j]);
			}
			else
				printf("%c", supergrid[i][j]);
		}
		printf("\n");
	}
}

void supergridModifyer(char supergrid[37][98], Move modification)
{
	Move startCoordinate, copy_of_startCoordinate, circleCoordinates;
	char circle[5][12] = { { ' ', ' ', ' ', '.', '-', '\"', '\"', '-', '.', ' ', ' ', ' ' },
						{ ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', '\\', ' ', ' ' },
						{ ' ', ';', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', ' ' },
						{ ' ', ' ', '\\', ' ', ' ', ' ', ' ', ' ', ' ', '/', ' ' , ' '},
						{ ' ', ' ', ' ', '\'', '-', '.', '.', '-', '\'', ' ', ' ', ' ' } };
		
	if (modification.row == 0)
		startCoordinate.row = 1;
	if (modification.row == 1)
		startCoordinate.row = 7;
	if (modification.row == 2)
		startCoordinate.row = 13;
	if (modification.row == 3)
		startCoordinate.row = 19;
	if (modification.row == 4)
		startCoordinate.row = 25;
	if (modification.row == 5)
		startCoordinate.row = 31;

	if (modification.col == 0)
		startCoordinate.col = 1;
	if (modification.col == 1)
		startCoordinate.col = 15;
	if (modification.col == 2)
		startCoordinate.col = 29;
	if (modification.col == 3)
		startCoordinate.col = 43;
	if (modification.col == 4)
		startCoordinate.col = 57;
	if (modification.col == 5)
		startCoordinate.col = 71;
	if (modification.col == 6)
		startCoordinate.col = 85;
	copy_of_startCoordinate.col = startCoordinate.col;
	copy_of_startCoordinate.row = startCoordinate.row;
	for (startCoordinate.row = copy_of_startCoordinate.row, circleCoordinates.row = 0; startCoordinate.row < (copy_of_startCoordinate.row + 5); startCoordinate.row++, circleCoordinates.row++)
	{
		for (startCoordinate.col = copy_of_startCoordinate.col, circleCoordinates.col = 0; startCoordinate.col < (copy_of_startCoordinate.col + 12); startCoordinate.col++, circleCoordinates.col++)
		{
			supergrid[startCoordinate.row][startCoordinate.col] = circle[circleCoordinates.row][circleCoordinates.col];
		}
	}

}

void getTheRow(int grid[6][7], Move *move)
{
	for (int i = 6; i >= 0; i--)
	{
		if (grid[i][move->col] == 0)
		{
			move->row = i;
			break;
		}
		if (i == 0)
		{
			move->row = -1;
		}
	}
}

int main(int argc, char* argv)
{
	int grid[6][7] = { 0 };
	char supergrid[37][98];

	supergridGenerator(supergrid);
	printf("\n");

	
	for (int mainMenu = 0; mainMenu == 0;)
	{
		int player;
		char playerNumber[3];
		Move playerMove;
		char playerMovement[3];
		printf("Gostaria de jogar o modo: 1- Singleplyer ou 2- Multiplayer\n");
		if (scanf("%i", &player) == 1);

		for (char keepPlaying = 's'; keepPlaying == 's' || keepPlaying == 'S';)
		{
			player = 1;
			for (int win = 0, tie = 0; win == 0 && tie == 0;)
			{
				if (player == 3)
					player = 1; 
				setupConsole();
				supergridPrinter(supergrid, grid);
				restoreConsole();
				printf("Jogue jogador %i\n", player);
				if(scanf(" %i", &playerMove.col) == 1);
				playerMove.col--;
				getTheRow(grid, &playerMove);
				if (playerMove.row == -1)
				{
					printf("Você não pode jogar aí!\n");
					getchar();
					getchar();
					continue;
				}
				if (player == 1)
					grid[playerMove.row][playerMove.col] = 1;
				if (player == 2)
					grid[playerMove.row][playerMove.col] = -1;
				supergridModifyer(supergrid, playerMove);
				player++;
			}

			printf("\nContinuar jogando? s-sim n-não\n");
			if (scanf(" %c", &keepPlaying) == 1);
		}
	}


	setBackgroundColor(MAGENTA_BKG);
	setTextColorBright(RED_TXT);
	puts("Hello, World\n");
	setTextColorBright(BLUE_TXT);
	puts("Hello, World\n");
	restoreConsole();
	
}