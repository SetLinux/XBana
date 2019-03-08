#include "Component.h"
#include "Object.h"
#include <iostream>

Component::Component()
{

}


Component::~Component()
{

}

void Component::Init()
{
}

void Component::Update(float dt)
{
}

void Component::FixedUpdate(float dt)
{
}

ComponentType Component::GetType()
{
	return ComponentType();
}
