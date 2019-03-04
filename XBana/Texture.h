#pragma once
#include <GL/glew.h>
#include "stb_image.h"
#include <iostream>
#include <string>
class Texture
{
public:
	Texture(std::string path);
	~Texture();
	void Init();
	void Use();
private:
	std::string path;
	unsigned int TexID;
};

