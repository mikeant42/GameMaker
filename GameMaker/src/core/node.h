#pragma once

#include <vector>
#include "transform.hpp"
#include <GL/glew.h>
#include "input.h"



class Camera;
class Component;

class Node
{
public:
	Node();
	~Node();

	virtual void Render(Camera *cam);
	virtual void Input(const InputData &data, float deltaTime);
	virtual void Update(float delta);

	std::vector<Node*> GetAllChildren();
	
	inline std::vector<Node*> GetChildren() {
		return children;
	}

	void AddChild(Node *node);

	inline Transform GetTransform() {
		return transform;
	}

	inline void SetTransform(const Transform &trans) {
		transform = trans;
	}

	void AddComponent(Component *comp);

	inline std::vector<Component*> GetComponents() {
		return components;
	}

protected:
	std::vector <Node*> children;
	std::vector <Component*> components;
	Transform transform = Transform();
};

