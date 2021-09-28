//---------------------------------------------------------
// file:	main.c
// author:	Anthon Reid
// email:	anthon.reid@digipen.edu
//
// brief:	A splashscreen of made with the Digipen
//			logo using the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"

CP_Image digiLogo;
CP_Sound drum;
CP_Sound hiHat;
CP_Sound clap;
CP_Sound aNote;


int fadeOut;
int fadeIn;
float rotationControl;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	CP_System_SetWindowSize(800, 800);
	digiLogo = CP_Image_Load("./Assets/DigiPen_BLACK.png");
	drum = CP_Sound_Load("./Assets/BassDrum.wav");
	hiHat = CP_Sound_Load("./Assets/HiHat.wav");
	clap = CP_Sound_Load("./Assets/Clap.wav");
	aNote = CP_Sound_Load("./Assets/Notes/a.wav");

	CP_System_SetFrameRate(5);
	fadeOut = 255; 
	fadeIn = 0;
	rotationControl = 0;
	
	
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{	
	float requiredWaitTime = 6.0f;
	float logoDisplayTime = CP_System_GetSeconds();
	int randomColor = CP_Random_RangeInt(0, 255);
	CP_Color backgroundColor = CP_Color_Create(255, 255, 255, 255);
	CP_Color backgroundColorTwo = CP_Color_Create(randomColor, 130, 200, 255);
	
	CP_Graphics_ClearBackground(backgroundColor);
	
	if (logoDisplayTime < requiredWaitTime || fadeIn < 255 )
	
	{
		fadeIn += 5;
		CP_Image_Draw(digiLogo, 400, 400, 300, 100, fadeIn);
		
	
	}
	
	else {
		CP_Graphics_ClearBackground(backgroundColorTwo);
		if ( rotationControl < 360 ) {
			rotationControl += 1;
			if (CP_System_GetFrameCount() % 14 == 0) {

			
		
				CP_Sound_Play(drum);
				CP_Image_DrawAdvanced(digiLogo, 400, 400, 350, 150, 255, rotationControl);
				
			}

			else {

				CP_Image_DrawAdvanced(digiLogo, 400, 400, 300, 100, 255, rotationControl);

			}
		

			if (CP_System_GetFrameCount() % 28 == 0) {
				
				CP_Sound_Play(clap);
				
			}
			if (CP_System_GetFrameCount() % 112 == 0) {
			
			
				CP_Sound_Play(aNote);
			
			}
	
		}
		else {
			if (fadeOut > 0) {

				fadeOut -= 5;

			}
			CP_Image_DrawAdvanced(digiLogo, 400, 400, 300, 100, fadeOut, 0);
			CP_Graphics_ClearBackground(backgroundColor);
			
		

		}


		
	
	}


	

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
