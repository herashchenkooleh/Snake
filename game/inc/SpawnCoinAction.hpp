#pragma once

#include <cocos2d.h>

class MainGameSceneLayer;

class SpawnCoinAction : public cocos2d::ActionInterval
{
public:
	static SpawnCoinAction* create(MainGameSceneLayer* Layer, const cocos2d::Vec2& Position);

	virtual void update(float time) override;

	SpawnCoinAction(MainGameSceneLayer* Layer);

	SpawnCoinAction(SpawnCoinAction&&) = default;
	SpawnCoinAction(const SpawnCoinAction&) = default;

	SpawnCoinAction& operator=(SpawnCoinAction&&) = default;
	SpawnCoinAction& operator=(const SpawnCoinAction&) = default;

	~SpawnCoinAction();

private:
	cocos2d::Vec2 position;
	MainGameSceneLayer* layer;
};