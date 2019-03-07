#pragma once
#include <vector>
#include "src/Sprite.h"
#include "Texture.h"
#include <memory>
#include "Game.h"
class Level {
public:
	Level();
	~Level();
	
	std::shared_ptr<Sprite> MakeSprite(glm::vec2 position,glm::vec2 scale,bool Static,Texture* texture);
	void Init();
	virtual void Update(float dt);
	virtual void FixedUpdate(float dt);
	
protected:
	std::vector<std::shared_ptr<Sprite>> Sprites;

};