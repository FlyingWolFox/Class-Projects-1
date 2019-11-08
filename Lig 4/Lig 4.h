#ifndef CONNECT_4_MAIN_H
#define CONNECT_4_MAIN_H

#include <stdbool.h>

typedef struct MoveCoordinates {
	int row, col;
}Move;

typedef struct WinInfo {
	bool win;
	int player;
	char victoryType;
	int victoryTypeVariation;
	int row, col;
}Win;

Win winVerifyer(int grid[6][7]);
void getTheRow(int grid[6][7], Move* move);

#endif