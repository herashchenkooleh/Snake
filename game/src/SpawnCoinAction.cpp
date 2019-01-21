#include "SpawnCoinAction.hpp"
#include "EntitiesManager.hpp"

/*static*/ SpawnCoinAction* SpawnCoinAction::create(MainGameSceneLayer* Layer, const cocos2d::Vec2& Position)
{
	SpawnCoinAction* action = new SpawnCoinAction(Layer);

	action->position = Position;

	return action;
}

SpawnCoinAction::SpawnCoinAction(MainGameSceneLayer* Layer)
	: layer(Layer)
{

}

SpawnCoinAction::~SpawnCoinAction()
{
}

/*virtual*/ void SpawnCoinAction::update(float time) /*override*/
{
	EntitiesManager::instance().createCoin(layer, position);
}