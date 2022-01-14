#include <Windows.h>
#include <chrono>
#include "GameObjects.h"
#include "Game.h"

typedef std::chrono::steady_clock::time_point Time;
typedef std::chrono::high_resolution_clock HiResClock;
typedef std::chrono::duration<float> TimeDiff;




int main() 
{

	Game gameInstance;
	
	gameInstance.Initialise();

	float deltaTime = 0.0f;
	Time previousFrameTime = HiResClock::now();
	bool exitGame = false;
	float difficultyMultiplier = 1;

	while (!exitGame) //main game loop, deactivates when the player presses escape
	{ 

		//calculate deltaTime
		Time currentFrameTime = HiResClock::now();
		TimeDiff diff = currentFrameTime - previousFrameTime;
		deltaTime = diff.count();

		if (deltaTime >= (1.0f / (FRAME_RATE * difficultyMultiplier))) 
		{

			//update the application
			gameInstance.Update(deltaTime);
			
			previousFrameTime = currentFrameTime;		
		}

		gameInstance.Draw();

		exitGame = gameInstance.GetExitGame();
		difficultyMultiplier = gameInstance.GetDifficulty();

	}


	return 0;
}
