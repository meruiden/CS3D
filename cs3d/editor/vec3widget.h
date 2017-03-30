#pragma once

#include <glm/glm.hpp>

#include <FL/Fl_Box.H>
#include <FL/Fl_Spinner.H>

class Vec3Widget : Fl_Widget
{
public:
	Vec3Widget(int x, int y, int w, int h, const char* label);
	virtual ~Vec3Widget();

	float x() { return xVal->value(); }
	float y() { return yVal->value(); }
	float z() { return zVal->value(); }

	void set(glm::vec3 newVal);
	glm::vec3 get() { return glm::vec3(x(), y(), z()); }

private:
	Fl_Spinner* xVal;
	Fl_Spinner* yVal;
	Fl_Spinner* zVal;

	void draw() {}
};

