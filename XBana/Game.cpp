#include "Game.h"

float Game::kPixelsPerMeter =90.f;
float Game::kGravity = 20.2f; // adjust this to taste
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
