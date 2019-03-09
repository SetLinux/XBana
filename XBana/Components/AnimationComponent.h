#pragma once
#include "../Component.h"
#include "../Animation.h"
class AnimationComponent : public Component
{
public:
	AnimationComponent();
	~AnimationComponent();
	void Init() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	ComponentType GetType() override;
	void SetIndex(int index);
	float Rows;
	int index;
	float GetXOffset();
	float GetYOffset();
	Animation* animation;
private:

};

