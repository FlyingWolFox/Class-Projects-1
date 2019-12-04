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

DWORD green_button, red_button, yellow_button, blue_button, wrong, youreTooSlow, fanfare[2]; // sounds dwords

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

// tracks the time elapsed
int timeElapsed(bool start)
{
	long maxTime;
	static clock_t now, then;

	maxTime = 5000 * (CLOCKS_PER_SEC / 1000);
	if (start)
		now = then = clock();
	now = clock();
	return (now - then);
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

void setSkillLevel(int* skillLevel)
{
	switch (*skillLevel)
	{
	case 1:
		*skillLevel = 8;
		break;
	case 2:
		*skillLevel = 14;
		break;
	case 3:
		*skillLevel = 20;
		break;
	case 4:
		*skillLevel = 31;
		break;

	default:
		*skillLevel = 8;
		break;
	}
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
	puts("-My Instant for the \"You're too slow\" SFX (https://www.myinstants.com/instant/youre-too-slow/)");
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
	int skillLevel = 8; // max lenght of the sequence. Can be changed by the user
	int gameMode = 1; // game mode switch
	int windowSize[2];
	sshort sequence[35]; // sequence of buttons to press
	sshort input[35]; // sequence of button pressed
	COORD mouseCoord;
	EVENT retEvent; // return event of the windows console interaction
	char trashcan[10]; // used to get inputs and freeze the program
	bool mistake = false; // flag
	bool tooSlow = false; // flag

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
	youreTooSlow = BASS_StreamCreateFile(FALSE, "youre-too-slow.ogg", 0, 0, 0);
	fanfare[0] = BASS_StreamCreateFile(FALSE, "ffi_victory.ogg", 0, 0, 0);
	fanfare[1] = BASS_StreamCreateFile(FALSE, "chrono_trigger_fanfare.ogg", 0, 0, 0);

	printf("Starting Simon. Do you wish to:\n(P) play now;\n(O)change options\n or\n(T)see the tutorial?\n");
	fgets(trashcan, 5, stdin);

	// prints the tutorial
	if (trashcan[0] == 'T' || trashcan[0] == 't')
	{
		clearScreenToTop();
		moveTo(0, 0);
		puts("Simon (basic) rules:");
		puts("-The board will flash colors on screen, in certain order");
		puts("-You repeat the pattern clicking on the same colors");
		puts("-If you get every color right, you go to the next level");
		puts("-Each level increases by one the number of colors to repeat");
		puts("-If you miss one, the game ends");
		puts("-Have paciense, the click will only work if the cursor is at the botton of the window");
		puts("-Also, the color have sounds, use this to your advantage");
		puts("-Your failure also has a sound, don't be scared");
		puts("-Your skill you'll be rewarded if you win");
		puts("-Per default the maximun lenght of a sequence is 8, but you can change this in the options menu");
		puts("");
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
		trashcan[0] = 'O';
		clearScreenToTop();
		moveTo(0, 0);
	}

	if (trashcan[0] == 'O' || trashcan[0] == 'o')
	{
		clearScreenToTop();
		moveTo(0, 0);
		puts("Here you can change the skill level and the game mode");
		puts("");
		puts("Skill level defines the maximum lenght of the sequnce before you win");
		puts("There's 4 skill levels:");
		puts("1- lenght = 8");
		puts("2- lenght = 14");
		puts("3- lenght = 20");
		puts("4- lenght = 31");
		puts("");
		puts("Game mode is how you play Simon. There's 3 modes:");
		puts("1- You against Simon. It says and you repeat");
		puts("2- You againnst your (or a friend's) memory. You say, you (or them) repeat");
		puts("3- Multiplayer. Everyone have a color, when Simon say someone's color, this person has to repeat. If it fails, his color is eliminated. The last Man standing wins");
		puts("");
		printf("What skill level will you play? ");
		fgets(trashcan, 5, stdin);
		skillLevel = trashcan[0] - '0';
		setSkillLevel(&skillLevel);
		printf("What game mode will you play? ");
		fgets(trashcan, 5, stdin);
		gameMode = trashcan[0] - '0';
		trashcan[0] = 'P';
	}

	if (trashcan[0] == 'P' || trashcan[0] == 'p')
	{
		if (gameMode == 1)
		{
			// play loop
			for (bool replay = true; replay == true;)
			{
				level = 1;
				while (mistake == false && level <= skillLevel)
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

						timeElapsed(true);
						tooSlow = false;

						// won't get out of the loop until the mouse click was received
						while (true)
						{
							retEvent.event.mouseEvent = 0xc00;
							retEvent = eventMain();
							mouseCoord = retEvent.event.mouseCoord;
							if (timeElapsed(false) >= 5000)
							{
								tooSlow = true;
								break;
							}
							if (retEvent.event.mouseEvent == FROM_LEFT_1ST_BUTTON_PRESSED)
								break;
						}

						// will add the button input into its array
						if (!tooSlow)
							input[count] = coordinatesToButton(mouseCoord, windowSize);

						// displays the button pressed
						// and play its sound
						if (!tooSlow)
						{
							display(input[count], windowSize);
							playSFX(sequence[count]);
						}

						// checks if you make a mistake
						// if yes it breaks the loop
						if (!tooSlow)
						{
							if (sequence[count] != input[count])
							{
								mistake = true;
								break;
							}
						}
						if (tooSlow)
							break;
					}

					// runs the "too slow" routine
					if (tooSlow == true)
					{
						// plays "too slow" sound
						puts("Too Slow! Try again? (Y/N)");
						BASS_ChannelPlay(youreTooSlow, FALSE);
						fgets(trashcan, 5, stdin);
						if (trashcan[0] == 'n' || trashcan[0] == 'N')
							replay = false;
					}

					// runs the mistake routine
					if (mistake == true && tooSlow == false)
					{
						// plays mistake sound
						BASS_ChannelPlay(wrong, FALSE);
						puts("Not right! Try again? (Y/N)");
						fgets(trashcan, 5, stdin);
						if (trashcan[0] == 'n' || trashcan[0] == 'N')
							replay = false;
					}
					if (tooSlow)
						mistake = true;

					level++; // high the level by one
				}

				if (!tooSlow && !mistake)
				{
					int randFanfare = rand() % 2;
					BASS_ChannelPlay(fanfare[randFanfare], TRUE);
					printf("You win! Try again? (Y/N)");
					fgets(trashcan, 5, stdin);
					if (trashcan[0] == 'n' || trashcan[0] == 'N')
						replay = false;
					BASS_ChannelStop(fanfare[randFanfare]);
				}
				mistake = false; // reset the mistake flag when starting a new game
				tooSlow = false; // reset the tooSlow flag when starting a new game
			}
		}
	
		if (gameMode == 2)
		{
			// play loop
			for (bool replay = true; replay == true;)
			{
				level = 1;
				while (mistake == false && level <= skillLevel)
				{
					// gets the console window size
					{
						setupConsole();
						moveTo(999, 999);
						getCursorPosition(&windowSize[0], &windowSize[1]);
						clearScreenToTop();
						restoreConsoleMode();
					}

					// gets the mouse input
					// and make the button that are pressed bright

					// here we get the sequence from the player
					// the screen willl be cleaned up when the sequence get the correct size
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

						// will add the button input into the sequence array
						sequence[count] = coordinatesToButton(mouseCoord, windowSize);

						display(sequence[count], windowSize);
						playSFX(sequence[count]);
					}

					// here the player have to repeat the sequence he created
					// the behavior here is a lot like of the game mode 1
					for (int count = 0; count < level; count++)
					{
						display(NO_COLOR, windowSize);

						timeElapsed(true);
						tooSlow = false;

						// won't get out of the loop until the mouse click was received
						while (true)
						{
							retEvent.event.mouseEvent = 0xc00;
							retEvent = eventMain();
							mouseCoord = retEvent.event.mouseCoord;
							if (timeElapsed(false) >= 5000)
							{
								tooSlow = true;
								break;
							}
							if (retEvent.event.mouseEvent == FROM_LEFT_1ST_BUTTON_PRESSED)
								break;
						}

						// will add the button input into its array
						if (!tooSlow)
							input[count] = coordinatesToButton(mouseCoord, windowSize);

						// displays the button pressed
						// and play its sound
						if (!tooSlow)
						{
							display(input[count], windowSize);
							playSFX(sequence[count]);
						}

						// checks if you make a mistake
						// if yes it breaks the loop
						if (!tooSlow)
						{
							if (sequence[count] != input[count])
							{
								mistake = true;
								break;
							}
						}
						if (tooSlow)
							break;
					}

					// runs the "too slow" routine
					if (tooSlow == true)
					{
						// plays "too slow" sound
						puts("Too Slow! Try again? (Y/N)");
						BASS_ChannelPlay(youreTooSlow, FALSE);
						fgets(trashcan, 5, stdin);
						if (trashcan[0] == 'n' || trashcan[0] == 'N')
							replay = false;
					}

					// runs the mistake routine
					if (mistake == true && tooSlow == false)
					{
						// plays mistake sound
						BASS_ChannelPlay(wrong, FALSE);
						puts("Not right! Try again? (Y/N)");
						fgets(trashcan, 5, stdin);
						if (trashcan[0] == 'n' || trashcan[0] == 'N')
							replay = false;
					}
					if (tooSlow)
						mistake = true;

					level++; // high the level by one
				}

				if (!tooSlow && !mistake)
				{
					int randFanfare = rand() % 2;
					BASS_ChannelPlay(fanfare[randFanfare], TRUE);
					printf("You win! Try again? (Y/N)");
					fgets(trashcan, 5, stdin);
					if (trashcan[0] == 'n' || trashcan[0] == 'N')
						replay = false;
					BASS_ChannelStop(fanfare[randFanfare]);
				}
				mistake = false; // reset the mistake flag when starting a new game
				tooSlow = false; // reset the tooSlow flag when starting a new game
			}
		}
	}
	BASS_Free(); // free the BASS from memory
	thanks(); // prints the thanks
	fgets(trashcan, 5, stdin); // freezes execution before the game closes

	return 0;
}