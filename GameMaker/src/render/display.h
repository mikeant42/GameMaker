#pragma once

#include <GL/glew.h>

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
	int width = 3000;
	int height = 1800;
	float frameSeconds;

	GLFWwindow *window;

};
/*
class WindowInput {
public:
	WindowInput();
	~WindowInput();

	GLFWkeyfun GetKeyboardCallback();
	GLFWmousebuttonfun GetMouseCallback();
	GLFWscrollfun GetScrollCallback();
	GLFWcursorposfun GetCursorCallback();
private:
	// our controls
	GLFWkeyfun keyboardCallback;
	GLFWmousebuttonfun mouseCallback;
	GLFWscrollfun scrollCallback;
	GLFWcursorposfun cursorCallback;
};
*/
