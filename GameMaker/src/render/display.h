#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "../core/input.h"

class DisplayManager {
public:
	//DisplayManager();
	//~DisplayManager();

	// Both const, because no resizing
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

	inline float GetDeltaTime() {
		return deltaTime;
	}

	void CreateDisplay();
	void CloseDisplay();
	void Loop();

	inline GLFWwindow *GetWindowPointer() {
		return window;
	}
	
private:
	int width = 3000;
	int height = 1800;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f;  	// Time of last frame

	float nbFrames = 0;

	GLFWwindow *window;

	InputManager &input = InputManager::GetInstance();

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
