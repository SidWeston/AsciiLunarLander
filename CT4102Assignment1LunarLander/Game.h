#ifndef GAME_H
#define GAME_H

//includes
#include <Windows.h>
#include "GameObjects.h"

class Game {
public:
	//functions
	Game();
	void Initialise();
	void Update(float deltaTime);
	void Draw();
	bool GetExitGame();
	float GetDifficulty();

private:
	//enums
	enum GAME_STATE {
		SPLASH,
		MENU,
		PLAY,
		OPTIONS,
		SCOREBOARD,
		GAME_OVER,

	};

	//console parameters
	//window size, starts at 0
	SMALL_RECT windowSize{ 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//A coord struct for specifiying the console's screen buffer dimensions 
	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;

	COORD characterBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);

	//game variables
	GAME_STATE currentGameState = SPLASH;
	Splash splash;
	Background background;
	Player player;
	Explosion explosion;
	FuelPickup fuelPickup;
	float timePlayed = 0;
	float score = 0;
	float highscore = 0;
	float difficultyMultiplier = 1;
	bool restartable = true;
	bool exitGame = false;
	bool scoreAdded = false;
	bool fuelLost = false;

};



#endif // !GAME_H


