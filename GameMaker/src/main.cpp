#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/display.h"
#include "render/texture.h"


#include "core/node.h"
#include "render/camera.h"
#include "render/meshrenderer.h"

#include <iostream>
#include <vector>

//class Light;

int main(void) {
	DisplayManager displayManager = DisplayManager();
	displayManager.CreateDisplay();

	Node root = Node();


	Camera *cam = new Camera();
	root.AddChild(cam);

	InputManager &input = InputManager::GetInstance();

	MeshRenderer *renderComp = new MeshRenderer("res/mesh/mitsuba.obj");

	renderComp->AddTexture(Texture::LoadTexture("res/texture/white.png"));

	renderComp->GetMaterial()->albedo = glm::vec3(0.0, 0.4, 0.4);
	renderComp->GetMaterial()->metallic = 0.9f;
	renderComp->GetMaterial()->roughness = 0.1f;

	Node *rock = new Node();
	//rock->GetTransform()->SetScale(0.5f);
	rock->AddComponent(renderComp);

	rock->GetTransform()->SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	root.AddChild(rock);

	Node *floor = new Node();

	MeshRenderer *floorRender = new MeshRenderer("res/mesh/scififloor.obj");
	floorRender->AddTexture(Texture::LoadTexture("res/texture/floor.tga"));

	floor->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	floor->GetTransform()->SetScale(5.0f);

	floor->AddComponent(floorRender);

	root.AddChild(floor);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	std::vector<Light> lights;

	Light light = Light();
	light.SetPosition(glm::vec3(1, 7, -1));
	light.SetColor(glm::vec3(255,255,255));
	lights.push_back(light);

	/* Loop until the user closes the window */
	while (!displayManager.ShouldClose()) {
		displayManager.Loop();
		/* Render here */

		glCullFace(GL_BACK);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam->CreateMatrices(displayManager.GetWindowWidth(), displayManager.GetWindowHeight());


		for (Node *child : root.GetChildren()) { // Should be GetAllChildren()
			child->Input(input.GetInputData(), displayManager.GetDeltaTime());
			child->Update(displayManager.GetDeltaTime());
			child->Render(cam, lights);
		}


	}


	//glDeleteBuffers(1, &EBO);
	
}
