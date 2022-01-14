#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "Constants.h"

//STRUCTS
struct Player 
{
	//functions
	void Reset() 
	{
		XPos = 10;
		YPos = 10;
		isAccelerating = false;
		landerAcceleration = 0.0f;
		hasLanded = false;
		hasCrashed = false;

	}

	//CONSTANTS
	static const int WIDTH = 2;
	static const int HEIGHT = 3;
	const char* VERTICAL_CHARACTERS = 
	{
		R"(__)"
		R"(||)"
		R"(/\)"
	};
	const char* RIGHT_CHARACTERS = 
	{
	R"( __/)"
	R"(|__)"
	R"(   \)"
	};
	const int COLOURS[WIDTH * HEIGHT] = 
	{
		0xF, 0xF,
		0xF, 0xF,
		0xE, 0xE,
	};
	//VARIABLES
	int XPos = 10;
	int YPos = 10;
	bool isAccelerating = false;
	float landerAcceleration = 0.0f;
	bool hasLanded = false;
	bool hasCrashed = false;
	bool landerHorizontal = false;
	const float ACCELERATION_RATE = 0.5f;
	const float DECELERATION_RATE = 0.5f;
	float fuel = 100;
};

struct Background 
{
    const char* CHARACTERS = 
	{
       R"(                                                                                                                                                      )"
       R"(                                                                                                                                                      )"
       R"(                                                                                                                                                      )"
       R"(                                                                                                                                                      )"
       R"(                                                                                                                                                      )"
       R"(                                                                                                                                                      )"
       R"(                                                                                                                                                      )"
       R"(                                                                                                                __                                    )"
       R"(                                                                                                               /x8\                                   )"
/*10*/ R"(                                                                                                              /    \                                  )"
       R"(                                                                                                             /      \                                 )"
       R"(                                                                                                            /        \___                             )"
       R"(                                                                     ______                                /           x4\                            )"
       R"(                                                                    /  x2  \                              /               \                           )"
       R"(                                                                   /        \                            /                 \                          )"
       R"(                                                                  |          \                          /                   \                         )"
       R"(                                                                  |           \                        /                     \                        )"
       R"(                                                                  |            \                      /                       \                       )"
       R"(                                                                 /              \                    /                         \_______               )"
/*20*/ R"(                                                                /                \                  /                             x2   \              )"
       R"(                                                               /                  \                /                                    \             )"
       R"(                                                              |                    \           ___/                                      \            )"
       R"(                                                             /                      \         / x4                                        \           )"
       R"(                                                            /                        \       /                                             \         /)"
       R"(                                                           /                          \     /                                               \       / )"
       R"(                                                          /                            \___/                                                 \     /  )"
       R"(                             ____                        /                               x4                                                   \___/   )"
       R"(                            / x2 \                      /                                                                                       x8    )"
       R"(                           /      \                    |                                                                                              )"
/*30*/ R"(                          /        |                   |                                                                                              )"
       R"(                         /         |                   |                                                                                              )"
       R"(          _____         /          |                  /                                                                                               )"
       R"(         /  x2 \       /            \                /                                                                                                )"
       R"(        /       \     /              \              /                                                                                                 )"
       R"(    ___/         \___/                \            /                                                                                                  )"
       R"(   / x2            x4                  \          /                                                                                                   )"
       R"(  /                                     |        |                                                                                                    )"
       R"( /                                      |________|                                                                                                    )"
       R"(/                                           x2                                                                                                        )"
/*40*/ R"(                                                                                                                                                      )"
    };//  123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
};

struct Splash 
{
	const char* CHARACTERS = 
	{
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
/*10*/ R"(                                               ___________         _____         ______                                                               )"
	   R"(                                              /                   |     |       |      \                                                              )"
	   R"(                                             /                    |_____|       |       \                                                             )"
	   R"(                                             |                     _____        |        \                                                            )"
	   R"(                                             |                    |     |       |         \                                                           )"
	   R"(                                              \                   |     |       |          |                                                          )"
	   R"(                                               \__________        |     |       |          |                                                          )"
	   R"(                                                          \       |     |       |          |                                                          )"
       R"(                                                           \      |     |       |          |                                                          )"
	   R"(                                                           |      |     |       |         /                                                           )"
/*20*/ R"(                                                           |      |     |       |        /                                                            )"
	   R"(                                                          /       |     |       |       /                                                             )"
	   R"(                                               __________/        |_____|       |______/                                                              )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                 S4004925                                                                             )"
	   R"(                                                                  CT4102                                                                              )"
	   R"(                                                   ASSIGNMENT 1: LUNAR LANDER ASCII GAME                                                              )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
/*30*/ R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
	   R"(                                                                                                                                                      )"
/*40*/ R"(                                                                                                                                                      )"
	};//      123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
	//variables
	float DURATION = 0;
};

struct Explosion 
{
	static const int WIDTH = 3;
	static const int HEIGHT = 3;
	const char* CHARACTERS = 
	{
	R"(\|/)"
	R"(- -)"
	R"(/|\)"
	};
	const char* EMPTY_CHARACTERS = 
	{
	R"(  )"
	R"(  )"
	R"(  )"
	};
	const int COLOURS[WIDTH * HEIGHT] = 
	{
	0xF, 0xF,
	0xF, 0xF,
	0xE, 0xE,
	};
};

struct FuelPickup 
{
	float fuelAmount = 50;
	bool pickedUp = false;
	bool instanceActive = false;

	int XPos = 45;
	int YPos = 5;

	static const int WIDTH = 2;
	static const int HEIGHT = 2;
	const char* CHARACTERS = 
	{
	R"(())"
	R"(||)"
	};

	const int COLOURS[WIDTH * HEIGHT] = 
	{
	0xF, 0xF,
	0xF, 0xF,
	};

	void Reset() 
	{
		pickedUp = false;
	}



};

#endif //GAME_OBJECTS_H