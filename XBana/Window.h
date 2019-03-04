#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
class Window
{
public:
	Window();
	~Window();

	static GLFWwindow* MakeWindow();
	static void Loop(std::function<void()> under_update, std::function<void(float)> fixedUpdate, GLFWwindow* under);
};

