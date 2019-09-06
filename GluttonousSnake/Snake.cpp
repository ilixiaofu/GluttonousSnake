#include "Snake.h"

Snake::Snake(int x, int y, int dir, int rate) : dir(dir), rate(rate), score(0), dead(false)
{
	Node head(x, y, FLAG_SNAKE);
	Node node(x + 1, y, FLAG_SNAKE);
	this->snakeList.push_front(head);
	this->snakeList.push_front(node);
}

Snake::~Snake()
{

}

std::shared_ptr<Node> Snake:: createNode()
{
	int step = 1;
	int x = 0;
	int y = 0;
	Node head = this->snakeList.front();
	switch (this->dir)
	{
	case UP:
		x = head.getX();
		y = head.getY() - step;
		break;
	case DOWN:
		x = head.getX();
		y = head.getY() + step;
		break;
	case LEFT:
		x = head.getX() - step;
		y = head.getY();
		break;
	case RIGHT:
		x = head.getX() + step;
		y = head.getY();
		break;
	default:
		break;
	}
	std::shared_ptr<Node> sptr(new Node(x, y, FLAG_SNAKE));
	return sptr;
}

void Snake::move(int mapw, int maph, Node& food)
{
	std::shared_ptr<Node> newHead = this->createNode();
	// 判断蛇头是否吃到了食物
	if ((*newHead) == food)
	{
		this->snakeList.push_front(*newHead);
		this->score += 1;
		if (this->score > 0 && this->score % 8 == 0)
		{
			if (this->rate > 8)
			{
				this->rate -= this->score / 8;
			}
		}
		// 生成新的食物
		this->generateNewFood(mapw, maph, food);
		return;
	}
	else
	{
		// 蛇头是否触碰到左右边界
		if (newHead->getX() <= 0 || newHead->getX() > (mapw - 2))
		{
			this->dead = true;
			return;
		}
		// 蛇头是否触碰到上下边界
		if (newHead->getY() <= 0 || newHead->getY() > (maph - 2))
		{
			this->dead = true;
			return;
		}
		// 蛇头是否触碰到蛇身
		auto it = this->snakeList.begin();
		++it;
		for (; it != this->snakeList.end(); )
		{
			if ((*it) == *newHead)
			{
				this->dead = true;
				break;
			}
			++it;
		}
	}
	// 增加蛇头
	this->snakeList.push_front(*newHead);
	// 移除蛇尾
	this->removeBack();
}

void Snake::removeBack()
{
	this->snakeList.pop_back();
}

void Snake::generateNewFood(int mapw, int maph, Node& food)
{
	srand((unsigned)time(NULL));
	while (true)
	{
		int x = rand() % (mapw - 2) + 1;
		int y = rand() % (maph - 2) + 1;
		food.setX(x);
		food.setY(y);
		food.setStatus(FLAG_FOOD);
		for (auto it = this->snakeList.begin(); it != this->snakeList.end(); )
		{
			if ((*it) == food)
			{
				food.setStatus(FLAG_FREE);
				break;
			}
			++it;
		}
		if (food.getStatus() == FLAG_FOOD)
		{
			return;
		}
	}
}