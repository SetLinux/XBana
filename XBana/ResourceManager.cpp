#include "ResourceManager.h"

std::vector<Texture*> ResourceManager::TexturesList;

ResourceManager::ResourceManager()
{
}
void LoadTexture(std::string path)
{
	
}

ResourceManager::~ResourceManager()
{
}

Texture* ResourceManager::LoadTexture(std::string path)
{
	for (int i = 0; i < TexturesList.size(); i++) {
		if (TexturesList[i]->path == path) {
			return TexturesList[i];
		}
	}
	Texture* tex = new Texture(path);
	tex->Init();
	TexturesList.push_back(tex);
	return TexturesList.back();
}
