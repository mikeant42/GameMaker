#pragma once

#include <GL/glew.h>
#include "input.h"
#include "../render/shader.h"

#include "node.h"
#include "../render/camera.h"

class Node;

class Component {
public:
	Component() {}
	~Component() {}

	virtual void Input(const InputData &data, float deltaTime) {}
	virtual void Update(float deltaTime) {}
	virtual void Render(Camera *cam) {}

	inline void SetParent(Node *node) {
		parent = node;
	}

	inline Node *GetParent() {
		return parent;
	}

private:
	Node *parent;

	Component(const Component &other) {}
	void operator=(const Component &other) {}
};