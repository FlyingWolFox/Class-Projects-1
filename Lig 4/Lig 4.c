#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "ai.h"
#include "ansi_escapes.h"
#include "lig 4.h"

#ifdef __linux__
#define linux
#include <sys/ioctl.h>
#endif //define to just compile linux code

#ifdef _WIN32
#define windows
#include <windows.h>
#include <wincon.h>
#include <consoleapi2.h>

BOOL WINAPI SetConsoleWindowInfo(
	_In_       HANDLE     hConsoleOutput,
	_In_       BOOL       bAbsolute,
	_In_ const SMALL_RECT* lpConsoleWindow
);
#endif //define to just compile windows code

#ifdef __APPLE__ && __MACH__
#define mac
#include <sys/ioctl.h>
#endif // __APPLE__ && __MACH__

extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);


Win winVerifyer(int grid[6][7])
{
	Win returnValue;
	returnValue.win = false;
	for (int i = 5; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j] == 1 && grid[i][j + 1] == 1 && grid[i][j + 2] == 1 && grid[i][j + 3] == 1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'H';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i][j + 1] == -1 && grid[i][j + 2] == -1 && grid[i][j + 3] == -1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'H';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}
		}
	}

	for (int j = 0; j < 7; j++)
	{
		for (int i = 5; i > 2; i--)
		{
			if (grid[i][j] == 1 && grid[i - 1][j] == 1 && grid[i - 2][j] == 1 && grid[i - 3][j] == 1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'V';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i - 1][j] == -1 && grid[i - 2][j] == -1 && grid[i - 3][j] == -1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'V';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}
		}

	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 5; i > 2; i--)
		{
			if (grid[i][j] == 1 && grid[i - 1][j + 1] == 1 && grid[i - 2][j + 2] == 1 && grid[i - 3][j + 3] == 1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i - 1][j + 1] == -1 && grid[i - 2][j + 2] == -1 && grid[i - 3][j + 3] == -1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 1;
				returnValue.row = i;
				returnValue.col = j;
			}
		}
	}

	for (int j = 6; j > 2; j--)
	{
		for (int i = 5; i > 2; i--)
		{
			if (grid[i][j] == 1 && grid[i - 1][j - 1] == 1 && grid[i - 2][j - 2] == 1 && grid[i - 3][j - 3] == 1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 2;
				returnValue.row = i;
				returnValue.col = j;
			}

			if (grid[i][j] == -1 && grid[i - 1][j - 1] == -1 && grid[i - 2][j - 2] == -1 && grid[i - 3][j - 3] == -1)
			{
				returnValue.win = true;
				returnValue.victoryType = 'D';
				returnValue.victoryTypeVariation = 2;
				returnValue.row = i;
				returnValue.col = j;
			}
		}
	}

	return returnValue;
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

void supergridPrinter(char supergrid[37][98], int grid[6][7], Move winCoordinates[4])
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


	for (bool mainMenu = true; mainMenu == true;)
	{
		int player;
		char playerNumber[3];
		Move playerMove;
		char playerMovement[3];
		Win winVerifyerReturn;
		Move winCoordinates[4];
		bool isMaximazed = false;
		char choice[10];

		//used to freeze the program instead of getchar
		char trashCan[10];

		setupConsole();
		setBackgroundColorRGB(20, 20, 20);
		printf("Você vai precisar maximizar a janela do console para poder jogar\n");

		#ifdef windows
		while (0) {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns, rows;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

			printf(" %i %i", rows, columns);
			if (columns == 0 && rows == 0)
			{
				printf("A janela não está no tamanha adequado!\n");
				printf("Aparentemente sua resolução de tela é pequena, rodando no modo legacy");
			}
			getchar();
		}
		#endif

		printf("Gostaria de testar pra ver se está funcionando? s- sim n- não\n");
		restoreConsoleMode();
		fgets(trashCan, 5, stdin);
		if (trashCan[0] == 's' || trashCan[0] == 'S')
		{
			supergridGenerator(supergrid);
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
					grid[i][j] = 0;
			}
			moveTo(0, 0);
			clearScreenToBottom();
			moveTo(0, 0);
			supergridPrinter(supergrid, grid, winCoordinates);
			printf("\n\n\n\n");
			supergridPrinter(supergrid, grid, winCoordinates);
			restoreConsoleMode();
			printf("\nEsses dois tabuleiros foram impressos iguais? s- sim n- não\n");
			if (getchar() == 's')
			{
				printf("Confirmado, executando modo expandido!\n");
				isMaximazed = true;
			}
			printf("Bem, aparentemente não. Caso você errou o teste você pode reiniciar o programa\n");

		}
		printf("Gostaria de jogar o modo: 1- Singleplyer ou 2- Multiplayer\n");
		if (scanf("%i", &player) == 1);

		for (char keepPlaying = 's'; keepPlaying == 's' || keepPlaying == 'S';)
		{
			supergridGenerator(supergrid);
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
					grid[i][j] = 0;
			}
			player = 1;
			for (bool win = false, tie = false; win == false && tie == false;)
			{
				for (int count = 0; count < 4; count++)
				{
					winCoordinates[count].row = -1;
					winCoordinates[count].col = -1;
				}
				if (player == 3)
					player = 1;
				setupConsole();
				setBackgroundColorRGB(20, 20, 20);

				if (isMaximazed == true)
				{
					moveTo(0, 0);
					clearScreenToBottom();
					moveTo(0, 0);
				}

				else
					clearScreen();

				supergridPrinter(supergrid, grid, winCoordinates);
				#ifdef windows
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				int columns, rows;

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
				columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
				rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

				printf(" %i %i\n", rows, columns);				
				#endif
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
					supergridPrinter(supergrid, grid, winCoordinates);
					printf("Jogador %i venceu!", player);
					win = true;
				}
				player++;
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