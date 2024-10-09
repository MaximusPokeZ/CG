#include <memory>
#include <vector>
#include <iostream>

#include "Window.h"
#include "Shape.h"


int main()
{
	Window window(800, 600, "OpenGL Cube");

	auto cube = std::make_shared<Cube>(0.0f, 0.0f, 0.0f, 1.0f);
	window.add_shape(cube);

	window.run();

	return 0;
}
