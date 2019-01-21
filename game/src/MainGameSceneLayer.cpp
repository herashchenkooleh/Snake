#include "MainGameSceneLayer.hpp"
#include "MainGameScene.hpp"

/*static*/ MainGameSceneLayer* MainGameSceneLayer::create(MainGameScene& Scene)
{
	return new MainGameSceneLayer(Scene);
}

MainGameSceneLayer::MainGameSceneLayer(MainGameScene& Scene)
	: scene(Scene)
{
}

void MainGameSceneLayer::addCoins(const unsigned int value)
{
	scene.addCoins(value);
}

cocos2d::PhysicsWorld* MainGameSceneLayer::getPhysicsWorld()
{
	return scene.getPhysicsWorld();
}