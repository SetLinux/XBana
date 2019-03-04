#pragma once
#include "glm/glm.hpp"
#include <Box2D/Box2D.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
struct Vector2D {
	GLfloat x, y;
	Vector2D() : x(0), y(0) {

	}

	Vector2D(float inx, float iny) {
		this->x = inx;
		this->y = iny;
	}
};
struct Vertex {
	Vector2D Position;
	Vector2D TexCoord;
	Vertex() : Position(0, 0)  {

	}
	
	Vertex(Vector2D pos,Vector2D TexCoord) {
		this->Position = pos;
		this->TexCoord = TexCoord;
	}
};
