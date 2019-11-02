#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
/* ^^ these are the include guards */

/* Prototypes for the functions */
//inicia as variáveis da I.A.
void aiStart(int symbolToPlay);

/*faz a I.A. jogar, de acordo com a dificuldade
e retorna as coordenadas de seua jogada*/
int* aiPlay(int grid[3][3], int difficulty);

/*verifica se falta somente um simbolo para
alguém ganhar em uma ou mais posições de vitória
retornando um array com arrays contendo as informções
de vitória. è quase uma cópia do winVerifyer em Jogo da Velha.c*/
int** winPositionVerifyer(int aiGrid[3][3], int symbol);

#endif