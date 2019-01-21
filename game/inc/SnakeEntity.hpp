#pragma once

#include "SnakeEntity.hpp"
#include "SnakeBodySegment.hpp"

class MainGameSceneLayer;

class SnakeEntity
{
public:
	static SnakeEntity* create(MainGameSceneLayer* Layer, const cocos2d::Vec2& Position);

	void update(float dt);

	void removeSegment();
	void createSegment();

	bool isEmpty();

	static void setBonusSpeed(const bool value);

	static int getSnakeTag();

protected:
	SnakeEntity(MainGameSceneLayer* Layer, const cocos2d::Vec2& Position);

private:
	MainGameSceneLayer* layer;

	std::vector<SnakeBodySegment*> body;
	std::vector<cocos2d::PhysicsJointPin*> joints;

	cocos2d::Sprite* fixtureHead;

	float timeToChangeMoveDirInSec;
	float totalTime;

	cocos2d::Vec2 moveDir;

	float speed;
	int snakeColor;

	static bool bonusSpeed;
	float bonusSpeedTime;
};
