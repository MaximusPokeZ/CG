#include <memory>


#include "Window.h"


int main()
{
	Window window(800, 600, "OpenGL Cube");

	auto cube = std::make_shared<Cube>(0.0f, 0.0f, 0.0f, 1.5);
	window.add_shape(cube);

	window.run();



	return 0;
}
