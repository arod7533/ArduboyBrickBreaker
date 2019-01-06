/*
BrickBreaker
January 5, 2019
Copyright (C) 2019 Tony Rodriguez
All rights reserved.
*/

#include <ArduboyTonesPitches.h>
#include <ArduboyTones.h>
#include <Arduboy2.h>

// make an instance of arduboy used for many functions
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);



//Variables needed for gameplay
int gamestate = 0;
float ballx = 62;
float bally = 0;
int ballsize = 4;
int ballright = 1;
int balldown = 1;
float ballSpeed = 1.5;
int ballRadius = 1;
int paddleWidth = 20;
int paddleHeight = 3;
int paddleX = 64 - (paddleWidth / 2);
int paddleY = 55;
int paddleRadius = 1;


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
		//Fill circle for the ball
		arduboy.fillRoundRect(ballx, bally, ballsize, ballsize, ballRadius, WHITE);

		//Move the ball right
		if (ballright == 1) {
			ballx = ballx + ballSpeed;
		}
		//Move the ball left
		if (ballright == -1) {
			ballx = ballx - ballSpeed;
		}
		//Reflect the ball off of the left side of the screen
		if (ballx <= 0) {
			ballright = 1;
			sound.tone(600, 50);
		}
		//Reflect the ball off of the right side of the screen
		if (ballx + ballsize >= 127) {
			ballright = -1;
			sound.tone(600, 50);
		}
		//Move the ball down
		if (balldown == 1) {
			bally = bally + ballSpeed;
		}
		//Move the ball up
		if (balldown == -1) {
			bally = bally - ballSpeed;
		}
		//Reflect the ball off of the top of the screen
		if (bally <= 0) {
			balldown = 1;
			sound.tone(500, 50);
		}
		//Reflect the ball off of the bottom of the screen
		if (bally + ballsize >= 64) {
			balldown = -1;
		}
		//Fill the rectangle for the paddle
		arduboy.fillRoundRect(paddleX, paddleY, paddleWidth, paddleHeight, paddleRadius, WHITE);

		//Paddle Movement
		if (arduboy.pressed(LEFT_BUTTON) && (paddleX - paddleRadius * 2) >= 0) {
			paddleX = paddleX - 2;
		}
		if (arduboy.pressed(RIGHT_BUTTON) && (paddleX + paddleWidth + paddleRadius * 2) <= 128) {
			paddleX = paddleX + 2;
		}
		//Paddle and ball collision
		if (bally + ballsize >= paddleY && (paddleX - paddleRadius * 2) < ballx + ballsize && (paddleX + paddleWidth + paddleRadius * 2) > ballx) {
			balldown = -1;
			sound.tone(900, 50);
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