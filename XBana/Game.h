#pragma once
#include <Box2D/Box2D.h>
class Game
{
public:
	Game();
	~Game();

	static b2World* GetWorld();
	static void ChangePPM(float value);
	static float kPixelsPerMeter ;
	static float kGravity; // adjust this to taste
	static float lerp(float a, float b, float f);
private:
	static b2World* world;
};

