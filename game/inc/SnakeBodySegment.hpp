#pragma once

#include "Entity.hpp"
#include <cocos2d.h>
#include <string>

class SnakeEntity;

class SnakeBodySegment : public Entity
{
public:
	static SnakeBodySegment* create(SnakeEntity& Parent, const std::string& ResFilePath);

	static float getScale();

	SnakeEntity& getSnake();
	const SnakeEntity& getSnake() const;

protected:
	SnakeBodySegment(SnakeEntity& Parent);

private:
	SnakeEntity& parent;
};