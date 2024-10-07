#ifndef LABS_SHAPE_H
#define LABS_SHAPE_H

class Shape
{
public:

	Shape(float cord_x_ = 0.0f, float cord_y_ = 0.0f, float cord_z_ = 0.0f);
	virtual ~Shape();

	virtual void draw();
	void set_cord(float new_x, float new_y, float new_z);

private:

	float cord_x, cord_y, cord_z;
};


#endif //LABS_SHAPE_H
