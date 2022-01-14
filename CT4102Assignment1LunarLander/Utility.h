#ifndef UTILITY_H
#define UTILITY_H

#include <Windows.h>
#include <string>
#include "Constants.h"
#include <time.h>

int ClampInt(int intToClamp, int lowerLimit, int upperLimit) 
{
	if (intToClamp <= lowerLimit) 
	{
		return lowerLimit;
	}
	else if (intToClamp >= upperLimit) 
	{
		return upperLimit;
	}
	else 
	{
		return intToClamp;
	}
}

float ClampFloat(float floatToClamp, float lowerLimit, float upperLimit) 
{
	return floatToClamp <= lowerLimit ? lowerLimit : floatToClamp >= upperLimit ? upperLimit : floatToClamp;
}

void WriteImageToBuffer(CHAR_INFO* consoleBuffer, const char* charsToPrint, const int coloursToPrint[], const int imageHeight, const int imageWidth, int imageXPos, int imageYPos) 
{
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Char.AsciiChar = charsToPrint[x + imageWidth * y];
			if (coloursToPrint) 
			{
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = coloursToPrint[x + imageWidth * y];

			}
			else 
			{
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = 7;
			}

		}
	}
}



void ClearScreen(CHAR_INFO* consoleBuffer) 
{
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++)
	{
		consoleBuffer[i].Char.AsciiChar = 0;
		consoleBuffer[i].Attributes = 0;
	}
}

void WriteTextToBuffer(CHAR_INFO* consoleBuffer, std::string stringToPrint, int textXPos, int TextYPos) 
{

	for (int x = 0; x < stringToPrint.length(); x++)
	{
		consoleBuffer[(textXPos + x) + SCREEN_WIDTH * TextYPos].Char.AsciiChar = stringToPrint[x];
		consoleBuffer[(textXPos + x) + SCREEN_WIDTH * TextYPos].Attributes = 0xf;
	}

}

float calculateMultiplier(int playerXPos)
{
	if (playerXPos >= 4 && playerXPos <= 8) 
	{
		return(2);
	}
	else if (playerXPos >= 10 && playerXPos <= 16) 
	{
		return(2);
	}
	else if (playerXPos >= 18 && playerXPos <= 21) 
	{
		return(4);
	}
	else if (playerXPos >= 29 && playerXPos <= 33) 
	{
		return(2);
	}
	else if (playerXPos >= 41 && playerXPos <= 49) 
	{
		return(2);
	}
	else if (playerXPos >= 69 && playerXPos <= 75) 
	{
		return(2);
	}
	else if (playerXPos >= 88 && playerXPos <= 91) 
	{
		return(4);
	}
	else if (playerXPos >= 95 && playerXPos <= 98) 
	{
		return(4);
	}
	else if (playerXPos >= 112 && playerXPos <= 114) 
	{
		return(8);
	}
	else if (playerXPos >= 118 && playerXPos <= 121) 
	{
		return(4);
	}
	else if (playerXPos >= 128 && playerXPos <= 135) 
	{
		return(2);
	}
	else if (playerXPos >= 143 && playerXPos <= 146) 
	{
		return(8);
	}
}

float CalculateScore(float multiplier, bool crashed) 
{

	if (!crashed) 
	{
		return(100 * multiplier);
	}
	else 
	{
		return(0);
	}

}

int SetFuelPositionX() 
{
	int fuelPos = 0;
	srand(time(NULL));
	fuelPos = rand() % 5 + 1; //randomly picks between 1 and 5, which determines the location of the fuel pickup
	if (fuelPos == 1) 
	{
		fuelPos = 12;
	}
	else if (fuelPos == 2) 
	{
		fuelPos = 25;
	}
	else if (fuelPos == 3) 
	{
		fuelPos = 40;
	}
	else if (fuelPos == 4) 
	{
		fuelPos = 60;
	}
	else if (fuelPos == 5) 
	{ 
		fuelPos = 80;
	}
	else 
	{
		fuelPos = 50; //just in case random number generator fails/generates a number outside the range
	}
	return fuelPos;
}



#endif // !UTILITY_H

