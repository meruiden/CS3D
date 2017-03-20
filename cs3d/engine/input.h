#pragma once

#include <GLFW/glfw3.h>

#include <engine/keycode.h>

class Input
{
public:
	static Input* getInstance();
	~Input();
	
	static void update();
	static void quitApplication();
	static void init(GLFWwindow* window);

	static bool getKey(cs3d::KeyCode keyCode);
	static bool getKeyDown(cs3d::KeyCode keyCode);
	static bool getKeyUp(cs3d::KeyCode keyCode);
	static bool getMouse(int button);
	static bool getMouseDown(int button);
	static bool getMouseUp(int button);

	static void handleKey(GLFWwindow * window, int key, int scancode, int action, int mode);
	static void handleMouse(GLFWwindow * window, int button, int action, int mode);
	static void handleMousePosition(GLFWwindow* window, double xpos, double ypos);

	static float getMouseX() { return Input::getInstance()->mouseX; }
	static float getMouseY() { return Input::getInstance()->mouseY; }
private:
	Input();
	static Input* instance;

	bool keys[GLFW_KEY_LAST];
	bool keysUp[GLFW_KEY_LAST];
	bool keysDown[GLFW_KEY_LAST];

	bool mouse[GLFW_MOUSE_BUTTON_LAST];
	bool mouseUp[GLFW_MOUSE_BUTTON_LAST];
	bool mouseDown[GLFW_MOUSE_BUTTON_LAST];

	GLFWwindow* window;

	float mouseX;
	float mouseY;
};
