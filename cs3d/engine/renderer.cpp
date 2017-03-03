#include <engine/renderer.h>

Renderer::Renderer()
{
	float windowWidth = 1400.0f;
	float windowHeight = 1050.0f;
	
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayID);
	delete Input::getInstance();
	glfwTerminate();
}

void Renderer::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Scene* currentScene = SceneManager::getCurrentScene();
		if (currentScene != NULL)
		{
			calculateDeltaTime();
			currentScene->update(deltaTime);

			std::vector<Entity*> entities = currentScene->getEntities();
			int numEntities = entities.size();

			for (int i = 0; i < numEntities; i++)
			{
				glm::mat4 View = glm::lookAt(
					glm::vec3(0, 0, 10), // Camera is at (4,3,3), in World Space
					glm::vec3(0, 0, 0), // and looks at the origin
					glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
				);

				// Model matrix : an identity matrix (model will be at the origin)
				glm::mat4 Model = getModelMatrix(entities[i]->position, entities[i]->scale, entities[i]->rotation);
				// Our ModelViewProjection : multiplication of our 3 matrices
				glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

				Material* m = NULL;
				m = entities[i]->getMaterial();
				if (m == NULL)
				{
					m = entities[i]->getDefaultMaterial();
				}

				renderMesh(entities[i]->getMesh(), MVP, Model, m, currentScene->getLights());

			}
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void Renderer::renderMesh(Mesh * mesh, glm::mat4 MVP, glm::mat4 model, Material* material, std::vector<Light*> lights)
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

	glUniform3f(glGetUniformLocation(material->getShader()->getProgramId(), "viewPos"), 0, 0, 10);

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
