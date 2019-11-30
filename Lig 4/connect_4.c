#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "minimax.h"
#include "ansi_escapes.h"
#include "connect_4.h"

extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);

extern void supergridTied(char supergrid[37][98]);
extern bool minimaxTie(int grid[6][7], int nextplayer);
extern Move minimaxPlay(int grid[6][7], int nextplayer);

// looks for wins
// return a Win variable
Win winVerifyer(int grid[6][7])
{
	Win returnValue;
	returnValue.win = false;
	
	// looks in the rows
	for (int i = 5; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j] == 1 && grid[i][j + 1] == 1 && grid[i][j + 2] == 1 && grid[i][j + 3] == 1)
			{
				returnValue.win = true;
				returnValue.player = 1;
				returnValue.victoryType = 'H';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i][j + 1] == -1 && grid[i][j + 2] == -1 && grid[i][j + 3] == -1)
			{
				returnValue.win = true;
				returnValue.player = 2;
				returnValue.victoryType = 'H';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}
		}
	}

	// looks in the collumns
	for (int j = 0; j < 7; j++)
	{
		for (int i = 5; i > 2; i--)
		{
			if (grid[i][j] == 1 && grid[i - 1][j] == 1 && grid[i - 2][j] == 1 && grid[i - 3][j] == 1)
			{
				returnValue.win = true;
				returnValue.player = 1;
				returnValue.victoryType = 'V';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i - 1][j] == -1 && grid[i - 2][j] == -1 && grid[i - 3][j] == -1)
			{
				returnValue.win = true;
				returnValue.player = 2;
				returnValue.victoryType = 'V';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}
		}

	}

	// looks in the '\' diagonals
	for (int j = 0; j < 4; j++)
	{
		for (int i = 5; i > 2; i--)
		{
			if (grid[i][j] == 1 && grid[i - 1][j + 1] == 1 && grid[i - 2][j + 2] == 1 && grid[i - 3][j + 3] == 1)
			{
				returnValue.win = true;
				returnValue.player = 1;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i - 1][j + 1] == -1 && grid[i - 2][j + 2] == -1 && grid[i - 3][j + 3] == -1)
			{
				returnValue.win = true;
				returnValue.player = 2;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}
		}
	}

	// looks in the '/' diagonals
	for (int j = 6; j > 2; j--)
	{
		for (int i = 5; i > 2; i--)
		{
			if (grid[i][j] == 1 && grid[i - 1][j - 1] == 1 && grid[i - 2][j - 2] == 1 && grid[i - 3][j - 3] == 1)
			{
				returnValue.win = true;
				returnValue.player = 1;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 2;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i - 1][j - 1] == -1 && grid[i - 2][j - 2] == -1 && grid[i - 3][j - 3] == -1)
			{
				returnValue.win = true;
				returnValue.player = -1;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 2;
				returnValue.row = i;
				returnValue.col = j;
			}
		}
	}

	return returnValue;
}

// generates (visually) the supergrid
void supergridGenerator(char supergrid[37][98])
{
	// put the ascii art of an empty board in the supergrid
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

// prints the supergrid in the screen
void supergridPrinter(char supergrid[37][98], int grid[6][7], Move winCoordinates[4])
{
	// prints looking in the grid to put the correct colors
	// also receive win information to see if highlights the win positions
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
					for (int count = 0; count < 4; count++)
					{
						if (winCoordinates[count].col == gridJ && winCoordinates[count].row == gridI)
							setBackgroundColorRGB(50, 50, 50);
					}
					printf("%c", supergrid[i][j]);
					setTextColor(WHITE_TXT);
					setBackgroundColorRGB(20, 20, 20);

				}
				if (grid[gridI][gridJ] == -1)
				{

					setTextColorBright(RED_TXT);
					for (int count = 0; count < 4; count++)
					{
						if (winCoordinates[count].col == gridJ && winCoordinates[count].row == gridI)
							setBackgroundColorRGB(50, 50, 50);
					}
					printf("%c", supergrid[i][j]);
					setTextColor(WHITE_TXT);
					setBackgroundColorRGB(20, 20, 20);

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

// modifyes the supergrid, putting a circle on the modification coordinates
void supergridModifyer(char supergrid[37][98], Move modification)
{
	Move startCoordinate, copy_of_startCoordinate, circleCoordinates;
	startCoordinate.row = 1;
	startCoordinate.col = 1;
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

// gets the row available to play in a certain column
void getTheRow(int grid[6][7], Move* move)
{
	for (int i = 5; i >= 0; i--)
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

int main(int argc, char** argv)
{
	int grid[6][7] = { 0 };
	char supergrid[37][98];

	// main menu loop, the player will be prompet if
	// it wants to exit the game or to main menu
	for (bool mainMenu = true; mainMenu == true;)
	{
		int player;
		bool multiplayer;
		Move playerMove;
		Win winVerifyerReturn;
		Move winCoordinates[4];
		char trashCan[10];	//used to freeze the program instead of getchar

		// verifyes if the windows is big enought to play the game
		// and prompts the player to maximaze the console window
		{
			int windowSize[2];
			setupConsole();
			moveTo(999, 999);
			getCursorPosition(&windowSize[0], &windowSize[1]);
			moveTo(0, 0);

			while (windowSize[0] < 41 || windowSize[1] < 101)
			{
				puts("You'll need to expand the windows to play");
				moveTo(999, 999);
				getCursorPosition(&windowSize[0], &windowSize[1]);
				moveTo(0, 0);
			}
			clearScreenToBottom();
			restoreConsoleMode();
		}

		// sets the background to a more bright black
		setupConsole();
		setBackgroundColorRGB(20, 20, 20);
		restoreConsole();

		printf("Gostaria de jogar o modo: 1- Singleplayer ou 2- Multiplayer\n");
		fgets(trashCan, 5, stdin);
		if (trashCan[0] == '2')
			multiplayer = true;
		else
			multiplayer = false;

		// keep playing loop
		// the player will be prompted if it wants to play again
		// if yes the loop stays running
		// else goes to main menu or exits the game
		for (char keepPlaying = 's'; keepPlaying == 's' || keepPlaying == 'S';)
		{
			supergridGenerator(supergrid); //generates the supergrid
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
					grid[i][j] = 0;
			}
			player = 1;

			// play loop
			for (bool win = false, tie = false; win == false && tie == false;)
			{
				for (int count = 0; count < 4; count++)
				{
					winCoordinates[count].row = -1;
					winCoordinates[count].col = -1;
				}
				if (player == 3) // loops the  player
					player = 1;
				setupConsole();
				setBackgroundColorRGB(20, 20, 20);

				clearScreenToTop();
				moveTo(0, 0);

				supergridPrinter(supergrid, grid, winCoordinates);
				restoreConsoleMode();
				printf("Jogue jogador %i\n", player);
				while (scanf(" %i", &playerMove.col) != 1);
				playerMove.col--;
				if (playerMove.col > 6 || playerMove.col < 0)
				{
					printf("Fora de Alcance!");
					continue;
				}
				getTheRow(grid, &playerMove);
				if (playerMove.row == -1)
				{
					printf("Você não pode jogar aí!\n");
					fgets(trashCan, 5, stdin);
					continue;
				}
				if (player == 1)
					grid[playerMove.row][playerMove.col] = 1;
				if (player == 2)
					grid[playerMove.row][playerMove.col] = -1;
				supergridModifyer(supergrid, playerMove);
				if (multiplayer == false)
				{
					supergridModifyer(supergrid, minimaxPlay(grid, 2));
					player = 0;
				}
				winVerifyerReturn = winVerifyer(grid);
				if (winVerifyerReturn.win == true)
				{
					if (winVerifyerReturn.victoryType == 'H')
					{
						for (int count = 0; count < 4; count++)
						{
							winCoordinates[count].row = winVerifyerReturn.row;
							winCoordinates[count].col = (winVerifyerReturn.col + count);
						}
					}

					if (winVerifyerReturn.victoryType == 'V')
					{
						for (int count = 0; count < 4; count++)
						{
							winCoordinates[count].row = (winVerifyerReturn.row - count);
							winCoordinates[count].col = winVerifyerReturn.col;
						}
					}

					if (winVerifyerReturn.victoryType == 'D' && winVerifyerReturn.victoryTypeVariation == 1)
					{
						for (int count = 0; count < 4; count++)
						{
							winCoordinates[count].row = (winVerifyerReturn.row - count);
							winCoordinates[count].col = (winVerifyerReturn.col + count);
						}
					}

					if (winVerifyerReturn.victoryType == 'D' && winVerifyerReturn.victoryTypeVariation == 2)
					{
						for (int count = 0; count < 4; count++)
						{
							winCoordinates[count].row = (winVerifyerReturn.row - count);
							winCoordinates[count].col = (winVerifyerReturn.col - count);
						}
					}
					clearScreenToTop();
					moveTo(0, 0);
					supergridPrinter(supergrid, grid, winCoordinates);
					printf("Jogador %i venceu!", player);
					win = true;
					continue;
				}
				player++;
				tie = minimaxTie(grid, player);
				if (tie == true);
				{
					if (tie == true)
					{
						clearScreenToTop();
						moveTo(0, 0);
						supergridTied(supergrid);
						supergridPrinter(supergrid, grid, winCoordinates);
						printf("Empate!");
						fgets(trashCan, 5, stdin);
					}
				}
			}

			printf("\nContinuar jogando? s-sim n-não\n");
			if (scanf(" %c", &keepPlaying) == 1)
				continue;
			printf("Voltar ao menu principal? s-sim n-não\n");
			fgets(trashCan, 5, stdin);
			if (trashCan[0] == 'n' || trashCan[1] == 'N')
				mainMenu = false;
		}
	}
}