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


	Camera *cam = new Camera();
	root.AddChild(cam);

	InputManager &input = InputManager::GetInstance();

	RenderComponent *renderComp = new RenderComponent("res/mesh/bunny.obj");

	renderComp->AddTexture(Texture::LoadTexture("res/texture/white.png"));

	Node *rock = new Node();
	rock->GetTransform().SetScale(0.05f);
	rock->AddComponent(renderComp);

	rock->GetTransform().SetPosition(glm::vec3(-1.0f, -5.0f, -1.0f));

	root.AddChild(rock);
	
	glEnable(GL_DEPTH_TEST);

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
