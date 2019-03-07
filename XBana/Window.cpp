#include "Window.h"
#include <iostream>


Window::Window()
{
}


Window::~Window()
{
}

void Window::Loop(Level* level, GLFWwindow* under)
{

	double t = 0.0;
	float dt = (float)(1.f / 45.f);

	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	while (!glfwWindowShouldClose(under))
	{  // - Measure time
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		if (frameTime > 0.25)
			frameTime = 0.25;
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			level->FixedUpdate(dt);
			t += dt;
			accumulator -= dt;
		}

		const double alpha = accumulator / dt;


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		level->Update(alpha);
		glfwSwapBuffers(under);
		glfwSwapInterval(1);

	}
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
