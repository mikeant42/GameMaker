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
#include "render/rendercomponent.h"

#include <iostream>

int main(void) {
	DisplayManager displayManager = DisplayManager();
	displayManager.CreateDisplay();

	Node root = Node();

	//glm::mat4 model;
	//model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);

	Camera *cam = new Camera();
	root.AddChild(cam);

	InputManager &input = InputManager::GetInstance();

	RenderComponent *renderComp = new RenderComponent("res/mesh/nanosuit.obj");

	//renderComp->AddTexture(Texture::LoadTexture("res/texture/stone005.jpg"));

	Node *rock = new Node();
	//rock->GetTransform().SetScale(0.0000008f);
	rock->AddComponent(renderComp);

	root.AddChild(rock);
	

	/* Loop until the user closes the window */
	while (!displayManager.ShouldClose()) {
		displayManager.Loop();
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam->CreateMatrices(displayManager.GetWindowWidth(), displayManager.GetWindowHeight());


		for (Node *child : root.GetChildren()) { // Should be GetAllChildren()
			child->Input(input.GetInputData(), displayManager.GetDeltaTime());
			child->Update(displayManager.GetDeltaTime());
			child->Render(cam);
		}


	}


	//glDeleteBuffers(1, &EBO);
	
}
