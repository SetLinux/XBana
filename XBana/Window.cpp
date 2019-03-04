#include "Window.h"
#include <iostream>


Window::Window()
{
}


Window::~Window()
{
}

void Window::Loop(std::function<void(float)> under_update, std::function<void(float)> fixedUpdate, GLFWwindow* under)
{
	const double maxFPS = 360.0f;
	const double maxPeriod = 1.0 / maxFPS;

	bool running = true;
	double lastTime = 0.0;

	while (!glfwWindowShouldClose(under))
	{


		double time = glfwGetTime();
		double deltaTime = time - lastTime;

		if (deltaTime >= maxPeriod) {
		fixedUpdate(deltaTime);
			
		lastTime = time;
		}

		// code here gets called with max FPS
		glEnable(GL_MULTISAMPLE);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		under_update(deltaTime);
		glfwSwapBuffers(under);
		glfwSwapInterval(1);
}
	glfwTerminate();
}


GLFWwindow * Window::MakeWindow()
{
	glfwInit();
	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	
	}
	glfwMakeContextCurrent(window);
	const GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
	}
	return window;
}
