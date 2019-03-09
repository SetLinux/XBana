#pragma once
#include <vector>
#include <iostream>
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
	void MakeAnimation(int start, int end);
private:
};

