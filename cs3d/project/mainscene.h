#pragma once

#include <engine/cs3d.h>

class MainScene : public Scene
{
public:
	MainScene();
	virtual ~MainScene();
	virtual void update(float deltaTime);
private:
	Entity* entity;
	Entity* entity2;
	Light* light;
	Light* light2;

	Entity* lightV;
	Entity* lightV2;

	Entity* floor;

	Material* unlit;
	Shader* unlitShader;

	float lastMouseX;
	float lastMouseY;
};

