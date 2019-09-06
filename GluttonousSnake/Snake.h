#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <list>
#include "Node.h"
#include "meta.h"

#define FLAG_FREE		0
#define FLAG_SNAKE		1
#define FLAG_FOOD		2

enum DIRECT
{
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

class Snake
{
public:
	Snake(int x, int y, int dir, int rate);
	virtual ~Snake();
	void move(int mapw, int maph, Node& food);
	std::shared_ptr<Node> createNode();
private:
	void removeBack();
	void generateNewFood(int mapw, int maph, Node& food);
public:
	std::list<Node> snakeList;
	int dir;
	int rate;
	int score;
	bool dead;
};

#endif // _SNAKE_H_