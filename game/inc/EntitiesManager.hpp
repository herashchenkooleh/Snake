#pragma once

#include <thread>
#include <vector>
#include "Entity.hpp"
#include "SnakeEntity.hpp"
#include "MainGameSceneLayer.hpp"

class EntitiesManager
{
public:

	using Entities = std::vector<Entity*>;
	using SnakeEntities = std::vector<SnakeEntity*>;

public:
	static EntitiesManager& instance();

	static int getFlowerTag();

	void createFlower(MainGameSceneLayer* Layer, const cocos2d::Vec2& pos);
	void createCoin(MainGameSceneLayer* Layer, const cocos2d::Vec2& pos);
	void createSnakeEntity(MainGameSceneLayer* Layer, const cocos2d::Vec2& pos);

	void update(float dt);

protected:
	EntitiesManager();

	EntitiesManager(EntitiesManager&&) = delete;
	EntitiesManager(const EntitiesManager&) = delete;

	EntitiesManager& operator=(EntitiesManager&&) = delete;
	EntitiesManager& operator=(const EntitiesManager&) = delete;

	~EntitiesManager();

	cocos2d::Vec2 genFinalCoinPosition() const;

private:
	Entities flowers;

	SnakeEntities snakeEntities;
};