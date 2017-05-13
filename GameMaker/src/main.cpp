#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/display.h"
#include "render/shader.h"
#include "render/texture.h"
#include "core/node.h"
#include "render/camera.h"

#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool keys[1024];

int main(void) {
	DisplayManager displayManager = DisplayManager();
	displayManager.CreateDisplay();

	Shader shader = Shader("res/shader/default.vert", "res/shader/default.frag");
	Texture tex = Texture::LoadTexture("res/texture/stone005.jpg");

	Node root = Node();



	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint VBO, VAO;
	//GLuint EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

	glfwSetKeyCallback(displayManager.GetWindowPointer(), key_callback);

	//glm::mat4 model;
	//model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);

	glm::mat4 model;
	model = glm::rotate(model, (GLfloat)(glfwGetTime() * 100.0f) / 50, glm::vec3(0.5f, 1.0f, 0.0f));

	Camera *cam = new Camera();
	root.AddChild(cam);
	cam->GetTransform().SetPosition(glm::vec3(0, 0, 5));

	root.GetTransform().SetPosition(glm::vec3(0, 5, 5));

	/* Loop until the user closes the window */
	while (!displayManager.ShouldClose()) {
		displayManager.Loop();
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		for (Node *child : root.GetChildren()) { // Should be GetAllChildren()
			child->Input(keys, displayManager.GetDeltaTime());
			child->Update(displayManager.GetDeltaTime());
			child->Render();
		}

		cam->GetTransform().SetPosition(cam->GetTransform().GetPosition() + 0.5f);

		// Create transformations
		glm::mat4 view;
		view = glm::lookAt(cam->GetTransform().GetPosition(), cam->GetTransform().GetPosition()
			+ cam->GetCamFront(), cam->GetCamUp());

		glm::mat4 projection;
		projection = glm::perspective(45.0f, GLfloat(displayManager.GetWindowWidth() / displayManager.GetWindowHeight()), 0.1f, 100.0f);

		tex.Use();

		shader.Start();

		shader.SetUniform("ccolor", glm::vec3(0.2f, 0.6f, 0.8f));
		shader.SetUniform("model", model);
		shader.SetUniform("view", view);
		shader.SetUniform("projection", projection);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		shader.Stop();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) 
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}