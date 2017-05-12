#pragma once

#include <vector>
#include "transform.h"

class Node
{
public:
	Node();
	~Node();

	void Render();

	Transform GetTransform() {
		return transform;
	}

private:
	std::vector <Node*> children;
	Transform transform;
};

