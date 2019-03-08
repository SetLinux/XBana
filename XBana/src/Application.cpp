/*#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Sprite.h"
#include <string>
#include <iostream>
#include "Shader.h"
#include "../Texture.h"
#include "../Window.h"
#include <Box2D/Box2D.h>
#include "../Game.h"
float accumulator, lastTickTime;
b2Body* body;
Sprite test;

Sprite test2;
std::string VertexShader = (
	"#version 330 core \n"
	"\n layout(location = 0) in vec4 position; \n"
	"layout (location = 1) in vec2 aTexCoord; \n"
	"uniform mat4 model; \n"
	"uniform mat4 view; \n"
	"uniform mat4 projection;\n "
	"out vec2 TexCoord; \n"
	"void main() { \n"
	" gl_Position = projection * view * model * vec4(position.xy,0.0,1.0); \n"
	"TexCoord = aTexCoord; \n "
	"}"

	);

std::string fragmentShader = (
	"#version 330 core \n"
	"\n  out vec4 color; \n"
	"in vec2 TexCoord; \n"

	"uniform sampler2D ourTexture;  \n"
	"void main()  { \n"
	" color = texture(ourTexture, TexCoord); \n"
	"}"

	);
Shader shdr(VertexShader, fragmentShader);

void smooth(float ff) {
	const float oneMinusRatio = 1.f - ff;
	//test.smoothedposition =
	//	glm::vec2(ff * (test.body->GetPosition().x), ff * (test.body->GetPosition().y)) + (oneMinusRatio * test.previousposition);
	test.smoothedposition = Game::interpolate(test.previousposition, glm::vec2(test.body->GetPosition().x, test.body->GetPosition().y), ff);
}
void resetsmooth() {
	test.smoothedposition = glm::vec2(test.body->GetPosition().x, test.body->GetPosition().y);
}
void update() {
	std::cout << "test" << std::endl;
}

void upd(float dt) {
	//smooth(dt);
	test.Draw(dt);
	test2.Draw();
}

void FixedUpdate(float dt) {
	test.previousposition = glm::vec2(test.body->GetPosition().x, test.body->GetPosition().y);
	resetsmooth();
	Game::GetWorld()->Step(dt, 8, 3);
	Game::GetWorld()->ClearForces();
	
}
int main(void)
{
	
	GLFWwindow* window = Window::MakeWindow();
	shdr.Compile();
	shdr.Use();
	test.Init();
	test.SetTexture("wall.jpg");
	test.position = glm::vec2(100,-2000);
	test2.Init();
	test2.SetTexture("wall.jpg");
	test2.position = glm::vec2(100, 150);
	test2.scale = glm::vec2(400, 100);
	test.InitPhysics(true);
	test2.InitPhysics(false);
	Window::Loop(upd,FixedUpdate, window);
	
	return 0;
}*/
#include "../Level.h"
#include "../ResourceManager.h"
#include "../Window.h"
#include "../Object.h"
#include "../Component.h"
#include "../Components/SpriteComponent.h"
std::string VertexShader = (
	"#version 330 core \n"
	"\n layout(location = 0) in vec4 position; \n"
	"layout (location = 1) in vec2 aTexCoord; \n"
	"uniform mat4 model; \n"
	"uniform mat4 view; \n"
	"uniform mat4 projection;\n "
	"out vec2 TexCoord; \n"
	"void main() { \n"
	" gl_Position = projection * view * model * vec4(position.xy,0.0,1.0); \n"
	"TexCoord = aTexCoord; \n "
	"}"

	);

std::string fragmentShader = (
	"#version 330 core \n"
	"\n  out vec4 color; \n"
	"in vec2 TexCoord; \n"

	"uniform sampler2D ourTexture;  \n"
	"void main()  { \n"
	" color = texture(ourTexture, TexCoord); \n"
	"}"

	);
Shader shdr(VertexShader, fragmentShader);
class MyLevel : public Level {
	Object obj;

	virtual void Update(float dt) override {
		Level::Update(dt);
		obj.Update(dt);
	
	};
	virtual void FixedUpdate(float dt) override {
		Level::FixedUpdate(dt);
		Texture* test = ResourceManager::LoadTexture("wall.jpg");


	
	
	};
public:
	void Start() {
		
		MakeSprite(glm::vec2(0, 000), glm::vec2(100,100), false, ResourceManager::LoadTexture("wall.jpg"));
		MakeSprite(glm::vec2(0, 200), glm::vec2(400,100),true, ResourceManager::LoadTexture("wall.jpg"));
		obj.AddComponent<TransformComponent>();
		obj.AddComponent<SpriteComponent>();
		obj.Init();
	}
};
int main() {
	GLFWwindow* window = Window::MakeWindow();
	MyLevel* level = new MyLevel();
	shdr.Compile();
	shdr.Use();

	level->Init();
	level->Start();
	Window::Loop(level, window);
}