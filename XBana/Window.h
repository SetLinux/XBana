#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Game.h"
class Window
{
public:
	Window();
	~Window();

	static GLFWwindow* MakeWindow();
	static void Loop(std::function<void(float)> under_update, std::function<void(float,float)> fixedUpdate, GLFWwindow* under);
};

