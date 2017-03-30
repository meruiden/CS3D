#pragma once

#include <vector>
#include <stdarg.h>
#include <sstream>

#include <editor/crossplatformtools.h>

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Sys_Menu_Bar.H>

#include <editor/vec3widget.h>

#include <manymouse.h>

#include <engine/cs3d.h>

class EditorRenderer : Fl_Gl_Window
{
public:
	EditorRenderer();
	~EditorRenderer();

	void run();
	
	Scene* getScene() { return editorScene; }
private:
	void draw();
	void init();
	void calculateDeltaTime();
	void handleCamera();
	static void resetObj(Fl_Widget*, void *data);
	static void onQuit(Fl_Widget*, void*);

	int handle(int e);

	Scene* editorScene;

	Renderer* engineRenderer;

	Fl_Window * mainWindow;
	Fl_Button* button;
	Fl_Sys_Menu_Bar* menuBar;
	Vec3Widget* positionWidget;
	Vec3Widget* scaleWidget;
	Vec3Widget* rotationWidget;


	Light* light;
	Entity* entity;

	Material* unlitMaterial;
	Shader* unlitShader;
	ManyMouseEvent manyMouseEvent;

	static bool quit;
	bool doneInit;
	bool dragging;

	int lockedMouseX, lockedMouseY;
	int mouseVelX, mouseVelY;

	double deltaTime;

	glm::mat4 projection;
	void setCursorPositionWindow(int x, int y);
	void updateMouseVelocity();
	
};

