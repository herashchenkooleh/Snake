#include "SpawnSnakeAction.hpp"
#include "EntitiesManager.hpp"
#include "MainGameSceneLayer.hpp"

/*static*/ SpawnSnakeAction* SpawnSnakeAction::create(MainGameSceneLayer* Layer)
{
	SpawnSnakeAction* action = new SpawnSnakeAction(Layer);

	return action;
}

SpawnSnakeAction::SpawnSnakeAction(MainGameSceneLayer* Layer)
	: layer(Layer)
{

}

SpawnSnakeAction::~SpawnSnakeAction()
{
}

/*virtual*/ void SpawnSnakeAction::update(float time) /*override*/
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto x = cocos2d::random(15.0f, visibleSize.width - 15.0f);
	auto y = cocos2d::random(15.0f, visibleSize.height - 30.0f);
	auto position = cocos2d::Vec2(x, y);

	EntitiesManager::instance().createSnakeEntity(layer, position);
}