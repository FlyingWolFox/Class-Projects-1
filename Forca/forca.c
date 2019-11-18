#define _CRT_SECURE_NO_WARNINGS
#include "forca.h"
#include "ansi_escapes.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void letterArrayCreator(char letters[28][3][5])
{
	char a[3][5] = { {'_', '_', '_', '_', ' '},
{'|', '_', '_', '|', ' '},
{'|', ' ', ' ', '|', ' '} };

	char b[3][5] = { {'_', '_', '_', ' ', ' '},
	{'|', '_', '_', ']', ' '},
	{'|', '_', '_', ']', ' '} };

	char c[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', ' ', ' ', ' ', ' '},
	{'|', '_', '_', '_', ' '} };

	char d[3][5] = { {'_', '_', '_', ' ', ' '},
	{'|', ' ', ' ', '\\', ' '},
	{'|', '_', '_', '/', ' '} };

	char e[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', '_', '_', '_', ' '},
	{'|', '_', '_', '_', ' '} };

	char f[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', '_', '_', '_', ' '},
	{'|', ' ', ' ', ' ', ' '} };

	char g[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', ' ', '_', '_', ' '},
	{'|', '_', '_', ']', ' '} };

	char h[3][5] = { {'_', ' ', ' ', '_', ' '},
	{'|', '_', '_', '|', ' '},
	{'|', ' ', ' ', '|', ' '} };

	char i[3][5] = { {' ', ' ', '_', ' ', ' '},
	{' ', ' ', '|', ' ', ' '},
	{' ', ' ', '|', ' ', ' '} };

	char j[3][5] = { {' ', '_', ' ', ' ', ' '},
	 {' ', '|', ' ', ' ', ' '},
	{'_', '|', ' ', ' ', ' '} };

	char k[3][5] = { {'_', ' ', ' ', '_', ' '},
	{'|', '_', '/', ' ', ' '},
	{'|', ' ', '\\', '_', ' '} };

	char l[3][5] = { {'_', ' ', ' ', ' ', ' '},
	{'|', ' ', ' ', ' ', ' '},
	{'|', '_', '_', '_', ' '} };

	char m[3][5] = { {'_', ' ', ' ', '_', ' '},
	{'|', '\\', '/', '|', ' '},
	{'|', ' ', ' ', '|', ' '} };

	char n[3][5] = { {'_', ' ', ' ', '_', ' '},
	{'|', '\\', ' ', '|', ' '},
	{'|', ' ', '\\', '|', ' '} };

	char o[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', ' ', ' ', '|', ' '},
	{'|', '_', '_', '|', ' '} };

	char p[3][5] = { {'_', '_', '_', ' ', ' '},
	{'|', '_', '_', ']', ' '},
	{'|', ' ', ' ', ' ', ' '} };

	char q[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', ' ', ' ', '|', ' '},
	{'|', '_', '\\', '|', ' '} };

	char r[3][5] = { {'_', '_', '_', '_', ' '},
	{'|', '_', '_', '/', ' '},
	{'|', ' ', ' ', '\\', ' '} };

	char s[3][5] = { {'_', '_', '_', '_', ' '},
	{'[', '_', '_', ' ', ' '},
	{'_', '_', '_', ']', ' '} };

	char t[3][5] = { {'_', '_', '_', ' ', ' '},
	{' ', '|', ' ', ' ', ' '},
	{' ', '|', ' ', ' ', ' '} };

	char u[3][5] = { {'_', ' ', ' ', '_', ' '},
	{'|', ' ', ' ', '|', ' '},
	{'|', '_', '_', '|', ' '} };

	char v[3][5] = { {'_', ' ', ' ', '_', ' '},
	{'|', ' ', ' ', '|', ' '},
	{' ', '\\', '/', ' ', ' '} };

	char w[3][5] = { {'_', ' ', '_', ' ', '_'},
	{'|', ' ', '|', ' ', '|'},
	{'|', '_', '|', '_', '|'} };

	char x[3][5] = { {'_', ' ', ' ', '_', ' '},
	{' ', '\\', '/', ' ', ' '},
	{'_', '/', '\\', '_', ' '} };

	char y[3][5] = { {'_', ' ', ' ', ' ', '_'},
	{' ', '\\', '_', '/', ' '},
	{' ', ' ', '|', ' ', ' '} };

	char z[3][5] = { {'_', '_', '_', ' ', ' '},
	{' ', ' ', '/', ' ', ' '},
	{' ', '/', '_', '_', ' '} };

	char _[3][5] = { {' ', ' ', ' ', ' ', ' '},
					 {' ', ' ', ' ', ' ', ' '},
					 {'_', '_', '_', '_', '_'} };

	char hyphen[3][5] = { {' ', ' ', ' ', ' ', ' '},
					 	  {' ', '_', '_', ' ', ' '},
					  	  {' ', ' ', ' ', ' ', ' '} };

	memcpy(letters['q' - 'a'], q, sizeof(q));
	memcpy(letters['w' - 'a'], w, sizeof(w));
	memcpy(letters['e' - 'a'], e, sizeof(e));
	memcpy(letters['r' - 'a'], r, sizeof(r));
	memcpy(letters['t' - 'a'], t, sizeof(t));
	memcpy(letters['y' - 'a'], y, sizeof(y));
	memcpy(letters['u' - 'a'], u, sizeof(u));
	memcpy(letters['i' - 'a'], i, sizeof(i));
	memcpy(letters['o' - 'a'], o, sizeof(o));
	memcpy(letters['p' - 'a'], p, sizeof(p));
	memcpy(letters['a' - 'a'], a, sizeof(a));
	memcpy(letters['s' - 'a'], s, sizeof(s));
	memcpy(letters['d' - 'a'], d, sizeof(d));
	memcpy(letters['f' - 'a'], f, sizeof(f));
	memcpy(letters['g' - 'a'], g, sizeof(g));
	memcpy(letters['h' - 'a'], h, sizeof(h));
	memcpy(letters['j' - 'a'], j, sizeof(j));
	memcpy(letters['k' - 'a'], k, sizeof(k));
	memcpy(letters['l' - 'a'], l, sizeof(l));
	memcpy(letters['z' - 'a'], z, sizeof(z));
	memcpy(letters['x' - 'a'], x, sizeof(x));
	memcpy(letters['c' - 'a'], c, sizeof(c));
	memcpy(letters['v' - 'a'], v, sizeof(v));
	memcpy(letters['b' - 'a'], b, sizeof(b));
	memcpy(letters['n' - 'a'], n, sizeof(n));
	memcpy(letters['m' - 'a'], m, sizeof(m));
	memcpy(letters[('z' - 'a') + 1], _, sizeof(_));
	memcpy(letters[('z' - 'a') + 2], hyphen, sizeof(hyphen));

}

bool displayModifyer(Word word, Word* display, char letter)
{
	bool foundLetter = false;
	for (int count = 0; count < (display->numberOfLetters); count++)
	{
		if (word.word[count] == letter)
		{
			display->word[count] = letter;
			foundLetter = true;
		}
	}
	return foundLetter;
}

int endVerifyer(char hangMan[8][11], Word display)
{
	int underlineCount = 0;
	if (hangMan[5][10] == '\\')
		return 2;
	for (int count = 0; count <= display.numberOfLetters; count++)
	{
		if (display.word[count] == '_')
			underlineCount++;
	}
	if (underlineCount == 0)
		return 1;
	return 0;
}

void hangManCopyer(char hangMan[8][11], Body partToUpdate)
{
	/*
			 _______
			|/      |
			|      (_)
			|      \|/
			|       |
			|      / \
			|
		jgs_|___
	*/

	if (partToUpdate == HANG)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 11; j++)
				hangMan[i][j] = ' ';
		}

		hangMan[7][0] = '_';
		hangMan[7][2] = '_';
		hangMan[7][3] = '_';

		for (int count = 7; count > 0; count--)
			hangMan[count][1] = '|';

		hangMan[1][2] = '/';

		for (int count = 2; count < 9; count++)
			hangMan[0][count] = '_';

		hangMan[1][9] = '|';
	}

	if (partToUpdate == HEAD)
	{
		hangMan[2][8] = '(';
		hangMan[2][9] = '_';
		hangMan[2][10] = ')';
	}

	if (partToUpdate == UPPER_BODY)
		hangMan[3][9] = '|';

	if (partToUpdate == LEFT_ARM)
		hangMan[3][8] = '\\';

	if (partToUpdate == RIGHT_ARM)
		hangMan[3][10] = '/';

	if (partToUpdate == LOWER_BODY)
		hangMan[4][9] = '|';

	if (partToUpdate == LEFT_LEG)
		hangMan[5][8] = '/';

	if (partToUpdate == RIGHT_LEG)
		hangMan[5][10] = '\\';

}

void letterCopier(char letterGrid[3][5], char letter, bool inicialization)
{
	static char letters[28][3][5];
	if (inicialization == true)
	{
		letterArrayCreator(letters);
	}

	if (letter != '_')
		memcpy(letterGrid, letters[letter - 'a'], sizeof(letters[letter - 'a']));
	if (letter == '_')
		memcpy(letterGrid, letters[26], sizeof(letters[26]));
	if (letter == '-')
		memcpy(letterGrid, letters[27], sizeof(letters[27]));
}

void screenPrinter(char hangMan[8][11], char* tip, Word word, char* alreadyChoosenLetters)
{
	char letterGrid[3][5];

	clearScreenToTop();
	moveTo(0, 0);
	for (int count = 0; count < 11; count++)
	{
		printf("%c", hangMan[0][count]);
	}
	moveRight(5);

	printf("%s", word.tip);
	moveTo(2, 0);

	for (int i = 1; i < 8; i++)
	{
		for (int j = 0; j < 11; j++)
			printf("%c", hangMan[i][j]);

		if (i < 7)
			printf("\n");
	}

	moveRight(5);
	if (word.numberOfLetters < 15)
	{

		for (int count = 0; count < word.numberOfLetters; count++)
		{
			letterCopier(letterGrid, word.word[count], false);

			for (int i = 2; i > -1; i--)
			{
				for (int j = 0; j < 5; j++)
					printf("%c", letterGrid[i][j]);
				moveLeft(5);
				moveUp(1);
			}
			moveRight(7);
			moveDown(3);
		}
	}

	else
	{
		for (int count = 0; count < word.numberOfLetters; count++)
		{
			letterCopier(letterGrid, word.word[count], false);
			printf("%c", word.word[count]);
			moveRight(2);
		}
	}

	moveUp(7);
	int alreadyChoosenLettersCounter = 0;
	for (int count1 = 0; count1 < 7; count1++)
	{		
		for (int count2 = 0; count2 < 6; count2++)
		{
			if (alreadyChoosenLetters[alreadyChoosenLettersCounter] == '\0' || alreadyChoosenLetters[alreadyChoosenLettersCounter] == ' ')
			{
				printf("%c", alreadyChoosenLetters[alreadyChoosenLettersCounter]);
				break;
			}
			else
				printf("%c", alreadyChoosenLetters[alreadyChoosenLettersCounter] - 32);
			alreadyChoosenLettersCounter++;
		}

		moveDown(1);
		moveLeft(6);
	}
	moveDown(1);
}

int main(int argc, char** argv)
{
	char letterGrid[3][5];
	char hangMan[8][11];
	char trashcan[10];
	char alreadyChosenLetters[27];
	int alreadyChosenLettersCounter = 0;
	int hangManState = 0;
	FILE* textFile;
	Word word;
	Word display;

	textFile = fopen(argv[1], "r");
	if (textFile == NULL)
	{
		printf("Text file not found, make sure it's named \"word.txt\" (without que quotes)\n");
		fgets(trashcan, 5, stdin);
		return 1;
	}

	for (int count = 0; count < 27; count++)
		alreadyChosenLetters[count] = ' ';

	alreadyChosenLetters[0] = '\0';

	if (fgets(word.word, 30, textFile) == NULL)
	{
		printf("The file is empty! Please insert an word\n");
		fgets(trashcan, 5, stdin);
		return 2;
	}

	if (fgets(word.tip, 40, textFile) == NULL)
		word.tip[0] = '\0';


	word.numberOfLetters = (strlen(word.word) - 1);

	letterCopier(letterGrid, 'a', true);
	hangManCopyer(hangMan, HANG);

	display = word;
	for (int count = 0; count < word.numberOfLetters; count++)
		display.word[count] = '_';
	for (int count = 0; count < word.numberOfLetters; count++)
	{
		if (word.word[count] == '-')
			display.word[count] = '-';
	}

	for (bool end = false; end == false;)
	{
		screenPrinter(hangMan, display.tip, display, alreadyChosenLetters);
		puts("\n\nChoose a letter:");
		fgets(trashcan, 5, stdin);
		trashcan[1] = '\0';
		if (trashcan[0] >= 'A' && trashcan[0] <= 'Z')
			trashcan[0] += 32;
		if (!((trashcan[0] >= 'A' && trashcan[0] <= 'Z') || (trashcan[0] >= 'a' && trashcan[0] <= 'z')))
			continue;
		if (strstr(alreadyChosenLetters, trashcan) != NULL)
			continue;
		if (displayModifyer(word, &display, trashcan[0]) == false)
			hangManState++;
		hangManCopyer(hangMan, hangManState);
		trashcan[1] = '\0';
		if ((trashcan[0] >= 'a' && trashcan[0] <= 'z') && (strstr(alreadyChosenLetters, trashcan) == NULL))
		{
			alreadyChosenLetters[alreadyChosenLettersCounter] = trashcan[0];
			alreadyChosenLettersCounter++;
			alreadyChosenLetters[alreadyChosenLettersCounter] = '\0';
		}

		if (endVerifyer(hangMan, display) == 1)
		{
			screenPrinter(hangMan, display.tip, display, alreadyChosenLetters);
			printf("\nYou win!\n");
			fgets(trashcan, 5, stdin);
			end = true;
		}
		if (endVerifyer(hangMan, display) == 2)
		{
			screenPrinter(hangMan, word.tip, word, alreadyChosenLetters);
			printf("\nYou Lose!\n");
			fgets(trashcan, 5, stdin);
			end = true;
		}
	}

	puts("Thank You for playing!");

	puts("Stickman art by Joan G. Stark (available at https://www.asciiart.eu/miscellaneous/noose)");
	puts("Ascii art font by Patrick Gillespie (twiiter @patorjk) and his Text to ASCII Art Generator (http://patorjk.com/software/taag)");
	printf("\n");
	puts("This project is made possible by Notepad++ and Visual Studio Community 2019, shoutouts");
	printf("\n");
	puts("Made by Lucas Isaac (@LIPSilva5)");
	fgets(trashcan, 5, stdin);
}