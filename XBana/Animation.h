#pragma once
#include <vector>
class Animation
{
public:
	Animation();
	~Animation();
	std::vector<int> indexes;
	int CurrentValue;
	float TimeBetween;
	float timer;
	float speed;
	void Update(float dt);
	int currentIndex;
private:
};

