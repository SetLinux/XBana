#include "Game.h"

float Game::kPixelsPerMeter =32.f;
float Game::kGravity = 50.2f; // adjust this to taste
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
