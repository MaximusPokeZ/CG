#include "Window.h"

Window::Window(int width, int height, const std::string &title) :
		window(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24))
		{
			window.setActive();
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

//			glm::mat4 view;
//			glm::mat4 projection;
//			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//			projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
			glMatrixMode(GL_MODELVIEW);
		}

void Window::run()
{
	bool is_rotating = false;
	float rotation_angle = 45.0f;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height); // наша область для рисования теперь от (0, 0) до (new_w, new_h)

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				float aspect_ratio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
				gluPerspective(45.0f, aspect_ratio, 0.1f, 100.0f);
				glMatrixMode(GL_MODELVIEW);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{
				is_rotating = !is_rotating;
			}
		}

		if (is_rotating)
		{
			rotation_angle += 0.01f;
			if (rotation_angle > 360.0f)
			{
				rotation_angle -= 360.0f;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (const auto& shape : shapes)
		{
			shape->draw(rotation_angle);
		}

		window.display();
	}
}

void Window::add_shape(const std::shared_ptr<Shape>& shape)
{
	shapes.push_back(shape);
}