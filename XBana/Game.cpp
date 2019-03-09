#include "Game.h"

float Game::kPixelsPerMeter =100.f;
float Game::kGravity = 30.2f; // adjust this to taste
b2World* Game::world;


Game::Game()
{
}


Game::~Game()
{
}

b2World* Game::GetWorld()
{
	if (!world) {
		world = new b2World(b2Vec2(0.0f, kGravity));
		world->SetAllowSleeping(true);
		world->SetContinuousPhysics(true);
	
	}
	return world;
}

void Game::ChangePPM(float value)
{
	kPixelsPerMeter = value;
}

float Game::lerp(float a, float b, float f)
{
		return a + f * (b - a);

}

glm::vec2 Game::interpolate(glm::vec2 previous, glm::vec2 currnet, float alpha)
{
	// state = currentstate * alpha + previousstate * (1-alpha)
	const float oneMinusRatio = 1.f - alpha;
	return glm::vec2(alpha * (currnet.x), alpha * (currnet.y)) + (oneMinusRatio * previous);
}

