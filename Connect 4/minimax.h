#ifndef CONNECT_4_MINIMAX_H
#define CONNECT_4_MINIMAX_H

#include "connect_4.h"

void supergridTied(char supergrid[37][98]);
bool minimaxTie(int grid[6][7], int nextplayer);
Move minimaxPlay(int grid[6][7]);

#endif