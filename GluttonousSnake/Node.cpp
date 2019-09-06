#include "Node.h"

Node::Node() :x(0), y(0), status(0)
{

}
Node::Node(int x, int y, int status):x(x), y(y), status(status)
{

}
Node::~Node()
{

}

void Node::setX(int x)
{
	this->x = x;
}
const int& Node::getX() const
{
	return this->x;
}

void Node::setY(int y)
{
	this->y = y;
}

const int& Node::getY() const
{
	return this->y;
}

void Node::setStatus(int status)
{
	this->status = status;
}
const int& Node::getStatus() const
{
	return this->status;
}
bool Node::operator==(const Node& node)
{
	if (this->x == node.x && this->y == node.y)
	{
		return true;
	}
	return false;
}
