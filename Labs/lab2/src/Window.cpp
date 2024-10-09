#include "Window.h"

Window::Window(int width, int height, const std::string &title) :
		window(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24))
		{
			window.setActive();
			glEnable(GL_DEPTH_TEST);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		}

void Window::run()
{
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
				glViewport(0, 0, event.size.width, event.size.height);

			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (const auto& shape : shapes)
		{
			shape->draw();
		}

		window.display(); // Отображаем изменения
	}
}

void Window::add_shape(const std::shared_ptr<Shape>& shape)
{
	shapes.push_back(shape);
}