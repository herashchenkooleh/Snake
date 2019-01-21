#pragma once

#include <cocos2d.h>

class MainGameScene;

class MainGameSceneLayer : public cocos2d::Layer
{
public:
	static MainGameSceneLayer* create(MainGameScene& Scene);

	void addCoins(const unsigned int value);

	cocos2d::PhysicsWorld* getPhysicsWorld();

protected:
	MainGameSceneLayer(MainGameScene& Scene);

private:
	MainGameScene& scene;
};