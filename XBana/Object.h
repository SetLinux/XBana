#pragma once
#include <vector>
#include "Component.h"
#include "Components/TransformComponent.h"
#include <memory>
class Object
{
public:
	Object();
	~Object();
	// Adding the Component Type I Want AddComponent<Type>();
	template<class T>
	void AddComponent();
	// Getting the Component Type I Want GetComponent<Type>();
	template<typename T>
	T* GetComponent(ComponentType Ctype);
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void FixedUpdate(float dt);
protected:
	std::vector<Component*> Components;
};

template<class T>
inline void Object::AddComponent()
{
	T* component = new T();
	component->Owner = this;
	Components.push_back(component);
	
}

template<class T>
inline T* Object::GetComponent(ComponentType Ctype)
{
	for (auto& it : Components) {
		if ((it)->GetType() == Ctype) {
			return (T*)(it);
		}
	}
	return nullptr;
	
}
