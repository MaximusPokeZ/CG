#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int x, int y);

int main()
{
	if (!glfwInit())
	{
		std::cerr << "Error init GLFW";
	}
	// Задаем конфигурации используем OpenGL ver 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// используем core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// создаем основное окно
	GLFWwindow* window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);
	if (window == nullptr)
	{
		std::cerr << "Window cant init";
		glfwTerminate();
		return -1;
	}
	// устанавливаем как текущий контекст
	// (чтобы все вызовы были для этого окна)
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Glad cant init";
		return -1;
	}

	glViewport(0, 0, 300, 300);

	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{
			glClearColor(0.8f, 0.3f, 0.3f, 1.0f); // выбираем цвет
			glClear(GL_COLOR_BUFFER_BIT); // заполняем
			glfwSwapBuffers(window); //свапаем буфера back front
		}
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
		}

		glfwPollEvents(); // события
	}


	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int x, int y)
{
	glViewport(0, 0, x, y);
}