#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ansi_escapes.h"

#include "windowsConsoleInteraction.h"
#include <conio.h>

typedef struct Coordinates {
	short i, j;
}coord;

coord clickToCoordinates(COORD click)
{
	coord retValue;
	
	click.X--;
	retValue.i = -1;
	retValue.j = -1;

	for (int count = 0; count < 37; count += 4)
	{
		if (click.Y > count&& click.Y < count + 4)
		{
			retValue.i = count / 4;
			break;
		}
	}
	for (int count = 0; count < 109; count += 9)
	{
		if (click.X > count&& click.X < count + 9)
		{
			retValue.j = count / 9;
			break;
		}
	}
	return retValue;
}

void createDisplayeGrid(char displayGrid[37][100])
{
	for (int i = 0; i < 37; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (j % 9 == 0 || i % 4 == 0)
			{
				if (i % 4 == 0)
					displayGrid[i][j] = ':';

				if (j % 9 == 0)
					displayGrid[i][j] = '|';
			}
			else
				displayGrid[i][j] = ' ';
		}		
	}
}

void modifyDisplayGrid(char displayGrid[37][100], coord coordinates, char symbol)
{
	char horizontalBow[3][8] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', '_'} ,
								 {' ', ' ', ' ', ' ', '_', '_', '/', ' '} ,
								 {' ', ' ', ' ', ' ', '\\', '_', '_', '_'} };

	char horizontalMiddle[3][8] = { {'_', '_', '_', '_', '_', '_', '_', '_'} ,
									{' ', ' ', '|', '_', 'o', '_', '|', ' '} ,
									{'_', '_', '_', '_', '_', '_', '_', '_'} };

	char horizontalStern[3][8] = { {'_', '_', '_', ' ', ' ', ' ', ' ', ' '} ,
								   {' ', ' ', ' ', '|', ' ', ' ', ' ', ' '} ,
								   {'_', '_', '/', ' ', ' ', ' ', ' ', ' '} };

	char verticalBow[3][8] = { {' ', ' ', ' ', '/', '\\', ' ', ' ', ' '} ,
							   {' ', ' ', '/', '_', '_', '\\', ' ', ' '} ,
							   {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} };

	char verticalMiddle[3][8] = { {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} ,
								  {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} ,
								  {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} };

	char verticalStern[3][8] = { {' ', '|', ' ', '_', '_', ' ', '|', ' '} ,
								 {' ', '|', '_', '_', '_', '_', '|', ' '} ,
								 {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} };

	char nope[3][8] = { {' ', ' ', '\\', '_', '_', '/', ' ', ' '} ,
						{' ', '-', '|', '_', '_', '|', '-', ' '} ,
						{' ', ' ', '/', ' ', ' ', '\\', ' ', ' '} };

	char submarine[3][8] = { {' ', ' ', ' ', ' ', '_', ' ', ' ', ' '} ,
							 {' ', '_', '_', '/', 'o', '\\', '_', ' '} ,
							 {'|', '_', '_', '_', '_', '_', '_', '|'} };

	coord start;

	for (int count = 0; count < 9; count++)
	{
		if (coordinates.i == count)
		{
			start.i = (count * 4) + 1;
			break;
		}
	}
	for (int count = 0; count < 11; count++)
	{
		if (coordinates.j == count)
		{
			start.j = (count * 9) + 1;
			break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (symbol == '<')
			{
				displayGrid[start.i + i][start.j + j] = horizontalBow[i][j];
				continue;
			}
			if (symbol == '=')
			{
				displayGrid[start.i + i][start.j + j] = horizontalMiddle[i][j];
				continue;
			}
			if (symbol == '>')
			{
				displayGrid[start.i + i][start.j + j] = horizontalStern[i][j];
				continue;
			}
			if (symbol == '^')
			{
				displayGrid[start.i + i][start.j + j] = verticalBow[i][j];
				continue;
			}
			if (symbol == '|')
			{
				displayGrid[start.i + i][start.j + j] = verticalMiddle[i][j];
				continue;
			}
			if (symbol == '~')
			{
				displayGrid[start.i + i][start.j + j] = verticalStern[i][j];
			}
			if (symbol == ' ')
			{
				displayGrid[start.i + i][start.j + j] = nope[i][j];
				continue;
			}
			if (symbol == 'o')
			{
				displayGrid[start.i + i][start.j + j] = submarine[i][j];
				continue;
			}
		}
	}

}

void printDisplayGrid(char displayGrid[37][100])
{
	for (int i = 0; i < 37; i++)
	{
		moveRight(1);
		for (int j = 0; j < 100; j++)
			printf("%c", displayGrid[i][j]);
		printf("\n");
	}
}

bool isEnd(char grid[9][11], char playerGrid[9][11])
{
	bool isEnd = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 11; j++)
			if (grid[i][j] != playerGrid[i][j])
				isEnd = false;
	}
	return isEnd;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("\tusage: battleship <file>\n");
		return -1;
	}

	FILE* textFile;
	textFile = fopen(argv[1], "r");
	if (textFile == NULL)
	{
		puts("Couldn't open file");
		return -2;
	}

	char displayGrid[37][100];
	char grid[9][11];
	char playGrid[9][11];
	coord play;
	EVENT retEvent;
	COORD mouseCoord;
	char trashcan[10];

	{
		char getGrid[9][25] = { 0 };
		bool pass = true;
		for (int count = 0; count < 9; count++)
			fgets(getGrid[count], 25, textFile);

		for (int count = 0; count < 9; count++)
		{
			if (getGrid[count][24] != '\0' && getGrid[count][24] != '\n')
			{
				pass = false;
				break;
			}
		}

		if (pass == false)
		{
			puts("the file isn't formatted correctly, please try again");
			return -1;
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 1; j < 22; j += 2)
				grid[i][j - (j/2 + 1)] = getGrid[i][j];
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 11; j++)
				playGrid[i][j] = ' ';
		}

	}
	
	{
		int windowSize[2];
		setupConsole();
		moveTo(999, 999);
		getCursorPosition(&windowSize[0], &windowSize[1]);
		moveTo(0, 0);

		while (windowSize[0] < 40)
		{
			puts("Please, expand the console window!");
			moveTo(999, 999);
			getCursorPosition(&windowSize[0], &windowSize[1]);
			moveTo(0, 0);
		}
		clearScreenToBottom();
		restoreConsoleMode();
	}

	createDisplayeGrid(displayGrid);
	printDisplayGrid(displayGrid);
	for (bool playing = true; playing == true;)
	{
		while (true)
		{
			retEvent.event.mouseEvent = 0xc00;
			retEvent = eventMain();
			mouseCoord = retEvent.event.mouseCoord;
			if (retEvent.event.mouseEvent == FROM_LEFT_1ST_BUTTON_PRESSED) 
				break;
		}

		play = clickToCoordinates(mouseCoord);
		if (play.i == -1 || play.j == -1)
			continue;

		modifyDisplayGrid(displayGrid, play, grid[play.i][play.j]);
		clearScreenToTop;
		moveTo(0, 0);
		printDisplayGrid(displayGrid);

		if (isEnd(grid, playGrid))
		{
			puts("Game Over!");
			playing = false;
			fgets(trashcan, 5, stdin);
			break;
		}
	}


	return 0;
}