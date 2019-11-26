# Class Projects 1

This repository is where my first batch of class projects from college is. Nothing to much complex ~~but the coding here maybe not be the best~~

Here you'll find 5 games: Tic Tac Toe (or naughts and crosses), Connect 4, Hangman, Simon and Battleship. They're all made in C and made to run on a terminal/console. They're made with portability in mind, but not all may be.

## Details:

- This entire repository and the projects were all made on Visual Studio Community 2019. Good portion of the projects will compile on gcc or clang

- These projects depends on the ANSI Escape Codes to work properly/as intended. In Windows machines the cmd will be setted up to support it. If one of these projects have weird screen behavior, like printing random characters, or something like [33;0;0;0m it's because your terminal emulator doens't support ANSI Escape codes 

- Not all projects works on Linux or Unix systems due to OS specific code, on each project deatails will be said if it's compatible with Linux, it's not or if there's a project made for linux

- The releases of these projects will be done

- The coding gets better like this: Tic Tac Toe > Connect 4 > Hangman > Simon > Batleship. This is because Tic Tac Toe was the first I done and I learned in the way of developing the others. Please don't roast me with the bad coding, I'm thinking about rewriting some things

## Projects on this repository

- ### Tic Tac Toe (Naughts and Crosses)
  - The classic game, there isn't that much to talk about
  - The game need ANSI Escape Codes for cleaning the screen
  - The game has two modes: Singleplayer and Multiplayer
    - Multiplayer is the classic form of playing. You and a person play against each other
    - On singleplayer you'll play against a AI, which have 3 difficult levels: Easy, Normal and Impossible. More on that on the wiki
  - The board is made in a beatiful ascii art, including the X and the O. The thanks for the people behind the ascii art is in the wiki and the game
 
- ### Connect 4
  - If you played Club Penguin you already know this game
  - Two people play against each oder, dropping pieces, wich fall in the last line in the board, trying to connect 4 pieces horizontaly, verticaly or diagonally. Who does that first wins
  - The game nedd ANSI Escape Codes to clear the screen and give colors to the pieces, backgroung, and detecting window size
  - The game needs a certain Window Size to work, because the board is big
  - The game has two modes: Singleplayer and Multiplayer
    - On multiplayer you and a person play against each other
    - On singleplayer you'll play against a AI, which is made to be impossible to win. More on that on the wiki
  - The board is made in a beatiful ascii art, including the pieces, wich have colors! . the thanks for the people behind the ascii art is in the wiki and the game
  
- ### Hangman
  -
