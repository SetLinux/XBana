#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::Update(float dt)
{
	timer += dt * speed;
	currentIndex = (int)(timer / TimeBetween);
}
