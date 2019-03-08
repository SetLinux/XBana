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
	for (std::vector<Component*>::iterator it = Components.begin(); it != Components.end(); ++it) {
		(*it)->Init();
	}
}

void Object::Update(float dt)
{
	for (std::vector<Component*>::iterator it = Components.begin(); it != Components.end(); ++it) {
		(*it)->Update(dt);
	}
}

void Object::FixedUpdate(float dt)
{
	for (std::vector<Component*>::iterator it = Components.begin(); it != Components.end(); ++it) {
		(*it)->FixedUpdate(dt);
	}
}
