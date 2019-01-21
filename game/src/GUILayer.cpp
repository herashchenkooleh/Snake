#include "GUILayer.hpp"
#include "LaunchGameScene.hpp"
#include "Entity.hpp"
#include "MainGameScene.hpp"

static constexpr float COINS_PROGRESS_BAR_SCALE = 0.12f;

/*static*/ GUILayer* GUILayer::create()
{
	auto layer = new GUILayer();
	if (layer && layer->init())
	{
		layer->autorelease();

		return layer;
	}

	return nullptr;
}

bool GUILayer::init()
{
	state = State::MENU;

	paused = false;

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto progressBarBorder = cocos2d::Sprite::create("MainScene/ProgressBarBorder.png");
	progressBarBorder->setScale(COINS_PROGRESS_BAR_SCALE);
	progressBarBorder->setAnchorPoint(cocos2d::Vec2(0, 0));
	auto height = progressBarBorder->getContentSize().height * COINS_PROGRESS_BAR_SCALE;
	progressBarBorder->setPosition(cocos2d::Vec2(25, visibleSize.height - height - 15));
	this->addChild(progressBarBorder);

	auto progressBarBackground = cocos2d::Sprite::create("MainScene/ProgressBarBackground.png");
	progressBarBackground->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));

	progressTimer = cocos2d::ProgressTimer::create(progressBarBackground);
	progressTimer->setAnchorPoint(cocos2d::Vec2(0, 0));
	progressTimer->setType(cocos2d::ProgressTimer::Type::BAR);
	progressTimer->setBarChangeRate(cocos2d::Vec2(1, 0));
	progressTimer->setMidpoint(cocos2d::Vec2(0, 1));
	progressTimer->setPosition(cocos2d::Vec2(15.0, 75.0));

	progressBarBorder->addChild(progressTimer);

	return true;
}

void GUILayer::updateProgressBar(const float percentage)
{	
	progressTimer->setPercentage(percentage);
}

void GUILayer::showHideMenu()
{
	switch (state)
	{
	case State::IDLE:
		processIdle();
		break;
	case State::MENU:
		processMenu();
		break;
	default:
		break;
	}
}

void GUILayer::showHidePause()
{
	auto director = cocos2d::Director::getInstance();
	if (!paused)
	{
		director->pause();
		paused = true;
	}
	else
	{
		director->resume();
		paused = false;
	}

	processPause();
}

void GUILayer::processWin()
{
	auto director = cocos2d::Director::getInstance();
	director->pause();

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	pausedSprite = Entity::create("MainScene/Win.png");
	pausedSprite->setPosition(cocos2d::Vec2(visibleSize / 2) + origin);
	pausedSprite->setScale(0.5f);

	this->addChild(pausedSprite);

	exitButton = cocos2d::ui::Button::create("MainScene/buttons/Exit_normal.png", "MainScene/buttons/Exit_select.png");
	exitButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y - 70));
	exitButton->setScale(0.3f);

	exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto director = cocos2d::Director::getInstance();
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			director->replaceScene(LaunchGameScene::create());
			break;
		default:
			break;
		}
		});

	this->addChild(exitButton);
}

void GUILayer::processGameOver()
{
	auto director = cocos2d::Director::getInstance();
	director->pause();

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	pausedSprite = Entity::create("MainScene/Gameover.png");
	pausedSprite->setPosition(cocos2d::Vec2(visibleSize / 2) + origin);
	pausedSprite->setScale(0.5f);

	this->addChild(pausedSprite);

	exitButton = cocos2d::ui::Button::create("MainScene/buttons/Exit_normal.png", "MainScene/buttons/Exit_select.png");
	exitButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y - 70));
	exitButton->setScale(0.3f);

	exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto director = cocos2d::Director::getInstance();
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			director->replaceScene(LaunchGameScene::create());
			break;
		default:
			break;
		}
		});

	this->addChild(exitButton);
}

void GUILayer::processIdle()
{
	this->removeChild(continueButton);
	this->removeChild(restartButton);
	this->removeChild(exitButton);

	auto director = cocos2d::Director::getInstance();
	director->resume();

	state = State::MENU;
}

void GUILayer::processMenu()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	continueButton = cocos2d::ui::Button::create("MainScene/buttons/Continue_normal.png", "MainScene/buttons/Continue_select.png");
	continueButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y + 70));
	continueButton->setScale(0.3f);

	continueButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			showHideMenu();
			break;
		default:
			break;
		}
		});

	this->addChild(continueButton);

	restartButton = cocos2d::ui::Button::create("MainScene/buttons/Restart_normal.png", "MainScene/buttons/Restart_select.png");
	restartButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y + 10));
	restartButton->setScale(0.3f);

	restartButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto director = cocos2d::Director::getInstance();
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			director->replaceScene(MainGameScene::create());
			break;
		default:
			break;
		}
		});

	this->addChild(restartButton);

	exitButton = cocos2d::ui::Button::create("MainScene/buttons/Exit_normal.png", "MainScene/buttons/Exit_select.png");
	exitButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y - 50));
	exitButton->setScale(0.3f);

	exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto director = cocos2d::Director::getInstance();
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			director->replaceScene(LaunchGameScene::create());
			break;
		default:
			break;
		}
		});

	this->addChild(exitButton);

	auto director = cocos2d::Director::getInstance();
	director->pause();

	state = State::IDLE;
}

void GUILayer::processPause()
{
	if (paused)
	{
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

		pausedSprite = Entity::create("MainScene/Paused.png");
		pausedSprite->setPosition(cocos2d::Vec2(visibleSize / 2) + origin);
		pausedSprite->setScale(0.5f);


		this->addChild(pausedSprite);
	}
	else
	{
		this->removeChild(pausedSprite);
	}
}