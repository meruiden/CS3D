#pragma once

#include <map>
#include <string>

#include <engine/scene.h>

class SceneManager
{
public:
	static void loadScene(std::string sceneName);
	static void addScene(std::string sceneName, Scene* scene);
	static Scene* getCurrentScene() { return SceneManager::currentScene; }
	static Scene* getScene(std::string sceneName) { return SceneManager::scenes[sceneName]; }
private:
	static std::map<std::string, Scene*> scenes;
	static Scene* currentScene;

};

