#ifndef FORCA_MAIN_H
#define FORCA_MAIN_H

typedef struct WordInfo {
	char word[30];
	int numberOfLetters;
	char tip[40];
}Word;

typedef struct Coordinates {
	int row, col;
}Coordinate;

typedef enum BodyParts {
	HANG,
	HEAD,
	UPPER_BODY,
	LEFT_ARM,
	RIGHT_ARM,
	LOWER_BODY,
	LEFT_LEG,
	RIGHT_LEG
}Body;


#endif