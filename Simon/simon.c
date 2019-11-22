#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ansi_escapes.h"
#include "windowsMouseInteraction.h"


extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);
extern void getCursorPosition(int* row, int* col);

typedef unsigned char sshort;

typedef enum ColorButtons {
	NO_COLOR = 0,
	GREEN = 1,
	RED,
	YELLOW,
	BLUE
}Color;

void display(int button, int screenSize[2])
{
	setupConsole();

	moveTo(0, 0);

	for (int row = 0; row <= (screenSize[0] / 2) - 2; row++)
	{
		if (button == GREEN)
			setBackgroundColorRGB(0, 150, 0); // bright green
		else
			setBackgroundColorRGB(15, 60, 15); // shadow green
		for (int greenCol = 0; greenCol <= (screenSize[1] / 2) - 1; greenCol++)
			printf(" ");

		if (button == RED)
			setBackgroundColorRGB(150, 30, 40); // bright red
		else
			setBackgroundColorRGB(70, 30, 30); // shadow red
		for (int rednCol = 0; rednCol <= (screenSize[1] / 2) - 1; rednCol++)
			printf(" ");

		printf("\n");

	}

	if (screenSize[0] % 2 != 0)
		printf("\n");

	for (int row = 0; row <= (screenSize[0] / 2) - 2; row++)
	{
		if (button == YELLOW)
			setBackgroundColorRGB(255, 255, 0); // bright yellow
		else
			setBackgroundColorRGB(50, 50, 0); // shadow yellow
		for (int greenCol = 0; greenCol <= (screenSize[1] / 2) - 1; greenCol++)
			printf(" ");


		if (screenSize[1] % 2 != 0)
			printf(" ");

		if (button == BLUE)
			setBackgroundColorRGB(40, 30, 150); // bright blue
		else
			setBackgroundColorRGB(15, 15, 60); // shadow blue
		for (int rednCol = 0; rednCol <= (screenSize[1] / 2) - 1; rednCol++)
			printf(" ");
	}
	restoreConsole();
	printf("\n");
}

void rng(int* sequence, int level)
{
	sequence[level - 1] = 1 + rand() % 4;
}

int main(int argc, char** argv)
{
	int level = 1;
	int windowSize[2];
	sshort sequence[4000];
	sshort mouseCoordinates[2];
	char trashcan[10];

	srand(time(NULL));

	printf("Starting Simon. Do you wish to:\n(P) play now\nor \n(T)see the tutorial?\n");
	fgets(trashcan, 5, stdin);

	if (trashcan[0] == 'T' || trashcan[0] == 't')
	{
		//teach how to play
	}

	if (trashcan[0] == 'P' || trashcan[0] == 'p')
	{
		for (bool replay = true; replay == true;)
		{
			setupConsole();
			moveTo(999, 999);
			getCursorPosition(&windowSize[0], &windowSize[1]);
			clearScreenToTop();
			restoreConsoleMode();
			display(NO_COLOR, windowSize);

			mouseClick(&mouseCoordinates[0], &mouseCoordinates[1]);
			printf("%i %i", mouseCoordinates[0], mouseCoordinates[1]);

			resetColor();
			break;
		}
	}

	return 0;
}