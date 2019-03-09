#include "Animation.h"
#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::Update(float dt)
{
	if (indexes.size() > 0) {
	
		timer += dt * speed;
		
		if ((int)(timer/TimeBetween) > indexes.size() - 1) {
			currentIndex = indexes[0];
			timer = 0;
			return;
		}
		currentIndex = (int)(timer / TimeBetween);
	}
}

void Animation::MakeAnimation(int start, int end)
{
	int count = end - start;
	for (int i = 0; i <= count; i++) {
		indexes.push_back(start + i);
	}
}
