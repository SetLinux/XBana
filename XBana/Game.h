#pragma once
#include <Box2D/Box2D.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
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
	static glm::vec2 interpolate(glm::vec2 previous, glm::vec2 currnet, float alpha);
private:
	static b2World* world;
};

