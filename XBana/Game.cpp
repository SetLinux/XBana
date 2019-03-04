#include "Game.h"

float Game::kPixelsPerMeter = 0.9f;
float Game::kGravity = Game::kPixelsPerMeter / 0.7f; // adjust this to taste
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
