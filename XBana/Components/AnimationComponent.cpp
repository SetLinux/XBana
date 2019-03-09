#include "AnimationComponent.h"



AnimationComponent::AnimationComponent()
{
}


AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Init()
{
}
void AnimationComponent::Update(float dt) {
	if (animation) {
		index = animation->currentIndex;
	}
}
void AnimationComponent::FixedUpdate(float dt) {
	animation->Update(dt);
}
void AnimationComponent::SetIndex(int index) {
	this->index = index;
}
float  AnimationComponent::GetXOffset() {
	int column = index % (int)Rows;
	float xOffset = (float)column / (float)Rows;
	return xOffset;
}
float AnimationComponent::GetYOffset() {
	int row = index / Rows;
	float yOffset = (float)row / (float)Rows;
	return yOffset;
}
ComponentType AnimationComponent::GetType() {
	return Animator;
}