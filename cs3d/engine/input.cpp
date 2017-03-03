#include <engine/input.h>

Input* Input::instance = NULL;

Input::Input()
{
}


Input * Input::getInstance()
{
	if (instance == NULL)
	{
		instance = new Input();
	}

	return instance;
}

Input::~Input()
{
}
