# Class Projects 1

This repository is where my first batch of class projects from college is. Nothing to much complex ~~but the coding here maybe not be the best~~

Here you'll find 5 games: Tic Tac Toe (or naughts and crosses), Connect 4, Hangman, Simon and Battleship. They're all made in C and made to run on a terminal/console. They're made with portability in mind, but not all may be.

## Details:

- This entire repository and the projects were all made on Visual Studio Community 2019. Good portion of the projects will compile on gcc or clang

- These projects depends on the ANSI Escape Codes to work properly/as intended. In Windows machines the cmd will be setted up to support it. If one of these projects have weird screen behavior, like printing random characters, or something like [33;0;0;0m it's because your terminal emulator doens't support ANSI Escape codes 

- Simon and Battleship doesn't work on Linux or Unix systems due to Windows specific code
- The releases of these projects will be done

- The coding gets better like this: Tic Tac Toe > Connect 4 > Hangman > Simon > Batleship. This is because Tic Tac Toe was the first I done and I learned in the way of developing the others. Please don't roast me with the bad coding, I'm thinking about rewriting some things

## Projects on this repository

- ### Tic Tac Toe (Naughts and Crosses)
  - The classic game, there isn't that much to talk about
  - The game need ANSI Escape Codes for cleaning the screen
  - The game has two modes: Singleplayer and Multiplayer
    - Multiplayer is the classic form of playing. You and a person play against each other
    - On singleplayer you'll play against a AI, which have 3 difficult levels: Easy, Normal and Impossible. More on that on the wiki
	- The game looks if the game will tie when there are 3 free positions or less. If it finds that the game will tie, it finishes it
  - The board is made with ascii art, including the X and the O. The thanks for the people behind the ascii art is in the wiki and the game
 
- ### Connect 4
  - If you played Club Penguin you already know this game
  - Two people play against each oder, dropping pieces, which fall in the last line in the board, trying to connect 4 pieces horizontaly, verticaly or diagonally. Who does that first wins
  - The game nedd ANSI Escape Codes to clear the screen and give colors to the pieces, backgroung, and detecting window size
  - The game needs a certain Window Size to work, because the board is big
  - The game has two modes: Singleplayer and Multiplayer
    - On multiplayer you and a person play against each other
    - On singleplayer you'll play against a AI, which is made to be impossible to win. More on that on the wiki
	- The game looks if the game will tie. If it finds that the game will tie, it finishes it
  - The board is made with ascii art, including the pieces, which have colors! . The thanks for the people behind the ascii art is in the wiki and the game
  - The background color are made with true color (RGB), your terminal emulator may not support it. If it doesn't I don't know What will happen
  
- ### Hangman
  - Works just as expected. You'll have to guess the word before the stickman gets hanged. Each mistake make him closer to his death. Get all letters right before this and you win!
  - The word is given by a file which is passed by argument. The project uses C:\word.txt as default
  - The file should look like:
  ```
  <word>
  <tip>
  ```
  - The tip is optional
  - The game nedd ANSI Escape Codes to clear and manipulate the screen
  - The game uses ascii art for the hangman and letters (if the word isn't that big)
  
- ### Simon
  - The game of the 70's and the 80's is now in C!
  - You have to repeat the sequence that the program passes to you. Each time you get all right, the number of presses increases by one
  - There's a little tutorial in the program at the start, however it's optional
  - The game nedd ANSI Escape Codes to clear the screen, and print colors in terminal
  - The colors are made with true color (RGB), your terminal emulator may not support it. If it doesn't I don't know What will happen
  - The game uses mouse interaction, which, for now, it's limited to Windows
  - The game has sounds for each button/color and a game over sound!
  - It uses the BASS Audio Library to play the souds. There five audio files on the project already, 4 for the buttons and 1 for the game over. If you keep the name, you can put your own sounds!
  - Due to have to print the entire screen, the game is dependent of the cpu speed, slowdown with the printing may occur. Don't cick until the cursor is at the botton of the screen or the click won't count
  - ~~~Don't get scared at the game over sound!~~~

- ### Battleship
  - The board/paper guessing game made in C
  - You have bomb every enemy ship on the board
  - There's ships and submarines! The ship's size it's determinated by you
  - There's no multiplayer yet, it'll be limited if it exists
  - The board is get by a text file passed by argument. The project default is C:\textFile.txt
  - The file should look like this, use this as a model, putting in the middle of the vertical bars your entry:
  ```
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  | | | | | | | | | | | |
  ```
  - The symbol for each part of the ship or subarine is the following:
    - `<` for the horizontal Bow of the ship
    - `=` for the horizontal Middle of the ship
    - `>` for the horizontal Stern of the ship
    - `^` for the vertical Bow of the ship
    - `|` for the vertical Middle of the ship
    - `~` for the vertical Stern of the ship
  - If you put the parts wrong, the program will display the ships wrong
  - The game nedd ANSI Escape Codes to clear the screen
  - The game uses ascii art for the board and the ships
  - The game uses mouse interaction, wich, for now, it's limited to Windows
  - Due to have to print the entire screen, the game is dependent of the cpu speed, slowdown with the printing may occur. Don't cick until the cursor is at the botton of the screen or the click won't count
  
## The documentation
This repository will have full documentation. From comment on the code to wiki with the details. If you have a question, probably it'll be answered there! Also the thanks are also there, apart from some "features" of the projects. At the moment there aren't any, the comments on the code will come first then the wiki. If you want to see my progress have a look at the project page! The first notes (and some middle ones) aren't english, but in portuguese. This is because the projects started in it. The code is being translated, but the old notes aren't (sorry for the bad english)
