#ifndef CONNECT_4_MAIN_H
#define CONNECT_4_MAIN_H

#include <stdbool.h>

typedef struct MoveCoordinates {
	int row, col;
}Move;

typedef struct WinInfo {
	bool win;
	char victoryType;
	int row, col;
}Win;

#endif