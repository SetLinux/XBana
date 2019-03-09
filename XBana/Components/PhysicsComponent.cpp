#include "PhysicsComponent.h"
#include <iostream>


PhysicsComponent::PhysicsComponent()
{
	PreviousPosition = glm::vec2(0, 0);
}


PhysicsComponent::~PhysicsComponent()
{
	Game::GetWorld()->DestroyBody(body);
	
}

void PhysicsComponent::Init() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(Owner->GetComponent<TransformComponent>(Transform)->position.x / Game::kPixelsPerMeter, Owner->GetComponent<TransformComponent>(Transform)->position.y / Game::kPixelsPerMeter);
	bodyDef.fixedRotation = true;
	body = Game::GetWorld()->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(
		(Owner->GetComponent<TransformComponent>(Transform)->scale.x / 2.f) / Game::kPixelsPerMeter,
		(Owner->GetComponent<TransformComponent>(Transform)->scale.y / 2.f) / Game::kPixelsPerMeter);
	b2FixtureDef fixtureDef;
	body->SetType(b2_dynamicBody);
	fixtureDef.shape = &shape;
	fixtureDef.density = 120.0f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = .2f;
	body->CreateFixture(&fixtureDef);
}
void PhysicsComponent::Update(float dt){
	SmoothedPos =  Game::interpolate(PreviousPosition == glm::vec2(0,0)? Owner->GetComponent<TransformComponent>(Transform)->position / Game::kPixelsPerMeter : PreviousPosition,glm::vec2(body->GetPosition().x, body->GetPosition().y), dt);

	glm::vec2 finals = glm::vec2(SmoothedPos.x * Game::kPixelsPerMeter, SmoothedPos.y * Game::kPixelsPerMeter);
	Owner->GetComponent<TransformComponent>(Transform)->position = finals;
}
void PhysicsComponent::FixedUpdate(float dt) {
	PreviousPosition = glm::vec2(body->GetPosition().x,body->GetPosition().y);
}

ComponentType PhysicsComponent::GetType()
{
	return Physics;
}
