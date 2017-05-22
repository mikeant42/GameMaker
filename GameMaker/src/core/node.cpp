
#include "node.h"

#include "component.h"
#include "../render/camera.h"


Node::Node()
{
}

std::vector<Node*> Node::GetAllChildren() {
	std::vector<Node*> result;

	for (unsigned int i = 0; i < children.size(); i++) {
		std::vector<Node*> childObjects = children[i]->GetAllChildren();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	return result;
}

void Node::AddChild(Node *node) {
	children.push_back(node);
}

void Node::AddComponent(Component *comp) {
	components.push_back(comp);
	comp->SetParent(this);
}

void Node::Render(Camera *cam) {
	for (Component *comp : components) {
		comp->Render(cam);
	}
}
void Node::Input(const InputData &data, float deltaTime) {
	for (Component *comp : components) {
		comp->Input(data, deltaTime);
	}
}
void Node::Update(float delta) {
	for (Component *comp : components) {
		comp->Update(delta);
	}
}


Node::~Node()
{
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children[i]) {
			delete children[i];
		}
	}

	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i])
		{
			delete components[i];
		}
	}
}
