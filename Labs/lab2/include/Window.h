#ifndef LABS_WINDOW_H
#define LABS_WINDOW_H

#include "Shape.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Window final
{
public:

	Window(int width, int height, const std::string& title);

	void run();
	void add_shape(const std::shared_ptr<Shape>& shape);
	void change_projection(const int& width, const int& height, bool& transitioning, bool& is_perspective, float& transition_progress, const float& transition_speed, const float& angle);

private:

	sf::RenderWindow window;
	std::vector<std::shared_ptr<Shape>> shapes;

	float ortho_left = -2.0f;
	float ortho_right = 2.0f;
	float ortho_bottom = -2.0f;
	float ortho_top = 2.0f;
};

#endif //LABS_WINDOW_H
