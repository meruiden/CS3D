#include <project/mainscene.h>

MainScene::MainScene() : Scene()

{
	entity = new Entity();
	entity->setAndLoadMesh("assets/m4a1.obj");

	entity2 = new Entity();
	entity2->setAndLoadMesh("assets/dragon.obj");

	entity->scale = glm::vec3(0.2f, 0.2f, 0.2f);
	entity->position = glm::vec3(-1.5f, -2, 0);
	entity2->position = glm::vec3(3, -4, -3);
	addEntity(entity);
	addEntity(entity2);
	entity->getDefaultMaterial()->setTexture("assets/m4a1.png");
	entity2->getDefaultMaterial()->setTexture("assets/white.png");
	light = new Light();
	light2 = new Light();
	addLight(light2);
	addLight(light);

	light2->color = glm::vec3(1, 0, 0);
	light2->brightness = 3;
	light2->position = glm::vec3(6, 0, 0);
	light->brightness = 7.0f;
	entity2->getDefaultMaterial()->specular = 3.0f;
	entity->getDefaultMaterial()->specular = 4.0f;
	light->position = glm::vec3(-3, 0, 0);
}


MainScene::~MainScene()
{
	delete entity;
	delete entity2;
	delete light;
	delete light2;
}

void MainScene::update(float deltaTime)
{
	static float t = 0;
	t += deltaTime*3;
	entity->rotation += glm::vec3(1, 0, 2) * deltaTime;
	entity2->rotation += glm::vec3(0, 0, 1) * deltaTime;

	if (Input::getKeyDown(KeyCode::Escape))
	{
		Input::quitApplication();
	}
}
