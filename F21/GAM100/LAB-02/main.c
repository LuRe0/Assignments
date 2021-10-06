//---------------------------------------------------------
// file:	main.c
// author:	Anthon Reid
// email:	anthon.reid@digipen.edu
//
// brief:	Program containing a basic jumping mecanic
//			made using the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include <math.h>
#include <stdio.h>

void playerObject(float xPosition, float yPosition, float rotation, float armRotation);
void stageBuilder(void);
void game_init(void);
void game_update(void);
void game_exit(void);

float playerXPosition = 350;
float playerYPosition;
float gravity = 9.81f;
float velocity = 10.0f;
float jumpVelocity = 30.0f;
float jumpState = 0;
float rotationControl = 0;
int myFrameCount = 0;
float armWave = 0;


// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	//CP_System_SetFrameRate(120);
	
	
	 myFrameCount = 0;
	 playerXPosition = 350;
	 playerYPosition = 150;
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)

{
	++myFrameCount;


	CP_Graphics_ClearBackground(CP_Color_Create(100, 120, 200, 255));

	

	stageBuilder();
	
	if (myFrameCount > 0) {

		rotationControl += 5;


	}
	if(CP_Input_KeyDown(KEY_D)){
		
		armWave = sinf(CP_System_GetSeconds() + playerXPosition) * 30.0f;
		playerXPosition += velocity;
		
	
		}
	else {

		armWave = 0;
	}


	if (CP_Input_KeyDown(KEY_A)) {

		armWave = sinf(CP_System_GetSeconds() + playerXPosition) * 30.0f;
		playerXPosition -= velocity;
		
		

	}



	if (CP_Input_KeyDown(KEY_SPACE)) {

		
		if (jumpState < (jumpVelocity/2)) {
			rotationControl += 30;
			armWave = 45;
			jumpState += 1;
			playerYPosition -= (jumpVelocity - gravity);
	
			if (CP_System_GetFrameCount() % 4 == 0) {
				CP_Settings_Stroke(CP_Color_Create(245, 155, 40, 255));
				CP_Settings_Fill(CP_Color_Create(255, 165, 50, 255));
				CP_Graphics_DrawTriangle(playerXPosition + 13, playerYPosition + 30,    // point 1
					playerXPosition - 13, playerYPosition + 30,                         // point 2
					playerXPosition - 5, playerYPosition + 70);


			
			}
		}

		if (CP_Input_KeyDown(KEY_D)) {
		
			armWave = 45;
		}

		if (CP_Input_KeyDown(KEY_A)) {
		
			armWave = -45;
		}
	
	}
	else if(CP_Input_KeyReleased(KEY_SPACE))
	{
		jumpState = 0;
		armWave = 0;
		
	}

	




	if (CP_Input_KeyDown(KEY_D) && CP_Input_KeyTriggered(KEY_E)) {

		playerXPosition += 200;
		

	}

	if (CP_Input_KeyDown(KEY_A) && CP_Input_KeyTriggered(KEY_E)) {

		playerXPosition -= 200;

	}



	if (playerYPosition < 568.98  || playerXPosition > 480 && playerXPosition < 810 || playerYPosition > 578.8) {
	
		playerYPosition += gravity;

	
	}


	


	if ( CP_Input_KeyDown(KEY_A) && playerXPosition == 0 ) {
	
		velocity = 0;

		
	}

	else if (playerXPosition == 0 && CP_Input_KeyDown(KEY_D)) {

		velocity = 10;

	}

	if (CP_Input_KeyDown(KEY_D) && playerXPosition == 1200) {

		velocity = 0;


	}

	else if ( playerXPosition == 1200 &&  CP_Input_KeyDown(KEY_A)) {

		velocity = 10;

	}


	 if ( playerXPosition >= 810  && playerYPosition <= 600) {
	
		CP_Settings_TextSize(60);
		char gameClearMessage[256] = { 0 };
		sprintf_s(gameClearMessage, 256, "The Robot Cleared The Gap. Congratulations!");
		CP_Font_DrawText(gameClearMessage, 50, 400);
	}



	if (playerYPosition > 800) {
		
		CP_Settings_TextSize(80);
		char gameOverMessage[128] = { 0 };
		sprintf_s(gameOverMessage, 128, "The Robot Failed. Press R To Restart");
		CP_Font_DrawText(gameOverMessage, 50, 400);
	
	
	}

	if (CP_Input_KeyTriggered(KEY_R))
	{
		// restart
		CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		// exit
		CP_Engine_Terminate();
	}

	CP_Settings_TextSize(20);
	char buffer[32] = { 0 };
	sprintf_s(buffer, 32, "JumpState: %.1f", jumpState);
	CP_Font_DrawText(buffer, 20, 20);
	sprintf_s(buffer, 32, "jumpVelocity: %.1f", jumpVelocity);
	CP_Font_DrawText(buffer, 20, 40);
	sprintf_s(buffer, 32, "posY: %.1f", playerYPosition);
	CP_Font_DrawText(buffer, 20, 60);
	sprintf_s(buffer, 32, "posX: %.1f", playerXPosition);
	CP_Font_DrawText(buffer, 20, 80);
	sprintf_s(buffer, 32, "FrameCount: %i", myFrameCount);
	CP_Font_DrawText(buffer, 20, 100);
	sprintf_s(buffer, 32, "Velocity: %f", velocity);
	CP_Font_DrawText(buffer, 20, 120);
	sprintf_s(buffer, 32, "Gravity: %f", gravity);
	CP_Font_DrawText(buffer, 20, 140);


	CP_Settings_TextSize(60);
	sprintf_s(buffer, 32, "Press R to restart.");
	CP_Font_DrawText(buffer, 750, 40);
	sprintf_s(buffer, 32, "Press ESC to exit.");
	CP_Font_DrawText(buffer, 750, 80);



	playerObject(playerXPosition, playerYPosition, rotationControl, armWave);
	}

//this creates the stage
void stageBuilder(void) {
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Stroke(CP_Color_Create(100, 30, 50, 255));
	CP_Settings_Fill(CP_Color_Create(100, 30, 50, 255));
	CP_Graphics_DrawRect(100, 700, 700, 200);
	CP_Graphics_DrawRect(1200, 700, 700, 200);
}


//this creates the player
void playerObject(float xPosition, float yPosition, float rotation, float armRotation) {

	CP_Settings_RectMode(CP_POSITION_CENTER);

	
	CP_Settings_Stroke(CP_Color_Create(140, 40, 40, 255));
	CP_Settings_Fill(CP_Color_Create(150, 50, 50, 255));
	CP_Graphics_DrawEllipseAdvanced(xPosition, yPosition - 60, 10, 30, rotation);
	CP_Graphics_DrawEllipseAdvanced(xPosition, yPosition - 60, 10, 30, -rotation);

	CP_Settings_Stroke(CP_Color_Create(50, 50, 50, 255));
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRectAdvanced(xPosition, yPosition, 20, 50, 0, 0);


	CP_Settings_RectMode(CP_POSITION_CORNER);

	CP_Settings_Stroke(CP_Color_Create(50, 50, 50, 255));
	CP_Settings_Fill(CP_Color_Create(150, 50, 50, 255));
	CP_Graphics_DrawRectAdvanced(xPosition - 5 , yPosition - 20, 10, 30, armRotation, 0);



}








// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	
}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	
	CP_System_SetWindowSize(1200, 800);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
