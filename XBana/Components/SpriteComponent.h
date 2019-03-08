#pragma once
#include "../Component.h"

#include <iostream>
#include <GL/glew.h>
#include "../XTypes.h"
#include "../Texture.h"
#include "../src/Shader.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent();
	~SpriteComponent();
	
	

	//Base Functions
	virtual void Init();
	virtual void Update(float dt);
	virtual void FixedUpdate(float dt);
	virtual ComponentType GetType();
private:
	void Draw(float dt);
	Vertex vertices[6];
	unsigned int VAO, VBO;
	Texture* tex;
	unsigned int viewLoc;
	unsigned int projectionLoc;
	glm::mat4 view;
	glm::mat4 projection;

};

