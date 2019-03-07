#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Game.h"
#include "Level.h"
class Window
{
public:
	Window();
	~Window();

	static GLFWwindow* MakeWindow();
	static void Loop(Level* level, GLFWwindow* under);
};

