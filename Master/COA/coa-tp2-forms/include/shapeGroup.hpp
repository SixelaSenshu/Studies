#ifndef __SHAPEG_H__
#define __SHAPEG_H__

#include "shape.hpp"
#include <vector>

class ShapeGroup{
public:

	vector<Shape *> sel_shapes;

	ShapeGroup();

	void move(int x, int y);

	void add( Shape *s);

	void remove( Shape *s);

	bool is_in_group(Shape *s);

	virtual ~ShapeGroup();
};

#endif