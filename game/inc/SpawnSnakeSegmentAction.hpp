#pragma once

#include <cocos2d.h>

class SnakeEntity;

class SpawnSnakeSegmentAction : public cocos2d::ActionInterval
{
public:
	static SpawnSnakeSegmentAction* create(SnakeEntity& Snake);

	virtual void update(float time) override;

	SpawnSnakeSegmentAction(SnakeEntity& Snake);

	SpawnSnakeSegmentAction(SpawnSnakeSegmentAction&&) = default;
	SpawnSnakeSegmentAction(const SpawnSnakeSegmentAction&) = default;

	SpawnSnakeSegmentAction& operator=(SpawnSnakeSegmentAction&&) = default;
	SpawnSnakeSegmentAction& operator=(const SpawnSnakeSegmentAction&) = default;

	~SpawnSnakeSegmentAction();

private:
	SnakeEntity& snake;
};