#include <engine/input.h>

Input* Input::instance = NULL;

Input::Input()
{
	for (unsigned int i = 0; i< GLFW_KEY_LAST; i++)
	{
		keys[i] = false;
		keysUp[i] = false;
		keysDown[i] = false;
	}
	for (unsigned int i = 0; i< GLFW_MOUSE_BUTTON_LAST; i++)
	{
		mouse[i] = false;
		mouseUp[i] = false;
		mouseDown[i] = false;
	}
	
	mouseX = 0;
	mouseY = 0;
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

void Input::update()
{
	for (unsigned int i = 0; i< GLFW_KEY_LAST; i++)
	{
		Input::getInstance()->keysUp[i] = false;
		Input::getInstance()->keysDown[i] = false;
	}
	for (unsigned int i = 0; i< GLFW_MOUSE_BUTTON_LAST; i++)
	{
		Input::getInstance()->mouseUp[i] = false;
		Input::getInstance()->mouseDown[i] = false;
	}

	glfwPollEvents();
}

void Input::quitApplication()
{
	glfwSetWindowShouldClose(Input::getInstance()->window, GLFW_TRUE);
}

void Input::init(GLFWwindow * window)
{
	Input::getInstance()->window = window;

	glfwSetKeyCallback(window, Input::handleKey);
	glfwSetMouseButtonCallback(window, Input::handleMouse);
	glfwSetCursorPosCallback(window, Input::handleMousePosition);
}

bool Input::getKey(cs3d::KeyCode keyCode)
{
	return Input::getInstance()->keys[keyCode];
}

bool Input::getKeyDown(cs3d::KeyCode keyCode)
{
	return Input::getInstance()->keysDown[keyCode];
}

bool Input::getKeyUp(cs3d::KeyCode keyCode)
{
	return Input::getInstance()->keysUp[keyCode];
}

bool Input::getMouse(int button)
{
	return Input::getInstance()->mouse[button];
}

bool Input::getMouseDown(int button)
{
	return Input::getInstance()->mouseDown[button];
}

bool Input::getMouseUp(int button)
{
	return Input::getInstance()->mouseUp[button];
}

void Input::handleKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key <= GLFW_KEY_LAST)
	{
		if (action == GLFW_PRESS)
		{
			Input::getInstance()->keys[key] = true;
			Input::getInstance()->keysDown[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Input::getInstance()->keys[key] = false;
			Input::getInstance()->keysUp[key] = true;
		}
	}
}

void Input::handleMouse(GLFWwindow * window, int button, int action, int mode)
{
	if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST)
	{
		if (action == GLFW_PRESS)
		{
			Input::getInstance()->mouse[button] = true;
			Input::getInstance()->mouseDown[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Input::getInstance()->mouse[button] = false;
			Input::getInstance()->mouseUp[button] = true;
		}
	}
}

void Input::handleMousePosition(GLFWwindow * window, double xpos, double ypos)
{
	Input::getInstance()->mouseX = (float)xpos;
	Input::getInstance()->mouseY = (float)ypos;
}
