#include "Level.h"



Level::Level()
{
	
}


Level::~Level()
{
	
}

std::shared_ptr<Sprite> Level::MakeSprite(glm::vec2 position, glm::vec2 scale, bool Static, Texture* texture)
{
	std::shared_ptr<Sprite> spr = std::make_shared<Sprite>();
	spr->Init();
	spr->position = position;
	
	spr->scale = scale;
	spr->InitPhysics(!Static);

	Sprites.push_back(spr);
	return spr;
}

void Level::Init()
{
}

void Level::Update(float dt)
{
	for (int i = 0; i < Sprites.size(); i++) {
		Sprites[i]->Draw(dt);


	}
}

void Level::FixedUpdate(float dt)
{
	for (int i = 0; i < Sprites.size(); i++) {
		if (Sprites[i]->body) {
			Sprites[i]->previousposition = glm::vec2(Sprites[i]->body->GetPosition().x, Sprites[i]->body->GetPosition().y);
		}
	}
	Game::GetWorld()->Step(dt, 8, 3);
	Game::GetWorld()->ClearForces();

}
