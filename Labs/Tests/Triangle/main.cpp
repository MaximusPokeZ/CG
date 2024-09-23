#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


int main()
{
	if(!glfwInit())
	{
		std::cerr << "GLFW can't init";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(700, 700, "Triangle", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Window can't init";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD can't load";
		return -1;
	}

	const char* vertex_shader = "#version 330 core\n"
								"layout (location = 0) in vec3 aPos;\n"
								"void main()\n"
								"{\n"
								"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								"}\0";

	const char* fragment_shader = "#version 330 core\n"
								  "out vec4 Color;\n"
								  "void main()\n"
								  "{\n"
								  "   Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
								  "}\0";

	GLint status;

	// Компилируем вершинный шейдер
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER); // создаем шейдер и присваиваем ему id
	glShaderSource(vertex_shader_id, 1, &vertex_shader, nullptr); // исходный код для шейдера (присваиваем)
	glCompileShader(vertex_shader_id); //
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLchar log[512];
		glGetShaderInfoLog(vertex_shader_id, 512, nullptr, log);
		std::cerr << "Vertex shader compilation error:\n" << log << std::endl;
		return -1;
	}

	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_shader, nullptr);
	glCompileShader(fragment_shader_id);
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLchar log[512];
		glGetShaderInfoLog(fragment_shader_id, 512, nullptr, log);
		std::cerr << "Fragment shader compilation error:\n" << log << std::endl;
		return -1;
	}

	// Создаём шейдерную программу и линкуем шейдеры
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader_id);
	glAttachShader(shader_program, fragment_shader_id);
	glLinkProgram(shader_program); // линковка всех шейдеров в единый исполняемый объект
	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLchar log[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, log);
		std::cerr << "Shader program linking error:\n" << log << std::endl;
		return -1; // правильное завершение при ошибке
	}

	// Шейдеры отдельно больше не нужны
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	float vertexes[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// связываем VAO для использования, теперь все вызовы VBO будут сохранены в VAO
	glBindVertexArray(VAO);

	// Привязываем и загружаем данные в VBO (т.е все вызовы связанные с буфером будут с данным VBO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	// Определяем формат данных вершин
	glVertexAttribPointer(0 /*позиция location=0*/, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0); // активация атрибута вершины с индексом 0

	// Отвязываем VAO и VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Отвязываем, т.к. он уже заполнен


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Используем шейдерную программу и отрисовываем треугольник
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	glfwTerminate();
	return 0;
}
