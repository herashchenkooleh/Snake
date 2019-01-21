#pragma once

#include <cocos2d.h>
#include "ui/UIButton.h"

class GUILayer : public cocos2d::Layer
{
public:
	enum class State
	{
		IDLE,
		MENU
	};

	static GUILayer* create();

	bool init();

	void updateProgressBar(const float percentage);
	void showHideMenu();
	void showHidePause();

	void processWin();
	void processGameOver();

private:
	void processIdle();
	void processMenu();
	void processPause();

private:
	cocos2d::ProgressTimer* progressTimer;

	State state;
	cocos2d::ui::Button* continueButton;
	cocos2d::ui::Button* restartButton;
	cocos2d::ui::Button* exitButton;

	cocos2d::Sprite* pausedSprite;

	bool paused;
};