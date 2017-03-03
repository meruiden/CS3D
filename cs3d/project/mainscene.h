#pragma once
#include <engine/defaultmaterial.h>
#include <engine/shader.h>
#include <engine/scene.h>
#include <engine/light.h>
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
};

