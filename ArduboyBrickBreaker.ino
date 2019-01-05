/*
BrickBreaker 
January 5, 2019
Copyright (C) 2019 Tony Rodriguez
All rights reserved.
*/

#include <Arduboy2.h>

// make an instance of arduboy used for many functions
Arduboy2 arduboy;


//Variables needed for gameplay
int gamestate = 0;
int ballx = 62;
int bally = 0;
int ballsize = 4;
int ballright = 1;
int balldown = 1;


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
	// initiate arduboy instance
	arduboy.begin();

	//Seed the random number generator
	srand(7 / 8);
	//Set the game to 60 frames per second
	arduboy.setFrameRate(60);
	arduboy.clear();
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
	// pause render until it's time for the next frame
	if (!(arduboy.nextFrame()))
		return;

	arduboy.pollButtons();

	arduboy.clear();
	//Game code here
	switch (gamestate) {
	case 0:
		//Title screen
		arduboy.setCursor(0, 0);
		arduboy.print("Title Screen");
		//Change the gamestate
		if (arduboy.justPressed(A_BUTTON)) {
			gamestate = 1;
		}
		break;
	case 1:
		//Gameplay screen
		arduboy.setCursor(0, 0);
		arduboy.print("Gameplay");

		arduboy.drawRect(ballx, bally, ballsize, ballsize, WHITE);
		//Move the ball right
		if (ballright == 1) {
			ballx = ballx + 1;
		}
		//Move the ball left
		if (ballright == -1) {
			ballx = ballx - 1;
		}
		//Reflect the ball off of the left side of the screen
		if (ballx == 0) {
			ballright = 1;
		}
		//Reflect the ball off of the right side of the screen
		if (ballx == 127) {
			ballright = -1;
		}

		//Change the gamestate
		if (arduboy.justPressed(A_BUTTON)) {
			gamestate = 2;
		}
		break;
	case 2:
		//Win screen
		arduboy.setCursor(0, 0);
		arduboy.print("Win Screen");
		//Change the gamestate
		if (arduboy.justPressed(A_BUTTON)) {
			gamestate = 3;
		}
		break;
	case 3:
		//Game over screen
		arduboy.setCursor(0, 0);
		arduboy.print("Game Over Screen");
		//Change the gamestate
		if (arduboy.justPressed(A_BUTTON)) {
			gamestate = 0;
		}
		break;
	}

	// then we finaly we tell the arduboy to display what we just wrote to the display
	arduboy.display();
}
