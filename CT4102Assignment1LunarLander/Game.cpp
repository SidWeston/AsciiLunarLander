#include "Game.h"
#include "Utility.h"
#include "Constants.h"

Game::Game() 
{
	//constructor
}

void Game::Initialise()
{
	//console title
	SetConsoleTitle(L"Console Title");

	//set screen buffer size
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	//set console window size 
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
}

void Game::Update(float deltaTime)
{


	switch (currentGameState)
	{
		case SPLASH:
		{

			splash.DURATION += deltaTime;

			if (splash.DURATION < 3.0) 
			{
				//draw splash image
				WriteImageToBuffer(consoleBuffer, splash.CHARACTERS, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
			}
			else 
			{
				currentGameState = MENU;
				splash.DURATION = 0;
			}

			break;
		}
		case MENU:
		{
			//clears the splash screen
			ClearScreen(consoleBuffer);

			WriteTextToBuffer(consoleBuffer, "1. PLAY", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
			WriteTextToBuffer(consoleBuffer, "2. OPTIONS", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 1);
			WriteTextToBuffer(consoleBuffer, "3. SCOREBOARD", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 2);
			WriteTextToBuffer(consoleBuffer, "4. EXIT", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 3);

			if (GetAsyncKeyState(KEY_1)) 
			{
				currentGameState = PLAY;
			}
			else if (GetAsyncKeyState(KEY_2)) 
			{
				currentGameState = OPTIONS;
			}
			else if (GetAsyncKeyState(KEY_3)) 
			{
				currentGameState = SCOREBOARD;
			}
			else if (GetAsyncKeyState(KEY_4)) 
			{
				exitGame = true;
			}

			break;
		}
		case PLAY:
		{
			if (!player.hasCrashed && !player.hasLanded) 
			{
				timePlayed += deltaTime;
			}


			//inputs
			if (GetAsyncKeyState(KEY_ESC)) 
			{
				exitGame = true; //sets exitGame to true once escape is pressed, ending the game loop
			}

			if (player.hasCrashed || player.hasLanded) 
			{
				//reset the game, without returning to the menu
				if (restartable) { //checks if the player can restart (without having to return to the menu)
					if (GetAsyncKeyState(KEY_ENT)) 
					{
						player.Reset();
						scoreAdded = false;
						fuelLost = false;
						if (player.fuel < 50) //if fuel is less than 50, a fuel pickup spawns in one of 5 locations
						{ 
							fuelPickup.Reset();
							fuelPickup.XPos = SetFuelPositionX();
						}
					}
				}

				//reset the game, and return to the menu
				if (GetAsyncKeyState(KEY_SPACE)) 
				{
					if(score > highscore)
					{
						highscore = score;
					}
					player.Reset();
					fuelPickup.Reset();
					player.fuel = 100; //resets fuel
					currentGameState = MENU;
					scoreAdded = false;
					fuelLost = false;
					score = 0;
					restartable = true;
					timePlayed = 0;
				}
			}

			if (!player.hasLanded && !player.hasCrashed) 
			{
				if (GetAsyncKeyState(KEY_W)) {
					if (player.fuel > 0) 
					{
						player.isAccelerating = true;
						player.fuel -= FUEL_CONSUMPTION_RATE;
					}
				}

				if (GetAsyncKeyState(KEY_A)) 
				{
					--player.XPos; //moves player left
				}

				if (GetAsyncKeyState(KEY_D)) 
				{
					++player.XPos; //moves player right
				}

				//should we accelerate
				if (player.isAccelerating) 
				{
					player.landerAcceleration += (player.ACCELERATION_RATE * deltaTime);
				}
				else 
				{
					player.landerAcceleration -= (player.DECELERATION_RATE * deltaTime);
				}

				//reset acceleration flag
				player.isAccelerating = false;

				//clamp acceleration
				player.landerAcceleration = ClampFloat(player.landerAcceleration, 0.0f, 1.5f);

				if (player.landerAcceleration >= 1.0f) 
				{
					player.YPos--;

				}
				else if (player.landerAcceleration < 0.5f) 
				{
					player.YPos++;
				}

				//gets the two characters under our landing gear
				char bottomLeftChar = background.CHARACTERS[player.XPos + SCREEN_WIDTH * (player.YPos + (player.HEIGHT - 1))];
				char bottomRightChar = background.CHARACTERS[(player.XPos + (player.WIDTH - 1)) + SCREEN_WIDTH * (player.YPos + (player.HEIGHT - 1))];

				if ((player.XPos == fuelPickup.XPos) && (player.YPos == fuelPickup.YPos)) 
				{
					if (!fuelPickup.pickedUp) 
					{
						fuelPickup.pickedUp = true;
						player.fuel += fuelPickup.fuelAmount;
					}
				}

				//Land or Crash?
				if (bottomLeftChar != ' ' || bottomRightChar != ' ') 
				{
					if (bottomLeftChar == '_' && bottomRightChar == '_') 
					{
						player.hasLanded = true;
					}
					else if (bottomLeftChar != ' ' || bottomRightChar != ' ') 
					{
						player.hasCrashed = true;
					}					
				}
			}



			//clamp movement to stop player from going off the edge of the screen
			player.XPos = ClampInt(player.XPos, 0, (SCREEN_WIDTH - player.WIDTH));
			player.YPos = ClampInt(player.YPos, 0, (SCREEN_HEIGHT - player.HEIGHT));

			//clear the previous frame
			ClearScreen(consoleBuffer);

			//Draw Background image 
			WriteImageToBuffer(consoleBuffer, background.CHARACTERS, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

			if (player.hasCrashed) 
			{
				static float explosionFlashTimer = 0.0f;
				explosionFlashTimer += deltaTime;

				if (explosionFlashTimer >= 0.5f) 
				{
					//draw explosion
					WriteImageToBuffer(consoleBuffer, explosion.CHARACTERS, explosion.COLOURS, explosion.HEIGHT, explosion.WIDTH, player.XPos, player.YPos);
					explosionFlashTimer = 0.0f;
				}
				else
				{
					//draw empty characters
					WriteImageToBuffer(consoleBuffer, explosion.EMPTY_CHARACTERS, explosion.COLOURS, explosion.HEIGHT, explosion.WIDTH, player.XPos, player.YPos);
				}

				if (!fuelLost) //player loses 25 fuel if they crash 
				{ 
					player.fuel -= 25;
					fuelLost = true;
				}
			}

			if (!fuelPickup.pickedUp) 
			{
				WriteImageToBuffer(consoleBuffer, fuelPickup.CHARACTERS, fuelPickup.COLOURS, fuelPickup.HEIGHT, fuelPickup.WIDTH, fuelPickup.XPos, fuelPickup.YPos);
			}

			if (!player.hasCrashed) 
			{
				//draw player image
				WriteImageToBuffer(consoleBuffer, player.VERTICAL_CHARACTERS, player.COLOURS, player.HEIGHT, player.WIDTH, player.XPos, player.YPos);
			}

			//draw game over screen
			if (player.hasLanded) 
			{
				float scoreMultiplier = 0;
				if (player.fuel > 0) {
					WriteTextToBuffer(consoleBuffer, "THE EAGLE HAS LANDED", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					WriteTextToBuffer(consoleBuffer, "Press 'Enter' To Restart", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
					WriteTextToBuffer(consoleBuffer, "Press 'Escape' To Exit Game", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 2);
					WriteTextToBuffer(consoleBuffer, "Press 'Space Bar' To Return To The Menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 3);
					if (!scoreAdded) 
					{
						scoreMultiplier = calculateMultiplier(player.XPos); //determines score multiplier
						score += CalculateScore(scoreMultiplier, false); //adds on score for that run
						scoreAdded = true; //breaks the loop
					}
				}
				else if (player.fuel <= 0) 
				{
					restartable = false;
					WriteTextToBuffer(consoleBuffer, "THE EAGLE HAS LANDED", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					WriteTextToBuffer(consoleBuffer, "You Have Run Out Of Fuel! GAME OVER!", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
					WriteTextToBuffer(consoleBuffer, "Press 'Escape' To Exit Game", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 2);
					WriteTextToBuffer(consoleBuffer, "Press 'Space Bar' To Return To The Menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 3);
					if (!scoreAdded) 
					{
						scoreMultiplier = calculateMultiplier(player.XPos); //determines score multiplier
						score += CalculateScore(scoreMultiplier, false); //adds on score for that run
						scoreAdded = true; //breaks the loop
					}
				}
			}
			else if (player.hasCrashed) 
			{
				if (player.fuel <= 0) 
				{
					restartable = false;
					WriteTextToBuffer(consoleBuffer, "HOUSTON WE HAVE A PROBLEM", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					WriteTextToBuffer(consoleBuffer, "You Have Run Out Of Fuel! GAME OVER!", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
					WriteTextToBuffer(consoleBuffer, "Press 'Escape' To Exit Game", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 2);
					WriteTextToBuffer(consoleBuffer, "Press 'Space Bar' To Return To The Menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 3);
				}
				else 
				{
					WriteTextToBuffer(consoleBuffer, "HOUSTON WE HAVE A PROBLEM", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					WriteTextToBuffer(consoleBuffer, "Press 'Enter' To Restart", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
					WriteTextToBuffer(consoleBuffer, "Press 'Escape' To Exit Game", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 2);
					WriteTextToBuffer(consoleBuffer, "Press 'Space Bar' To Return To The Menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 3);
					if (!scoreAdded)
					{
						score += CalculateScore(0, true);
					}
				}
			}

			//draw UI text
			WriteTextToBuffer(consoleBuffer, "SCORE: " + std::to_string(score), 1, 0);
			WriteTextToBuffer(consoleBuffer, "TIME: " + std::to_string(timePlayed) , 1, 1);
			WriteTextToBuffer(consoleBuffer, "FUEL: " + std::to_string(player.fuel), 1, 2);
			break;
		}
		case OPTIONS:
		{
			ClearScreen(consoleBuffer);

			WriteTextToBuffer(consoleBuffer, "1 - Easy Difficulty ", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			WriteTextToBuffer(consoleBuffer, "2 - Medium Difficulty ", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
			WriteTextToBuffer(consoleBuffer, "3 - Hard Difficulty ", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 2);
			WriteTextToBuffer(consoleBuffer, "4 - Back To Menu ", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 3);
			WriteTextToBuffer(consoleBuffer, "ESC - Exit Game ", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 4);

			if (GetAsyncKeyState(KEY_1)) 
			{ //increases game speed to make the game harder, if chosen
				difficultyMultiplier = 1;
				currentGameState = MENU;
			}
			else if (GetAsyncKeyState(KEY_2)) 
			{
				difficultyMultiplier = 2;
				currentGameState = MENU;
			}
			else if (GetAsyncKeyState(KEY_3))
			{
				difficultyMultiplier = 3;
				currentGameState = MENU;
			}
			else if (GetAsyncKeyState(KEY_4)) 
			{
				currentGameState = MENU;
			}
			else if (GetAsyncKeyState(KEY_ESC)) 
			{
				exitGame = true;
			}

			break;
		}
		case SCOREBOARD:
		{

			ClearScreen(consoleBuffer);

			WriteTextToBuffer(consoleBuffer, "Highscore - " + std::to_string(highscore), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			WriteTextToBuffer(consoleBuffer, "4 - Return To Menu ", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
			
			if (GetAsyncKeyState(KEY_4)) 
			{ //returns to menu
				currentGameState = MENU;
			}

			break;
		}
		default:
		{
			break;
		}
		}
}

bool Game::GetExitGame() 
{ //this function allows for the exitGame variable to be accessed in Main.cpp, so the game loop can be ended
	return exitGame;
}

float Game::GetDifficulty() 
{ //passes the difficulty multiplier to Main.cpp
	return difficultyMultiplier;
}

void Game::Draw() 
{
	//kick the draw
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

