#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "ansi_escapes.h"

// handles mouse interaction
#include "windowsConsoleInteraction.h"
#include <conio.h>

// coordinate system
typedef struct Coordinates {
	short i, j;
}coord;

// holds the shot info
typedef struct ShotInfo {
	bool fired;
	coord position;
}shot;


short mapISize, mapJSize, displayISize, displayJSize;
char *displayGrid, *playerGrid, *grid;


// converts the simple map received by file
// and converts it to internal symbol for each ship
// so identify each ship using other character for display drawning
void convertMap(char grid)
{

}

// converts the mouse click to board coordinates
coord clickToCoordinates(COORD click)
{
	coord retValue;
	
	click.X--;
	retValue.i = -1;
	retValue.j = -1;

	for (int count = 0; count < 40; count += 4)
	{
		if (click.Y > count&& click.Y < count + 4)
		{
			retValue.i = count / 4;
			break;
		}
	}
	for (int count = 0; count < 135; count += 9)
	{
		if (click.X > count&& click.X < count + 9)
		{
			retValue.j = count / 9;
			break;
		}
	}
	return retValue;
}

// creates the display board
// putting the character to create an empty board
void createDisplayeGrid(void)
{
	for (int i = 0; i < mapISize; i++)
	{
		for (int j = 0; j < mapJSize; j++)
		{
			if (j % 9 == 0 || i % 4 == 0)
			{
				if (i % 4 == 0)
					displayGrid[i * mapJSize + j] = ':';

				if (j % 9 == 0)
					displayGrid[i * mapJSize + j] = '|';
			}
			else
				displayGrid[i * mapJSize + j] = ' ';
		}		
	}
}

// modifyes the display grid putting
// a ship part, submarine or miss in the squares
void modifyDisplayGrid(coord coordinates, char symbol)
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

	for (int count = 0; count < mapISize; count++)
	{
		if (coordinates.i == count)
		{
			start.i = (count * 4) + 1;
			break;
		}
	}
	for (int count = 0; count < mapJSize; count++)
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
				displayGrid[(start.i + i) * mapJSize + start.j + j] = horizontalBow[i][j];
				continue;
			}
			if (symbol == '=')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = horizontalMiddle[i][j];
				continue;
			}
			if (symbol == '>')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = horizontalStern[i][j];
				continue;
			}
			if (symbol == '^')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = verticalBow[i][j];
				continue;
			}
			if (symbol == '|')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = verticalMiddle[i][j];
				continue;
			}
			if (symbol == '~')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = verticalStern[i][j];
			}
			if (symbol == ' ')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = nope[i][j];
				continue;
			}
			if (symbol == 'o')
			{
				displayGrid[(start.i + i) * mapJSize + start.j + j] = submarine[i][j];
				continue;
			}
		}
	}

}

// prints the display
void printDisplayGrid(void)
{
	for (int i = 0; i < displayISize; i++)
	{
		moveRight(1);
		for (int j = 0; j < displayJSize; j++)
			printf("%c", displayGrid[i * mapJSize + j]);
		printf("\n");
	}
}

// sees if the game ended
// if yes, is because all ships have been found
bool isEnd(void)
{
	bool isEnd = true;
	for (int i = 0; i < mapISize; i++)
	{
		for (int j = 0; j < mapJSize; j++)
			if (grid[i * mapJSize + j] != playerGrid[i * mapJSize + j])
				isEnd = false;
	}
	return isEnd;
}

// prints the thanks
void thanks(void)
{
	puts("Thanks for playing!");
	puts("");
	puts("Shoutouts for the people on Stack Overflow!");
	puts("This project was made using Visual Studio Comuity 2019, Excel and Notepad++");
	puts("");
}

// default: battleship.exe "C:\textFile" 1
int main(int argc, char** argv)
{
	// if there's no argument, shows the usage
	if (argc < 3)
	{
		printf("\tusage: battleship <file> <map mode>\n");
		return -1;
	}

	// try to open the file
	FILE* textFile;
	textFile = fopen(argv[1], "r");
	if (textFile == NULL)
	{
		puts("Couldn't open file");
		return -2;
	}

	if (argv[2][0] != '0' && argv[2][0] != '1')
	{
		printf("\tinvalid map mode");
		return -3;
	}

	// sets map mode
	int mapMode;
	mapMode = argv[2][0] - '0';

	char trashcan[10]; // used to get inputs or freeze execution
	
	// verifies the windows size
	// if it's too small it'll prompt to maximaze it
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


	// ask the player if it wants the harder ruleset
	bool hardRule = false;
	puts("Hard or easy ruleset? (Hard/easy)");
	fgets(trashcan, 10, stdin);

	clearScreenToTop();
	moveTo(0, 0);

	if (trashcan[0] == 'H' || trashcan[0] == 'h')
		hardRule = true;

	shot attack[3]; // cointains the three player shots

	if (mapMode == 0)
	{
		mapISize = 15;
		mapJSize = 15;
		displayISize = 61;
		displayJSize = 136;
	}

	if (mapMode == 1)
	{
		mapISize = 10;
		mapJSize = 15;
		displayISize = 41;
		displayJSize = 136;
	}
	
	displayGrid = malloc(sizeof(char) * displayISize * displayJSize);
	grid = malloc(sizeof(char) * mapISize * mapJSize); // grid with the complete board
	playerGrid = malloc(sizeof(char) * mapISize * mapJSize); // the grid that the player sees
	EVENT retEvent; // console window events
	COORD mouseCoord; // mouse click coordinates		

	// looks if the file is valid and
	// formatted correctly, and 
	// gets the map from the file
	{
		char* getGrid = malloc(mapISize * (mapJSize * 2 + 3));
		bool pass = true;
		for (int count = 0; count < mapISize * mapJSize; count++)
			getGrid[count] = fgetc(textFile);

		for (int count = 0; count < mapISize; count++)
		{
			if (getGrid[count * 32 + 32] != '\0' && getGrid[count * 32 + 32] != '\n')
			{
				pass = false;
				break;
			}

		}

		if (pass == false)
		{
			puts("the file isn't formatted correctly, please try again");
			fgets(trashcan, 10, stdin);
			return 1;
		}

		for (int i = 0; i < mapISize; i++)
		{
			for (int j = 1; j < mapJSize; j += 2)
				grid[(i * mapJSize) + (j - (j / 2 + 1))] = getGrid[i * mapJSize + j];
		}

		for (int count = 0; count < mapISize * mapJSize; count++)
			playerGrid[count] = ' ';
	}

	createDisplayeGrid();
	printDisplayGrid();

	// play loop
	for (bool playing = true; playing == true;)
	{
		attack[0].fired = false;
		attack[1].fired = false;
		attack[2].fired = false;

		for (int count = 0; attack[2].fired == false; count++)
		{
			if (mapMode == 0)
			{
				// gets the player move coordinates and converts to int
				puts("What cordinates to attack? (Type the X coordinate and enter, then type the Y coordinate)");
				fgets(trashcan, 10, stdin);
				attack[count].position.i = (strtoimax(trashcan, NULL, 10)) - 1;

				fgets(trashcan, 10, stdin);
				attack[count].position.j = (strtoimax(trashcan, NULL, 10)) - 1;

				if ((attack[count].position.i == UINTMAX_MAX && errno == ERANGE) || (attack[count].position.j == UINTMAX_MAX && errno == ERANGE))
				{
					puts("Invalid input. Just numbers are allowed");
					fgets(trashcan, 10, stdin);
					count--;
					continue;
				}

				if (attack[count].position.i > 15 || attack[count].position.i < 1 || attack[count].position.j > 15 || attack[count].position.j < 1)
				{
					puts("Out of the range!");
					fgets(trashcan, 10, stdin);
					count--;
					continue;
				}

				attack[count].position.i--;
				attack[count].position.j--;
			}

			if (mapMode == 1)
			{
				// gets the mouse click coordinates
				while (true)
				{
					retEvent.event.mouseEvent = 0xc00;
					retEvent = eventMain();
					mouseCoord = retEvent.event.mouseCoord;
					if (retEvent.event.mouseEvent == FROM_LEFT_1ST_BUTTON_PRESSED)
						break;
				}

				// if the mouse click coordinates weren't captured
				// (for some reason) it'll loop to get it again
				attack[count].position = clickToCoordinates(mouseCoord);
				if (attack[count].position.i == -1 || attack[count].position.j == -1)
					continue;
			}			

			attack[count].fired = true;
			printf("Shoot %i! ", count + 1);
		}

		for (int count = 0; count < 3; count++)
		{
			// modifies the grid and prints it
			modifyDisplayGrid(attack[count].position, grid[(attack[count].position.i * mapJSize) + attack[count].position.j]);
			playerGrid[attack[count].position.i * mapJSize + attack[count].position.j] = grid[(attack[count].position.i * mapJSize) + attack[count].position.j];
			clearScreenToTop();
			moveTo(0, 0);
			attack[count].fired = false;
		}
		printDisplayGrid();

		// verifies if the game ended
		if (isEnd())
		{
			puts("Game Over!");
			playing = false;
			break;
		}
	}
	
	// prints the thanks
	thanks();
	puts("---Press any key to exit---");
	fgets(trashcan, 5, stdin);
	return 0;
}