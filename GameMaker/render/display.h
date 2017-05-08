#pragma once

#include <GLFW/glfw3.h>

class DisplayManager {
public:
	//DisplayManager();
	//~DisplayManager();

	// Both static, because no resizing
	inline const int GetWindowWidth() {
		return width;
	}
	inline const int GetWindowHeight() {
		return height;
	}

	inline double GetCurrentTimeMillis() {
		return glfwGetTime() * 1000;
	}

	inline bool ShouldClose() {
		return glfwWindowShouldClose(window);
	}

	float GetFrameTimeSeconds();

	void CreateDisplay();
	void CloseDisplay();
	void Loop();

	inline GLFWwindow *GetWindowPointer() {
		return window;
	}

	
private:
	const int width = 3000;
	const int height = 1800;
	float frameSeconds;

	GLFWwindow *window;


	// our controls
	GLFWkeyfun keyboardCallback;
	GLFWkeyfun mouseCallback;
	GLFWkeyfun scrollCallback;
	GLFWkeyfun cursorCallback;
};

