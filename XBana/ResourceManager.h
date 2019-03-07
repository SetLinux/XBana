#pragma once
#include "Texture.h"
#include <vector>
#include <memory>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	static Texture* LoadTexture(std::string path);

private:
	static std::vector<Texture*> TexturesList;
};

