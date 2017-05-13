#include "node.h"



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

void Node::Render() {}
void Node::Input(bool keys[], float deltaTime) {}
void Node::Update(float delta) {}


Node::~Node()
{
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children[i]) {
			delete children[i];
		}
	}
}
