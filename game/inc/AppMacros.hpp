#pragma once

#include "cocos2d.h"

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource gameResource  =  { cocos2d::Size(480, 320),   "images" };

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)
