#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <limits>

void draw_circle(int center_x, int center_y, int radius)
{
	glBegin(GL_POINTS); // говорим OpenGL, что будем рисовать точки
	int x = 0;
	int y = radius;
	int d = 1 - radius;

	while (x <= y) // рисуем до четверти (используем симметрию)
	{
		glVertex2i(center_x + x, center_y + y);
		glVertex2i(center_x - x, center_y + y);
		glVertex2i(center_x + x, center_y - y);
		glVertex2i(center_x - x, center_y - y);
		glVertex2i(center_x + y, center_y + x);
		glVertex2i(center_x - y, center_y + x);
		glVertex2i(center_x + y, center_y - x);
		glVertex2i(center_x - y, center_y - x);

		if (d < 0)
		{
			d = d + 2 * x + 1;
		}
		else // выходим за окружность --> уменьшить y
		{
			d = d + 2 * (x - y) + 2;
			y--;
		}
		x++; // переход к следующему пикселю по x
	}
	glEnd();
}

int main()
{
	int radius, add_pulse_radius = 0;
	bool pulse = false, increase = true;

	while (true)
	{
		std::cout << "Enter the radius of rhe circle: ";
		std::cin >> radius;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "Invalid input. Enter a valid integer.\n";
		}
		else if (radius < 0 || radius > 400)
		{
			std::cout << "Radius out of range\n";
		}
		else break;
	}


	sf::Window window(sf::VideoMode(800, 600), "Bresenham Circle", sf::Style::Close);
	window.setActive(true);
	glOrtho(0, 800, 600, 0, -1, 1); // Установка ортографической проекции от (0, 0) до (800, 600)

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Equal) radius += 5;
				if (event.key.code == sf::Keyboard::Hyphen) radius = std::max(0, radius - 5);

				if (event.key.code == sf::Keyboard::P)
				{
					pulse = !pulse;
					if (!pulse)
					{
						add_pulse_radius = 0;
					}
				}
			}
		}

		if (pulse)
		{
			if (increase)
			{
				++add_pulse_radius;
				if (add_pulse_radius >= 20) increase = false;
			}
			else
			{
				--add_pulse_radius;
				if (add_pulse_radius <= 0) increase = true;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		draw_circle(400, 300, radius + add_pulse_radius);
		window.display();
	}

	return 0;
}
