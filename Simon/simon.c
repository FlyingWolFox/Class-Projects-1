#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ansi_escapes.h"

extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);
extern void getCursorPosition(int* row, int* col);

typedef enum ColorButtons {
	GREEN = 1,
	RED,
	YELLOW,
	BLUE
}Color;

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
	int sequence[4000];
	char trashcan[10];

	srand(time(NULL));

	printf("Starting Simon. Do you wish to:\n(P) play now\nor \n (T)see the tutorial?\n");
	fgets(trashcan, 5, stdin);

	if (trashcan[0] == 'T')
	{
		//teach how to play
	}

	if (trashcan[0] == 'P')
	{
		for (bool replay = true; replay == true;)
		{
			clearScreenToBottom();
			getCursorPosition(&windowSize[0], &windowSize[1]);
			clearScreenToTop();
		}
	}
}