#include <editor/editorrenderer.h>

bool EditorRenderer::quit = false;

EditorRenderer::EditorRenderer() : Fl_Gl_Window(0, 50, 900, 800)
{
	end();

	if (ManyMouse_Init() < 0)
	{
		printf("Error initializing ManyMouse!\n");
		ManyMouse_Quit();
	}

	mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3 | FL_ALPHA | FL_DEPTH | FL_STENCIL);

	dragging = false;
	doneInit = false;
	deltaTime = 0;

	mainWindow = new Fl_Window(1400, 1050);
	menuBar = new Fl_Sys_Menu_Bar(0, 0, 1400, 50);

	mainWindow->add(this);
	mainWindow->resizable(mainWindow);
	mainWindow->label("CS3D Editor");

	button = new Fl_Button(900 + 10, y() + 10, 100, 50, "Change obj\nand/or texture");

	positionWidget = new Vec3Widget(900 + 10, y() + 70, 100, 30, "Position");
	scaleWidget = new Vec3Widget(900 + 10, y() + 150, 100, 30, "Scale");
	rotationWidget = new Vec3Widget(900 + 10, y() + 230, 100, 30, "Rotation");

	scaleWidget->set(glm::vec3(1.0f));

	mainWindow->callback(onQuit);
	mainWindow->end();

	lockedMouseX = 0;
	lockedMouseY = 0;
	mouseVelX = 0;
	mouseVelY = 0;


	mainWindow->show();

	projection = glm::perspective(45.0f, 900.0f / 800.0f, 0.1f, 2000.0f);
}


EditorRenderer::~EditorRenderer()
{
	std::vector<Entity*> entities = editorScene->getEntities();

	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}

	std::vector<Light*> lights = editorScene->getLights();

	for (int i = 0; i < lights.size(); i++)
	{
		delete lights[i];
	}

	delete editorScene;
	delete engineRenderer;
	delete unlitMaterial;
	delete unlitShader;
	ManyMouse_Quit();
}

void EditorRenderer::calculateDeltaTime()
{
	double milis = getMiliSeconds() / 1000.0f;

	static double lastTime = milis;
	double startTime = milis;
	deltaTime = startTime - lastTime;
	lastTime = startTime;
}

void EditorRenderer::handleCamera()
{
	
	if (dragging)
	{
		editorScene->getCamera()->rotation += glm::vec3(glm::radians((float)mouseVelX) * 0.07f, glm::radians((float)mouseVelY) * 0.07f, 0);
		setCursorPosition(lockedMouseX, lockedMouseY);

		float sp = 4;

		glm::vec3 forward = glm::vec3(cos(editorScene->getCamera()->rotation.y + 1.57f) * cos(editorScene->getCamera()->rotation.x),
			sin(editorScene->getCamera()->rotation.x),
			sin(editorScene->getCamera()->rotation.y - 1.57f) *
			cos(editorScene->getCamera()->rotation.x));

		forward = glm::normalize(forward);

		glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));

		if (Fl::event_key('W'))
		{
			editorScene->getCamera()->position += forward * deltaTime * sp;
		}

		if (Fl::event_key('S'))
		{
			editorScene->getCamera()->position -= forward * deltaTime * sp;
		}

		if (Fl::event_key('A'))
		{
			editorScene->getCamera()->position -= right * deltaTime * sp;
		}

		if (Fl::event_key('D'))
		{
			editorScene->getCamera()->position += right * deltaTime * sp;
		}
	}
}

void EditorRenderer::resetObj(Fl_Widget*, void *data)
{
	Entity* e = ((Entity*)data);

	Fl_Native_File_Chooser fnfc;
	fnfc.title("Pick a obj");
	fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fnfc.filter("Obj file\t*.obj");
	fnfc.directory("assets");

	switch (fnfc.show())
	{
	case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;
	case  1: printf("CANCEL\n");                      break;
	default:
		printf("PICKED: %s\n", fnfc.filename());
		e->setAndLoadMesh(fnfc.filename());
		break;
	}

	fnfc.title("Pick a texture");
	fnfc.filter("PNG file\t*.png");

	switch (fnfc.show())
	{
	case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;
	case  1: printf("CANCEL\n");                      break;
	default:
		printf("PICKED: %s\n", fnfc.filename());
		e->getDefaultMaterial()->setTexture(fnfc.filename());
		break;
	}
}

int EditorRenderer::handle(int e)
{
	int ret = Fl_Gl_Window::handle(e);

	if (e == FL_PUSH && Fl::event_button() == 3)
	{
		dragging = true;
		lockedMouseX = Fl::event_x_root();
		lockedMouseY = Fl::event_y_root();
		mainWindow->cursor(FL_CURSOR_NONE);

	}
	else if (e == FL_RELEASE && Fl::event_button() == 3)
	{
		dragging = false;
		mainWindow->cursor(FL_CURSOR_DEFAULT);
	}


	return ret;
}


void EditorRenderer::draw()
{
	if (!doneInit)
	{
		init();
		doneInit = true;
	}
	calculateDeltaTime();
	updateMouseVelocity();

	handleCamera();

	entity->position = positionWidget->get();
	entity->scale = scaleWidget->get();
	entity->rotation = rotationWidget->get() * (3.1415f / 180.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	projection = glm::perspective(45.0f, (float)w() / h(), 0.1f, 2000.0f);
	glViewport(0, 0, w(), h());

	std::vector<Entity*> entities = editorScene->getEntities();
	for (int i = 0; i < entities.size(); i++)
	{
		Entity* e = entities[i];
		glm::mat4 model = Renderer::getModelMatrix(e->position, e->scale, e->rotation);
		glm::mat4 MVP = projection * editorScene->getCamera()->getViewMatrix() * model;

		engineRenderer->renderMesh(e->getMesh(), MVP, model, e->getMaterial(), editorScene->getLights(), editorScene->getCamera());
	}
}

void EditorRenderer::init()
{
	make_current();

	engineRenderer = new Renderer(false);
	engineRenderer->initGL();

	editorScene = new Scene();

	entity = new Entity();
	button->callback(resetObj, (void*)entity);
	menuBar->add("File/Change OBJ", "", resetObj, entity);
	menuBar->redraw();
	editorScene->addEntity(entity);

	entity->position = glm::vec3(10, 0, -20);
	entity->rotation = glm::vec3(0, 0, -3.14f / 2.0f);
	entity->scale = glm::vec3(0.3f);

	entity->setAndLoadMesh("assets/m4a1.obj");
	entity->getDefaultMaterial()->setTexture("assets/m4a1.png");
	entity->getDefaultMaterial()->specular = 3;

	light = new Light();
	light->brightness = 8;
	light->position = glm::vec3(7, 3, -18);
	editorScene->addLight(light);

	unlitMaterial = new Material();
	unlitShader = new Shader();
	unlitShader->loadShader("shaders/unlit.vert", "shaders/unlit.frag");

	unlitMaterial->setShader(unlitShader);

	Entity* lightVisual = new Entity();
	lightVisual->setAndLoadMesh("assets/cube.obj");
	lightVisual->setMaterial(unlitMaterial);

	editorScene->addEntity(lightVisual);
	lightVisual->position = light->position;
}

void EditorRenderer::run()
{
	while (!quit)
	{
		Fl::wait(0.0f);

		redraw();
	}
}

void EditorRenderer::onQuit(Fl_Widget*, void*)
{
	if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape)
		return;

	if (fl_choice("Are you sure you want to quit?", "Yes", "No", 0) == 1)
		return;

	EditorRenderer::quit = true;
}

void EditorRenderer::setCursorPositionWindow(int x, int y)
{
	x += mainWindow->x();
	y += mainWindow->y();

	setCursorPosition(x, y);
}

void EditorRenderer::updateMouseVelocity()
{
	mouseVelX = 0;
	mouseVelY = 0;
	while (ManyMouse_PollEvent(&manyMouseEvent))
	{
		if (manyMouseEvent.type == MANYMOUSE_EVENT_RELMOTION)
		{
			if (manyMouseEvent.item == 1)
			{
				mouseVelX = -manyMouseEvent.value;
			}
			else if (manyMouseEvent.item == 0)
			{
				mouseVelY = -manyMouseEvent.value;
			}

		}
	}
}
