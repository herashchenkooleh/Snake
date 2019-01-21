#include "MainGameScene.hpp"
#include "AppMacros.hpp"
#include "ui/CocosGUI.h"
#include "EntitiesManager.hpp"
#include "SpawnSnakeAction.hpp"

static constexpr unsigned int FLOWER_COST = 50;
static constexpr unsigned int SNAKE_SPAWN_INTERVAL_IN_SEC = 5;
static constexpr unsigned int INCREASE_SNAKE_SPAWN_INTERVAL_IN_SEC = 10;

cocos2d::Scene* MainGameScene::scene()
{
     return MainGameScene::create();
}

bool MainGameScene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

	cocos2d::Director::getInstance()->resume();
	getPhysicsWorld()->setSubsteps(10);

	numFlowers = 0;
	flowerPlanted = false;
	spawnIntervalInc = 1.0f;
	spawnIntervalIncTime = 0.0f;
	needSpawnSnake = true;
	//fixtureSprite = nullptr;

	scheduleUpdate();

	auto mouseListener = cocos2d::EventListenerMouse::create();

	//mouse events
	mouseListener->onMouseUp = CC_CALLBACK_1(MainGameScene::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MainGameScene::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//keyborad events
	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainGameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto sprite = cocos2d::Sprite::create("MainScene/Grass.png");
	sprite->setPosition(cocos2d::Vec2(visibleSize / 2) + origin);
	sprite->setScaleX(visibleSize.width  / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);

	this->addChild(sprite);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainGameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	gameLayer = MainGameSceneLayer::create(*this);
	this->addChild(gameLayer);

	guiLayer = GUILayer::create();
	float percentage = ((float)purse.getCoinsCount() / (float)purse.getNeedNumCoins()) * 100.0f;
	guiLayer->updateProgressBar(percentage);
	this->addChild(guiLayer);

    return true;
}

void MainGameScene::onMouseDown(cocos2d::Event *event)
{
	cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
	if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		mouseEvent = MouseEvent::left;
	}
	else if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{
		mouseEvent = MouseEvent::right;
	}
	else
	{
		mouseEvent = MouseEvent::unknown;
	}

	mouseClickPos = cocos2d::Vec2(e->getCursorX(), e->getCursorY());
}

void MainGameScene::onMouseUp(cocos2d::Event *event)
{
	cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;

	switch (mouseEvent)
	{
	case MainGameScene::MouseEvent::right:
		tryPlantFlower();
		break;
	default:
		break;
	}
}

void MainGameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
}

void MainGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		guiLayer->showHideMenu();
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_P)
	{
		guiLayer->showHidePause();
	}
}

void MainGameScene::addCoins(const unsigned int value)
{
	purse.addCoins(value);
	float percentage = ((float)purse.getCoinsCount() / (float)purse.getNeedNumCoins()) * 100.0f;
	guiLayer->updateProgressBar(percentage);
}

/*virtual*/ void MainGameScene::update(float delta) /*override*/
{
	if (checkWin())
	{
		guiLayer->processWin();
	}
	else if (checkGameOver())
	{
		guiLayer->processGameOver();
	}

	//if (flowerPlanted && !fixtureSprite)
	//{
	//	fixtureSprite = new cocos2d::Sprite();
	//	fixtureSprite->autorelease();

	//	auto create = SpawnSnakeAction::create(gameLayer);
	//	auto wait = cocos2d::DelayTime::create(SNAKE_SPAWN_INTERVAL_IN_SEC);
	//	auto sequence = cocos2d::Sequence::create(create, wait, NULL);
	//	fixtureSprite->runAction(cocos2d::RepeatForever::create(sequence));
	//	this->addChild(fixtureSprite);
	//}

	if (spawnIntervalIncTime >= INCREASE_SNAKE_SPAWN_INTERVAL_IN_SEC)
	{
		spawnIntervalInc += 0.05f;
		spawnIntervalIncTime = 0.0f;
	}
	spawnIntervalIncTime += delta;

	if (flowerPlanted && needSpawnSnake)
	{
		needSpawnSnake = false;
		auto create = SpawnSnakeAction::create(gameLayer);
		auto waitInSec = SNAKE_SPAWN_INTERVAL_IN_SEC * spawnIntervalInc;
		auto wait = cocos2d::DelayTime::create(waitInSec);
		auto callback = cocos2d::CallFunc::create([this]() {
			this->actionFinished();
		});
		auto sequence = cocos2d::Sequence::create(create, wait, callback, NULL);
		this->runAction(sequence);
	}

	EntitiesManager::instance().update(delta);
}

void MainGameScene::tryPlantFlower()
{
	if (purse.getCoinsCount() >= FLOWER_COST)
	{
		purse.removeCoins(FLOWER_COST);
		EntitiesManager::instance().createFlower(gameLayer, mouseClickPos);

		float percentage = ((float)purse.getCoinsCount() / (float)purse.getNeedNumCoins()) * 100.0f;
		guiLayer->updateProgressBar(percentage);

		flowerPlanted = true;
		numFlowers++;
	}
}

bool MainGameScene::checkWin()
{
	return purse.getNeedNumCoins() <= purse.getCoinsCount();
}

bool MainGameScene::checkGameOver()
{
	return (numFlowers <= 0) && (purse.getCoinsCount() < FLOWER_COST);
}

bool MainGameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if ((nodeA->getTag() == EntitiesManager::getFlowerTag()) &&
			(nodeB->getTag() == SnakeEntity::getSnakeTag()))
		{
			nodeA->removeFromParentAndCleanup(true);
			SnakeEntity::setBonusSpeed(true);
			numFlowers--;
		}
		else if ((nodeB->getTag() == EntitiesManager::getFlowerTag()) &&
			(nodeA->getTag() == SnakeEntity::getSnakeTag()))
		{
			nodeB->removeFromParentAndCleanup(true);
			SnakeEntity::setBonusSpeed(true);
			numFlowers--;
		}
	}

	return true;
}

void MainGameScene::actionFinished()
{
	needSpawnSnake = true;
}