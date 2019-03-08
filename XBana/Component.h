#pragma once
#include "Components/ComponentType.h"

class Object;
class Component{
public:
	Component();
	~Component();
	virtual void Init();
	virtual void Update(float dt);
	virtual void FixedUpdate(float dt); 

	virtual ComponentType GetType();
	Object* Owner;
protected:
};

