#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "render/display.h"
#include "render/shader.h"

int main(void) {
	DisplayManager displayManager = DisplayManager();
	displayManager.CreateDisplay();

	Shader shader = Shader("res/shader/default.vert", "default.frag");

	/* Loop until the user closes the window */
	while (!displayManager.ShouldClose()) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		displayManager.Loop();
	}
	
}