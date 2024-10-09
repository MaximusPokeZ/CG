#ifndef LABS_SHAPE_H
#define LABS_SHAPE_H

#include <SFML/OpenGL.hpp>

class Shape
{
public:

	Shape(float x_, float y_, float z_);

	virtual ~Shape() = default;

	virtual void draw() const = 0;

	virtual void set_size(float size_) = 0;

protected:

	float x, y, z;
};

class Cube : public Shape
{

private:

	float size;

public:

	Cube(float x_, float y_, float z_, float size_);

	void draw () const override;

	void set_size(float size_) override;
};


#endif //LABS_SHAPE_H
