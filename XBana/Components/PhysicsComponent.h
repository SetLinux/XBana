#pragma once
#include "../Component.h"
#include "TransformComponent.h"
#include <Box2D/Box2D.h>
#include "../Game.h"
#include "../Object.h"
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	void Init() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	ComponentType GetType() override;
	b2Body* body;
protected:
	glm::vec2 PreviousPosition;
	glm::vec2 SmoothedPos;
};

