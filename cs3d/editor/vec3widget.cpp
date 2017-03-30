#include <editor/vec3widget.h>

Vec3Widget::Vec3Widget(int x, int y, int w, int h, const char* label) : Fl_Widget(x, y, w, h)
{

	new Fl_Box(x, y, 50, 30, label);
	xVal = new Fl_Spinner(x + 10, y + 30, w, h, "x");
	yVal = new Fl_Spinner(x + w + 30, y + 30, w, h, "y");
	zVal = new Fl_Spinner(x + w * 2 + 50, y + 30, w, h, "z");

	xVal->range(-INT_MAX, INT_MAX);
	yVal->range(-INT_MAX, INT_MAX);
	zVal->range(-INT_MAX, INT_MAX);

	xVal->step(0.5f);
	yVal->step(0.5f);
	zVal->step(0.5f);

	xVal->value(0);
	yVal->value(0);
	zVal->value(0);
}


Vec3Widget::~Vec3Widget()
{
}

void Vec3Widget::set(glm::vec3 newVal)
{
	xVal->value(newVal.x);
	yVal->value(newVal.y);
	zVal->value(newVal.z);
}
