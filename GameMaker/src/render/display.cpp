#include "display.h"

void DisplayManager::CreateDisplay() {
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// ini glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		//std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}

	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	InputManager &input = InputManager::GetInstance();

	glfwSetKeyCallback(window, InputManager::key_callback);
	glfwSetCursorPosCallback(window, InputManager::mouse_callback);
}

void DisplayManager::Loop() {

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}




