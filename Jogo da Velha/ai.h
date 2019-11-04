#ifndef TIC_TAC_TOE_AI_H
#define TIC_TAC_TOE_AI_H
/* ^^ these are the include guards */

/* Prototypes for the functions */
//inicia as variáveis da I.A.
extern void aiStart(int symbolToPlay);

/*faz a I.A. jogar, de acordo com a dificuldade
e retorna as coordenadas de seua jogada*/
extern int* aiPlay(int grid[3][3], int difficulty);

/*verifica se falta somente um simbolo para
alguém ganhar em uma ou mais posições de vitória
retornando um array com arrays contendo as informções
de vitória. è quase uma cópia do winVerifyer em Jogo da Velha.c*/
int** winPositionVerifyer(int aiGrid[3][3], int symbol);

int randPostion(int positionNotAvailible);



#endif