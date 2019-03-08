#pragma once
#include "../Component.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

public:
	//Basically the Component
	// Transformation Controller
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

public:
	//Base Functions
	void Init() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	ComponentType GetType() override;
};

