#include "PhysicsComponent.h"



PhysicsComponent::PhysicsComponent()
{
	PreviousPosition = glm::vec2(0, 0);
}


PhysicsComponent::~PhysicsComponent()
{
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
	fixtureDef.density = 12.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = .4f;
	body->CreateFixture(&fixtureDef);
}
void PhysicsComponent::Update(float dt){
	SmoothedPos =  Game::interpolate(PreviousPosition == glm::vec2(0,0)? Owner->GetComponent<TransformComponent>(Transform)->position : PreviousPosition, glm::vec2(body->GetPosition().x, body->GetPosition().y), dt);
	Owner->GetComponent<TransformComponent>(Transform)->position = SmoothedPos * Game::kPixelsPerMeter;
}
void PhysicsComponent::FixedUpdate(float dt) {
	PreviousPosition = glm::vec2(body->GetPosition().x,body->GetPosition().y);
}