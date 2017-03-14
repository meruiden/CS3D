#include <engine/renderer.h>

GLFWwindow* Renderer::window = NULL;

Renderer::Renderer()
{
	float windowWidth = 1400.0f;
	float windowHeight = 1050.0f;
	
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(windowWidth, windowHeight, "Project", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(13.0f / 255.0f, 105.0f / 255.0f, 249.0f / 255.0f, 0.0f);

	glEnable(GL_BLEND);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Projection = glm::perspective(45.0f, windowWidth / windowHeight, 0.1f, 2000.0f);
	this->deltaTime = 0;

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;

	//glShadeModel(GL_SMOOTH);

	
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	shadowFrameBuffer = 0;

	glGenFramebuffers(1, &shadowFrameBuffer);

	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


	glBindFramebuffer(GL_FRAMEBUFFER, shadowFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		glfwTerminate();
		return;
	}

	Input::init(window);
}

Renderer::~Renderer()
{
	delete Input::getInstance();
	delete ResourceManager::getInstance();
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteFramebuffers(1, &shadowFrameBuffer);
	glDeleteTextures(1, &depthTexture);

	glfwTerminate();
}

void Renderer::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Scene* currentScene = SceneManager::getCurrentScene();
		Input::update();
		if (currentScene != NULL)
		{
			calculateDeltaTime();
			currentScene->update(deltaTime);

			std::vector<Entity*> entities = currentScene->getEntities();
			int numEntities = entities.size();

			for (int i = 0; i < numEntities; i++)
			{
				
				glm::mat4 Model = getModelMatrix(entities[i]->position, entities[i]->scale, entities[i]->rotation);
				// Our ModelViewProjection : multiplication of our 3 matrices
				glm::mat4 MVP = Projection * currentScene->getCamera()->getViewMatrix() *Model; // Remember, matrix multiplication is the other way around

				Material* m = NULL;
				m = entities[i]->getMaterial();
				if (m == NULL)
				{
					m = entities[i]->getDefaultMaterial();
				}

				renderMesh(entities[i]->getMesh(), MVP, Model, m, currentScene->getLights(), currentScene->getCamera());

			}
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}
}

void Renderer::renderMesh(Mesh * mesh, glm::mat4 MVP, glm::mat4 model, Material* material, std::vector<Light*> lights, Camera* camera)
{
	glUseProgram(material->getShader()->getProgramId());

	material->passToShader();
	glUniformMatrix4fv(glGetUniformLocation(material->getShader()->getProgramId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(material->getShader()->getProgramId(), "model"), 1, GL_FALSE, &model[0][0]);

	MeshData meshData = mesh->getMeshData();

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, meshData.vertexBuffer);
	glVertexAttribPointer(
		0,  // The attribute we want to configure
		3,                            // size
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, meshData.uvBuffer);
	glVertexAttribPointer(
		1,                   // The attribute we want to configure
		2,                            // size : U+V => 2
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, meshData.normalBuffer);
	glVertexAttribPointer(
		2,    // The attribute we want to configure
		3,                            // size
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);
	
	glUniform3fv(glGetUniformLocation(material->getShader()->getProgramId(), "viewPos"), 1, &camera->position[0]);

	renderLighting(lights, material->getShader());

	glDrawArrays(GL_TRIANGLES, 0, meshData.numVerts);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);


}

void Renderer::renderLighting(std::vector<Light*> lights, Shader* shader)
{
	glUniform1i(glGetUniformLocation(shader->getProgramId(), "numLights"), lights.size());

	for (int i = 0; i < lights.size(); i++)
	{
		std::stringstream indexString;
		indexString << i;
		glUniform3f(glGetUniformLocation(shader->getProgramId(), ("pointLights[" + indexString.str() + "].position").c_str()), lights[i]->position.x, lights[i]->position.y, lights[i]->position.z);
		glUniform3f(glGetUniformLocation(shader->getProgramId(), ("pointLights[" + indexString.str() + "].color").c_str()), lights[i]->color.x, lights[i]->color.y, lights[i]->color.z);
		glUniform1f(glGetUniformLocation(shader->getProgramId(), ("pointLights[" + indexString.str() + "].brightness").c_str()), lights[i]->brightness);
	}
}

glm::mat4 Renderer::getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
	// Build the Model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::orientate3(rotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

	return mm;
}

void Renderer::calculateDeltaTime()
{
	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	deltaTime = startTime - lastTime;
	lastTime = startTime;
}
