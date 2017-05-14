#pragma once

#include <GLFW/glfw3.h>

struct InputData {
	bool keys[1024];
	double mousePosX, mousePosY;
	double scrollOffsetX, scrollOffsetY;
};

class InputManager
{
public:
	static InputManager &GetInstance() {
		static InputManager instance;
		return instance;
	}

	inline static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		GetInstance().key_callback_fun(window, key, scancode, action, mode);
	}

	inline void key_callback_fun(GLFWwindow* window, int key, int scancode, int action, int mode) {
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
				data.keys[key] = true;
			else if (action == GLFW_RELEASE)
				data.keys[key] = false;
		}
	}

	inline static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		GetInstance().mouse_callback_real(window, xpos, ypos);
	}

	inline void mouse_callback_real(GLFWwindow* window, double xpos, double ypos) {
		data.mousePosX = xpos;
		data.mousePosY = ypos;
	}

	inline InputData GetInputData() {
		return data;
	}

private:

	InputData data;

	InputManager(void) {};
	InputManager(InputManager const&) {};
	void operator=(InputManager const&) {} ; // prevent assignments
};


