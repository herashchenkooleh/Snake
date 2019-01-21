#pragma once

#include <cocos2d.h>

class MainGameSceneLayer;

class SpawnSnakeAction : public cocos2d::ActionInterval
{
public:
	static SpawnSnakeAction* create(MainGameSceneLayer* Layer);

	virtual void update(float time) override;

	SpawnSnakeAction(MainGameSceneLayer* Layer);

	SpawnSnakeAction(SpawnSnakeAction&&) = default;
	SpawnSnakeAction(const SpawnSnakeAction&) = default;

	SpawnSnakeAction& operator=(SpawnSnakeAction&&) = default;
	SpawnSnakeAction& operator=(const SpawnSnakeAction&) = default;

	~SpawnSnakeAction();

private:
	MainGameSceneLayer* layer;
};