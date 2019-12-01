#ifndef CONNECT_4_MAIN_H
#define CONNECT_4_MAIN_H

#include <stdbool.h>

// struct to work as coordinates
typedef struct MoveCoordinates {
	int row, col;
}Move;

// struct to store win information
typedef struct WinInfo {
	bool win;
	int player;
	char victoryType;
	int victoryTypeVariation;
	int row, col;
}Win;

// looks for wins
// return a Win variable
Win winVerifyer(int grid[6][7]);

// gets the row available to play in a certain column
void getTheRow(int grid[6][7], Move* move);

#endif