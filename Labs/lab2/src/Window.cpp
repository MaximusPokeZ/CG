#include "Window.h"

void Window::change_projection(const int& width, const int& height, bool& transitioning, bool& is_perspective, float& transition_progress, const float& transition_speed, const float& angle)
{
	float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);

	if (transitioning)
	{
		if (is_perspective)
		{
			transition_progress += transition_speed;
			if (transition_progress >= 1.0f)
			{
				transition_progress = 1.0f;
				transitioning = false;
			}
		}
		else
		{
			transition_progress -= transition_speed;
			if (transition_progress <= 0.0f)
			{
				transition_progress = 0.0f;
				transitioning = false;
			}
		}
	}

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if (transition_progress < 1.0f && !is_perspective)
	{
		float mix_left = ortho_left * aspect_ratio * (1.0f - transition_progress);
		float mix_right = ortho_right * aspect_ratio * (1.0f - transition_progress);
		float mix_bottom = ortho_bottom * (1.0f - transition_progress);
		float mix_top = ortho_top * (1.0f - transition_progress);

		glOrtho(mix_left, mix_right, mix_bottom, mix_top, 0.1f, 100.0f);
	}
	else if(is_perspective)
	{
		gluPerspective(angle, aspect_ratio, 0.1f, 100.0f);
	}

	glMatrixMode(GL_MODELVIEW);
}

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
	bool is_perspective = true, transitioning = false;
	float transition_progress = 1.0f;
	float transition_speed = 0.002f;

	bool is_rotating = false;
	float rotation_angle = 45.0f, view_angle = 45.0f;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width,
						   event.size.height); // наша область для рисования теперь от (0, 0) до (new_w, new_h)

				change_projection(event.size.width, event.size.height, transitioning, is_perspective, transition_progress, transition_speed, view_angle);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::S)
					is_rotating = !is_rotating;
				else if (event.key.code == sf::Keyboard::P)
				{
					is_perspective = true;
					transitioning = true;
				}
				else if (event.key.code == sf::Keyboard::O && is_perspective)
				{
					is_perspective = false;
					transitioning = true;
				}
				else if (event.key.code == sf::Keyboard::B)
				{
					++view_angle;
				}
				else if (event.key.code == sf::Keyboard::N)
				{
					--view_angle;
				}
				else if (event.key.code == sf::Keyboard::Equal)
				{
					ortho_left *= 1.1f;
					ortho_right *= 1.1f;
					ortho_bottom *= 1.1f;
					ortho_top *= 1.1f;
				}
				else if (event.key.code == sf::Keyboard::Hyphen)
				{
					ortho_left *= 0.9f;
					ortho_right *= 0.9f;
					ortho_bottom *= 0.9f;
					ortho_top *= 0.9f;
				}
			}
		}

		change_projection(window.getSize().x, window.getSize().y, transitioning, is_perspective, transition_progress, transition_speed, view_angle);

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