#include <GL/glew.h>
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

void update() {
	std::cout << "test" << std::endl;
}

void upd() {
	test.Draw();
	test2.Draw();
	
	test.position = glm::vec2(body->GetPosition().x / Game::kPixelsPerMeter, body->GetPosition().y / Game::kPixelsPerMeter);

}
void FixedUpdate(float dt) {
	Game::GetWorld()->Step(dt, 6, 1);
}
int main(void)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	bodyDef.fixedRotation = true;
	body = Game::GetWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(
		100 / Game::kPixelsPerMeter,
		100 / Game::kPixelsPerMeter
	);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.1f;
	body->CreateFixture(&fixtureDef);

	
	GLFWwindow* window = Window::MakeWindow();
	shdr.Compile();
	shdr.Use();
	test.Init();
	test.SetTexture("wall.jpg");
	test.position = glm::vec2(100,0);
	test2.Init();
	test2.SetTexture("wall.jpg");
	Window::Loop(upd,FixedUpdate, window);
	
	return 0;
}