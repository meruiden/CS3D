#pragma once

#include <map>
#include <string>

#include <engine/scene.h>

class SceneManager
{
public:
	static void loadScene(std::string sceneName);
	static void addScene(std::string sceneName, Scene* scene);
	static Scene* getCurrentScene() { return SceneManager::getInstance()->currentScene; }
	static Scene* getScene(std::string sceneName) { return SceneManager::getInstance()->scenes[sceneName]; }
	static SceneManager* getInstance();
private:
	std::map<std::string, Scene*> scenes;
	Scene* currentScene;
	static SceneManager* instance;

};

