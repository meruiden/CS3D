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
	light2->brightness = 10;
	light2->position = glm::vec3(10, 0, 0);
	light->brightness = 10;
	entity2->getDefaultMaterial()->specular = 2.0f;
	entity->getDefaultMaterial()->specular = 2.0f;
	light->position = glm::vec3(-6, 0, 0);

	camera->rotation += glm::vec3(0, 3.14f, 0);
	camera->position = glm::vec3(0, 0, -15);

	lastMouseX = Input::getMouseX();
	lastMouseY = Input::getMouseY();

	lightV = new Entity();
	lightV2 = new Entity();

	addEntity(lightV);
	addEntity(lightV2);

	unlit = new Material();
	unlitShader = new Shader();
	unlitShader->loadShader("shaders/unlit.vert", "shaders/unlit.frag");
	unlit->setShader(unlitShader);
	lightV->setMaterial(unlit);
	lightV2->setMaterial(unlit);

	lightV->setAndLoadMesh("assets/cube.obj");
	lightV2->setAndLoadMesh("assets/cube.obj");

//	lightV->position = light->position;
	lightV2->position = light2->position;

	floor = new Entity();
	floor->setAndLoadMesh("assets/floor.obj");
	addEntity(floor);
	floor->getDefaultMaterial()->setTexture("assets/white.png");
	floor->position = glm::vec3(0, -5, 0);
}


MainScene::~MainScene()
{
	delete entity;
	delete entity2;
	delete light;
	delete light2;
	delete floor;
}

void MainScene::update(float deltaTime)
{
	static float t = 0;
	t += deltaTime*3;

	float sp = 4;

	glm::vec3 forward = glm::vec3(cos(camera->rotation.y + 1.57f) * cos(camera->rotation.x), sin(camera->rotation.x), sin(camera->rotation.y - 1.57f) * cos(camera->rotation.x));
	forward = glm::normalize(forward);

	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));

	if (Input::getKey(cs3d::KeyCode::W)) {
		camera->position += forward * deltaTime * sp;
	}

	if (Input::getKey(cs3d::KeyCode::S)) {
		camera->position -= forward * deltaTime * sp;
	}

	if (Input::getKey(cs3d::KeyCode::A)) {
		camera->position -= right * deltaTime * sp;
	}

	if (Input::getKey(cs3d::KeyCode::D)) {
		camera->position += right * deltaTime * sp;
	}

	camera->rotation += glm::vec3(glm::radians(lastMouseY - Input::getMouseY()) * 0.1f, glm::radians(lastMouseX - Input::getMouseX()) * 0.1f, 0);

	lastMouseX = Input::getMouseX();
	lastMouseY = Input::getMouseY();

	entity2->rotation += glm::vec3(0, 0, 1) * deltaTime;

	if (Input::getKeyDown(cs3d::KeyCode::escape))
	{
		Input::quitApplication();
	}
}
