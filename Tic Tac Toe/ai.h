#ifndef TIC_TAC_TOE_AI_H
#define TIC_TAC_TOE_AI_H
/* ^^ these are the include guards */

/* Prototypes for the functions */

// start the AI variables and gets a random seed to srand
 void aiStart(int symbolToPlay);

 // makes the AI play, accordingly to the difficulty
 // and return its play coordinates
int* aiPlay(int grid[3][3], int difficulty);

// looks if the AI or player can will win in the next turn
// retunrs an array with "win" info
//	[0]: position of the possible win
//	[1]: win type
//	[2]: row for hotizontal, and column for the rest
// it's almost a copy of winVerifyer in tictactoe.c
int** winPositionVerifyer(int aiGrid[3][3], int symbol);

// it'll receive a position on the board that it's not available
// to play and will chose randomly of the other two positions 
int randPostion(int positionNotAvailible);

#endif