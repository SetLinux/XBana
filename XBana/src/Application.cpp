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
#include "../Components/PhysicsComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Animation.h"
std::string VertexShader = (
	"#version 330 core \n"
	"\n layout(location = 0) in vec4 position; \n"
	"layout (location = 1) in vec2 aTexCoord; \n"
	"uniform mat4 model; \n"
	"uniform mat4 view; \n"
	"uniform mat4 projection;\n "
	"uniform float numberOfRows;\n"
	"uniform vec2 offset; \n"
	"uniform bool atlas;"
	"out vec2 TexCoord; \n"
	"void main() { \n"
	" gl_Position = projection * view * model * vec4(position.xy,0.0,1.0); \n"
	"if(atlas){ \n"
	"TexCoord = (aTexCoord/numberOfRows) + offset; "
	"} \n else{ \n TexCoord = aTexCoord; \n }"
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
Animation anim;
class MyLevel : public Level {
	Object obj;
	Object obj2;
	Object obj3;

	virtual void Update(float dt) override {
		
		Level::Update(dt);
		obj.Update(dt);
		obj2.Update(dt);
		if (obj.GetComponent<TransformComponent>(Transform)->position.y != obj2.GetComponent<TransformComponent>(Transform)->position.y) {
			std::cout << " A Problem " << std::endl;
		}
		obj3.Update(dt);
		obj.GetComponent<PhysicsComponent>(Physics)->body->SetLinearVelocity(b2Vec2(0, obj.GetComponent<PhysicsComponent>(Physics)->body->GetLinearVelocity().y));

		if (Window::GetKey(GLFW_KEY_A)) {
			obj.GetComponent<PhysicsComponent>(Physics)->body->SetLinearVelocity(b2Vec2(-3, obj.GetComponent<PhysicsComponent>(Physics)->body->GetLinearVelocity().y));
		}
		if (Window::GetKey(GLFW_KEY_D)) {
			obj.GetComponent<PhysicsComponent>(Physics)->body->SetLinearVelocity(b2Vec2(3, obj.GetComponent<PhysicsComponent>(Physics)->body->GetLinearVelocity().y));
		}
	};
	virtual void FixedUpdate(float dt) override {
		
		obj.FixedUpdate(dt);
		obj2.FixedUpdate(dt);
		obj3.FixedUpdate(dt);
		Level::FixedUpdate(dt);
		anim.Update(dt);
		
	
	};
public:
	void MoveLeft() {

	}
	void MoveRight() {

	}
	void Start() {
		
		//MakeSprite(glm::vec2(0, 000), glm::vec2(100, 100), false, ResourceManager::LoadTexture("wall.jpg"));
		//MakeSprite(glm::vec2(150, 000), glm::vec2(100, 100), false, ResourceManager::LoadTexture("wall.jpg"));
		//MakeSprite(glm::vec2(0, 200), glm::vec2(400, 100), true, ResourceManager::LoadTexture("wall.jpg"));

		Texture* test = ResourceManager::LoadTexture("terrain.png");
		Texture* wall = ResourceManager::LoadTexture("wall.jpg");
		obj.AddComponent<TransformComponent>();
		obj.AddComponent<SpriteComponent>();
		obj.AddComponent<AnimationComponent>();
		obj.GetComponent<SpriteComponent>(Renderer)->tex = test;
		obj.GetComponent<AnimationComponent>(Animator)->index = 0;
		obj.GetComponent<AnimationComponent>(Animator)->Rows= 256/16;

		obj.GetComponent<TransformComponent>(Transform)->scale = glm::vec2(100, 100);
		obj.GetComponent<TransformComponent>(Transform)->position = glm::vec2(-110, -3000);
		obj.AddComponent<PhysicsComponent>();
		obj.Init();
	

		obj2.AddComponent<TransformComponent>();
		obj2.AddComponent<SpriteComponent>();
		obj2.GetComponent<SpriteComponent>(Renderer)->tex = wall;
		obj2.GetComponent<TransformComponent>(Transform)->scale = glm::vec2(100, 100);
		obj2.GetComponent<TransformComponent>(Transform)->position = glm::vec2(100, -3000);
		obj2.AddComponent<PhysicsComponent>();
		obj2.Init();
	
		obj3.AddComponent<TransformComponent>();
		obj3.AddComponent<SpriteComponent>();
		obj3.GetComponent<TransformComponent>(Transform)->scale = glm::vec2(500, 100);
		obj3.GetComponent<TransformComponent>(Transform)->position = glm::vec2(100, 200);
		obj3.AddComponent<PhysicsComponent>();
		obj3.Init();
		obj3.GetComponent<PhysicsComponent>(Physics)->body->SetType(b2_staticBody);
		anim.speed = 3.f;
		anim.MakeAnimation(1, 5);
		anim.TimeBetween = 5.f;
		obj.GetComponent<AnimationComponent>(Animator)->animation = &anim;
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