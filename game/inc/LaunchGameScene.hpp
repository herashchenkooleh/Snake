#pragma once

#include "cocos2d.h"

class LaunchGameScene : public cocos2d::Scene
{
public:
	virtual bool init() override;

	static cocos2d::Scene* scene();

	CREATE_FUNC(LaunchGameScene);
};
