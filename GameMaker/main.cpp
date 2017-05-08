#include <GLFW/glfw3.h>
#include "render/display.h"

int main(void) {

	DisplayManager displayManager = DisplayManager();
	displayManager.CreateDisplay();

	/* Loop until the user closes the window */
	while (!displayManager.ShouldClose()) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		displayManager.Loop();
	}
	
}