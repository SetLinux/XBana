#include "TransformComponent.h"
#include <iostream>


TransformComponent::TransformComponent()
{
	position = glm::vec2(0, 0);
	scale = glm::vec2(300.0f, 300.0f);
	rotation = 0.f;
}


TransformComponent::~TransformComponent()
{
}
void TransformComponent::Init() {

}
void TransformComponent::FixedUpdate(float dt) {

}
ComponentType TransformComponent::GetType()
{
	return ComponentType::Transform;
}
void TransformComponent::Update(float dt) {

}
