#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
/* ^^ these are the include guards */

/* Prototypes for the functions */

/*verifica se alguém venceu e retorna um array[3]
caso verdade, retorna {1, W, C},
sendo W o tipo de vitória:
0 = Horizontal, 1 = Vertical
2 = Diagonal 1 (\), 3 = Diagonal 2 (/)
sendo C uma coordenada, i para vitória
horizontal e j para o resto */
int* winVerifyer(int grid[3][3]);

/*verifica se há até 3 casas livres
e retorna as 3 posições, ou menos*/
int** freeCells(int grid[3][3]);

/*retem a gridCopy usada na tieVerifyer
para passá-la para a main*/
int** gridTiedReturner(int gridCopy[3][3], int mod);

/*verifica se o jogo vai empatar daqui 3, 2 ou 1 jogada(s)
caso empate, retorna 1
caso não, retorna 0*/
int tieVerifyer(int grid[3][3], int player, int insertionPreference);

//converte o posicionamento de 1 a 9 por coordenadas
int* convertToCoordinate(int position);

//converte as coordenadas da grade para coordenadas da
//super grade
int* coordinatesToSupergrid(int coordinates[2]);

//modifica a super grade, botando X ou O
void superGridModifier(char supergrid[31][51], int grid[3][3]);

//imprime a grade
void gridPrinter(int grid[3][3], int mod);

//imprime os agradecimentos
void thanks();

#endif