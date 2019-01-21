#pragma once

#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "Purse.hpp"
#include "GUILayer.hpp"
#include "MainGameSceneLayer.hpp"

class MainGameScene : public cocos2d::Scene
{
	enum class MouseEvent
	{
		right,
		left,
		unknown
	};
public:
    virtual bool init() override;

    static cocos2d::Scene* scene();

    CREATE_FUNC(MainGameScene);

	void onMouseDown(cocos2d::Event *event);
	void onMouseUp(cocos2d::Event *event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void addCoins(const unsigned int value);

	virtual void update(float delta) override;

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void actionFinished();

private:
	void tryPlantFlower();

	bool checkWin();
	bool checkGameOver();

private:
	MouseEvent mouseEvent;
	cocos2d::Vec2 mouseClickPos;

	Purse purse;

	bool flowerPlanted;

	bool needSpawnSnake;
	float spawnIntervalInc;
	float spawnIntervalIncTime;

	GUILayer* guiLayer;
	MainGameSceneLayer* gameLayer;

	int numFlowers;
};
