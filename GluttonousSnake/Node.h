#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
	Node();
	Node(int x, int y, int status);
	virtual ~Node();
	void setX(int x);
	const int& getX() const;
	void setY(int y);
	const int& getY() const;
	void setStatus(int status);
	const int& getStatus() const;
	bool operator==(const Node& node);

private:
	int x;
	int y;
	int status;
};

#endif _NODE_H_