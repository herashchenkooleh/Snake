#include "LaunchGameScene.hpp"
#include "AppMacros.hpp"
#include "ui/UIButton.h"

#include "MainGameScene.hpp"

USING_NS_CC;


Scene* LaunchGameScene::scene()
{
	return LaunchGameScene::create();
}

bool LaunchGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//sky sprite
	auto sky = Sprite::create("LaunchScene/Sky.png");
	sky->setPosition(Vec2(visibleSize / 2) + origin);
	sky->setScaleX(visibleSize.width / sky->getContentSize().width);
	sky->setScaleY(visibleSize.height / sky->getContentSize().height);

	this->addChild(sky);

	//background sprite
	auto background = Sprite::create("LaunchScene/Background.png");
	background->setPosition(Vec2(visibleSize / 2) + origin);
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);

	this->addChild(background);

	//label sprite
	auto label = Sprite::create("LaunchScene/Label.png");
	label->setPosition(Vec2(visibleSize / 2) + origin + Vec2(0, 80));
	label->setScale(0.5f);
	this->addChild(label);

	auto playButton = cocos2d::ui::Button::create("LaunchScene/buttons/Play_normal.png", "LaunchScene/buttons/Play_select.png");

	playButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y + 20));
	playButton->setScale(0.3f);

	playButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto director = Director::getInstance();
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			director->replaceScene(MainGameScene::create());
			break;
		default:
			break;
		}
		});

	this->addChild(playButton);

	auto exitButton = cocos2d::ui::Button::create("LaunchScene/buttons/Exit_normal.png", "LaunchScene/buttons/Exit_select.png");

	exitButton->setPosition(cocos2d::Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y - 40));
	exitButton->setScale(0.3f);

	exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto director = Director::getInstance();
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			director->end();
			break;
		default:
			break;
		}
		});

	this->addChild(exitButton);

	return true;
}