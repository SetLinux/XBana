#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
	for (std::vector<Component*>::iterator it = Components.begin(); it != Components.end(); ++it) {
		delete (*it);
	}

}




void Object::Init()
{
	for (auto& it : Components) {
		(it)->Init();
	}
}

void Object::Update(float dt)
{
	for (auto& it : Components) {
		(it)->Update(dt);
	}
}

void Object::FixedUpdate(float dt)
{
	for (auto& it : Components) {
		(it)->FixedUpdate(dt);
	}
}
