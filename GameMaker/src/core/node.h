#pragma once

#include <vector>
#include "transform.h"

class Node
{
public:
	Node();
	~Node();

	virtual void Render();
	virtual void Input(bool keys[], float deltaTime);
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

protected:
	std::vector <Node*> children;
	Transform transform = Transform();
};

