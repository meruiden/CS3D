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

	static bool getKey(KeyCode keyCode);
	static bool getKeyDown(KeyCode keyCode);
	static bool getKeyUp(KeyCode keyCode);
	static bool getMouse(int button);
	static bool getMouseDown(int button);
	static bool getMouseUp(int button);

	static void handleKey(GLFWwindow * window, int key, int scancode, int action, int mode);
	static void handleMouse(GLFWwindow * window, int button, int action, int mode);
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
};
