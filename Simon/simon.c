#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ansi_escapes.h"

extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);
extern void getCursorPosition(int* row, int* col);

typedef unsigned char sshort;

typedef enum ColorButtons {
	GREEN = 1,
	RED,
	YELLOW,
	BLUE
}Color;

void display(int button, bool zero, int screenSize[2])
{
	setupConsole();
	if (zero == true)
	{
		moveTo(0, 0);
		
		for (int row = 0; row <= screenSize[0]/2 ; row++)
		{
			setBackgroundColorRGB(30, 50, 40); // shadow green
			for (int greenCol = 0; greenCol <= (screenSize[1] / 2) - 1; greenCol++)
				printf(" ");

			if (screenSize[1] % 2 != 0)
				printf(" ");

			setBackgroundColorRGB(50, 30, 40); // shadow red
			for (int rednCol = 0; rednCol <= (screenSize[1] / 2) - 1; rednCol++)
				printf(" ");

			printf("\n");
		}

		if (screenSize[0] % 2 != 0)
			printf("\n");

		for (int row = 0; row <= screenSize[0]/2; row++)
		{
			setBackgroundColorRGB(50, 50, 0); // shadow yellow
			for (int greenCol = 0; greenCol <= (screenSize[1] / 2) - 1; greenCol++)
				printf(" ");

			if (screenSize[1] % 2 != 0)
				printf(" ");

			setBackgroundColorRGB(40, 30, 50); // shadow blue
			for (int rednCol = 0; rednCol <= (screenSize[1] / 2) - 1; rednCol++)
				printf(" ");

			printf("\n");
		}

	}


	restoreConsoleMode();
}

void rng(int* sequence, int level)
{
	unsigned int sequenceSize = level;
	bool repetion;
	sequence[sequenceSize - 2] = 0;
	for (int count1 = 0; count1 < sequence[sequenceSize - 1]; count1++)
	{
		sequence[count1] = 1 + rand() % 4;
		for (int count2 = 0; count2 < count1; count2++)
		{
			if (sequence[count2] == sequence[count1])
				repetion = true;
			while (repetion == 1)
			{
				sequence[count1] = 1 + rand() % 9;
				if (sequence[count2] != sequence[count1])
					repetion = false;
			}
		}
	}
}

int main(int argc, char** argv)
{
	int level = 2;
	int windowSize[2];
	sshort sequence[4000];
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
			display(1, true, windowSize);
			resetColor();
			break;
		}
	}

	return 0;
}