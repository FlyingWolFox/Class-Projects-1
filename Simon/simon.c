#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ansi_escapes.h"
#include "windowsConsoleInteraction.h"

// used to play the sounds
#include "bass.h"

// handles mouse interaction
#include <conio.h>
#pragma comment(lib, "bass.lib")

DWORD green_button, red_button, yellow_button, blue_button, wrong; // sounds dwords

extern EVENT eventMain(VOID);

extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);
extern void getCursorPosition(int* row, int* col);

typedef unsigned char sshort; // defines a char type as sshor, to use just one byte intead or 2 of the short

typedef enum ColorButtons {
	NO_COLOR = 0,
	GREEN = 1,
	RED,
	YELLOW,
	BLUE
}Color;

// delays the period of time passed by argument
void delay(int milliseconds)
{
	long pause;
	clock_t now, then;

	pause = milliseconds * (CLOCKS_PER_SEC / 1000);
	now = then = clock();
	while ((now - then) < pause)
		now = clock();
}

// display the game
void display(int button, int screenSize[2])
{
	setupConsole();

	moveTo(0, 0);
	// will print the buttons
	// if they're triggered, they're printed in a bright color
	for (int row = 0; row <= (screenSize[0] / 2) - 2; row++)
	{
		if (button == GREEN)
			setBackgroundColorRGB(0, 150, 0); // bright green
		else
			setBackgroundColorRGB(15, 60, 15); // shadow green
		for (int greenCol = 0; greenCol <= (screenSize[1] / 2) - 1; greenCol++)
			printf(" ");

		if (button == RED)
			setBackgroundColorRGB(150, 30, 40); // bright red
		else
			setBackgroundColorRGB(70, 30, 30); // shadow red
		for (int rednCol = 0; rednCol <= (screenSize[1] / 2) - 1; rednCol++)
			printf(" ");

		printf("\n");

	}

	// if the screen buffer is even, it'll make a little black line to separate the buttons
	if (screenSize[0] % 2 != 0)
		printf("\n");

	for (int row = 0; row <= (screenSize[0] / 2) - 2; row++)
	{
		if (button == YELLOW)
			setBackgroundColorRGB(255, 255, 0); // bright yellow
		else
			setBackgroundColorRGB(50, 50, 0); // shadow yellow
		for (int greenCol = 0; greenCol <= (screenSize[1] / 2) - 1; greenCol++)
			printf(" ");


		if (screenSize[1] % 2 != 0)
			printf(" ");

		if (button == BLUE)
			setBackgroundColorRGB(40, 30, 150); // bright blue
		else
			setBackgroundColorRGB(15, 15, 60); // shadow blue
		for (int rednCol = 0; rednCol <= (screenSize[1] / 2) - 1; rednCol++)
			printf(" ");
	}
	restoreConsole();
	printf("\n");
}

// converts the coordinates of the click of the mouse to which button was pressed
int coordinatesToButton(COORD click, int windowSize[2])
{
	if (click.Y < windowSize[0] / 2)
	{
		if (click.X < windowSize[1] / 2)
			return GREEN;
		if (click.X > windowSize[1] / 2)
			return RED;
	}

	if (click.Y > windowSize[0] / 2)
	{
		if (click.X < windowSize[1] / 2)
			return YELLOW;
		if (click.X > windowSize[1] / 2)
			return BLUE;
	}
	return 0;
}

// generates the next button of the sequence
void rng(sshort* sequence, int level)
{
	sequence[level - 1] = 1 + rand() % 4;
	sequence[level] = 0;
}

// plays the sound effects
void playSFX(int button)
{
	switch (button)
	{
	case 1:
		BASS_ChannelPlay(green_button, FALSE);
		break;
	case 2:
		BASS_ChannelPlay(red_button, FALSE);
		break;
	case 3:
		BASS_ChannelPlay(yellow_button, FALSE);
		break;
	case 4:
		BASS_ChannelPlay(blue_button, FALSE);
		break;
	default:
		break;
	}
}

// display error messages from BASS
void Error(const char* text)
{
	printf("Error(%d): %s\n", BASS_ErrorGetCode(), text);
	BASS_Free();
	exit(0);
}

// prints the thanks
void thanks()
{
	clearScreenToTop();
	moveTo(0, 0);
	puts("Thanks for Playing!");
	puts("");
	puts("Thanks to:");
	puts("-Brodhead Media Features for the Wrong Buzzer SFX (https://youtu.be/2naim9F4010)");
	puts("-gamesplusjames for the button sounds that he used in his simon");
	puts("-Stackoverflow people, mainly Ahmad Taha whose question was my solution (https://stackoverflow.com/questions/35797336/how-to-find-the-mouse-button-click-position-x-and-y*/)");
	puts("-Raymond, helping with disabling the quick edit mode (https://devblogs.microsoft.com/oldnewthing/?p=4453)");
	puts("-Tomasz P. Szynalski and his Online Tone Generator for helping me to organze the sounds");
	puts("-The neat things that this program uses works because of them!");
	puts("");
	puts("-Also, thanks to Super Mario Maker streamers on twitch, coded everything hearing you");
	puts("");
	puts("The make of this project has the participation of:");
	puts("-BASS Audio Library, with wich this can play sound");
	puts("-Audacity, that was used to cut the audio");
	puts("-Visual Studio Community 2019, in wich this project was made on.");
	puts("");
	puts("---Press any key to exit---");
}

int main(int argc, char** argv)
{

	int level = 1; // start level
	int windowSize[2];
	sshort sequence[4000]; // sequence of buttons to press
	sshort input[4000]; // sequence of button pressed
	COORD mouseCoord;
	EVENT retEvent; // return event of the windows console interaction
	char trashcan[10]; // used to get inputs and freeze the program
	bool mistake = false; // flag

	srand(time(NULL)); // random seed to srand
	
	// use the default device for sound
	int device = -1;

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
		printf("An incorrect version of BASS was loaded");
		return;
	}

	// checks if the device was initialized
	if (!BASS_Init(device, 44100, 0, 0, NULL))
		Error("Can't initialize device");

	// try streaming the file
	green_button = BASS_StreamCreateFile(FALSE, "green_button.wav", 0, 0, 0);
	red_button = BASS_StreamCreateFile(FALSE, "red_button.wav", 0, 0, 0);
	yellow_button = BASS_StreamCreateFile(FALSE, "yellow_button.wav", 0, 0, 0);
	blue_button = BASS_StreamCreateFile(FALSE, "blue_button.wav", 0, 0, 0);
	wrong = BASS_StreamCreateFile(FALSE, "wrong.wav", 0, 0, 0);

	printf("Starting Simon. Do you wish to:\n(P) play now\nor \n(T)see the tutorial?\n");
	fgets(trashcan, 5, stdin);

	// prints the tutorial
	if (trashcan[0] == 'T' || trashcan[0] == 't')
	{
		clearScreenToTop();
		moveTo(0, 0);
		puts("Simon rules:");
		puts("-The board will flash colors on screen, in certain order");
		puts("-You repeat the pattern clicking on the same colors");
		puts("-If you get every color right, you go to the next level");
		puts("-Each level increases by one the number of colors to repeat");
		puts("-If you miss one, the game ends");
		puts("-Have paciense, the click will only work if the cursor is at the botton of the window");
		puts("-Also, the color have sounds, use this to your advantage");
		puts("-Your failure also has a sound, don't be scared");
		puts("-Here you can go until the level 3999, good luck");
		puts("");
		puts("-Ready to start?");
		// special effect
		for (int count = 0; count < 15; count++)
		{
			delay(250);
			puts("---Press enter to continue---");
			moveUp(1);
			delay(250);
			puts("                               ");
			moveUp(1);
		}
		puts("---Press enter to continue---");
		fgets(trashcan, 5, stdin);
		trashcan[0] = 'P';
		clearScreenToTop();
		moveTo(0, 0);
	}

	if (trashcan[0] == 'P' || trashcan[0] == 'p')
	{
		// play loop
		for (bool replay = true; replay == true;)
		{
			level = 1;
			while (mistake == false)
			{
				// gets the console window size
				{
					setupConsole();
					moveTo(999, 999);
					getCursorPosition(&windowSize[0], &windowSize[1]);
					clearScreenToTop();
					restoreConsoleMode();
				}
				// prints the simon withou any bright buttons
				display(NO_COLOR, windowSize);

				// generates the next button of the sequnce
				rng(sequence, level);

				// will display the triggered button,
				// play its sound
				// and wait a little before continuing
				for (int count = 0; count < level; count++)
				{
					delay(500);
					display(sequence[count], windowSize);
					playSFX(sequence[count]);
					delay(510);
					display(NO_COLOR, windowSize);
				}

				// gets the mouse input
				// and make the button that are pressed bright
				for (int count = 0; count < level; count++)
				{
					display(NO_COLOR, windowSize);

					// won't get out of the loop until the mouse click was received
					while (true)
					{
						retEvent.event.mouseEvent = 0xc00;
						retEvent = eventMain();
						mouseCoord = retEvent.event.mouseCoord;
						if (retEvent.event.mouseEvent == FROM_LEFT_1ST_BUTTON_PRESSED)
							break;
					}

					// will add the button input into its array
					input[count] = coordinatesToButton(mouseCoord, windowSize);

					// displays the button pressed
					// and play its sound
					display(input[count], windowSize);
					playSFX(sequence[count]);

					// checks if you make a mistake
					// if yes it breaks the loop
					if (sequence[count] != input[count])
					{
						mistake = true;
						break;
					}
				}

				// runs the mistake routine
				if (mistake == true)
				{
					// plays mistake sound
					BASS_ChannelPlay(wrong, FALSE);
					puts("Not right! Try again? (Y/N)");
					fgets(trashcan, 5, stdin);
					if (trashcan[0] == 'n' || trashcan[0] == 'N')
						replay = false;
				}
				level++; // high the level by one
			}
			mistake = false; // reset the mistake flag when starting a new game
		}
	}
	BASS_Free(); // free the BASS from memory
	thanks(); // prints the thanks
	fgets(trashcan, 5, stdin); // freezes execution before the game closes

	return 0;
}