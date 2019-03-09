#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Game.h"
#include "Level.h"
#include <map>
#include <functional>
#include <vector>
class Window
{
	using Callback = std::function<void()>;
public:

	Window();
	~Window();
	static GLFWwindow* MakeWindow();
	static void Loop(Level* level, GLFWwindow* under);
	static int GetKey(int key);
private:
	static GLFWwindow* x_window;
};

