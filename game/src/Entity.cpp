#include "Entity.hpp"

/*static*/ Entity* Entity::create(const std::string& ResFilePath, cocos2d::PhysicsBody* body)
{
	auto pSprite = new Entity();
	if (pSprite && pSprite->initWithFile(ResFilePath))
	{
		pSprite->autorelease();
		pSprite->initTouchable();

		if (body != nullptr)
		{
			body->autorelease();
			pSprite->setPhysicsBody(body);
		}

		return pSprite;
	}

	return nullptr;
}


void Entity::setClickCallback(ClickCallback callback)
{
	clickCallback = callback;
}

float Entity::getTotalTime() const
{
	return totalTime;
}

void Entity::zeroTotalTIme()
{
	totalTime = 0.0f;
}

void Entity::initTouchable()
{
	clickListener = cocos2d::EventListenerTouchOneByOne::create();
	CC_SAFE_RETAIN(clickListener);
	clickListener->setSwallowTouches(true);
	clickListener->onTouchBegan = CC_CALLBACK_2(Entity::onClickBegan, this);
	clickListener->onTouchMoved = CC_CALLBACK_2(Entity::onClickMoved, this);
	clickListener->onTouchEnded = CC_CALLBACK_2(Entity::onClickEnded, this);
	clickListener->onTouchCancelled = CC_CALLBACK_2(Entity::onClickCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);
}

bool Entity::hitTest(const cocos2d::Vec2 &pt)
{
	cocos2d::Vec2 nsp = convertToNodeSpace(pt);
	cocos2d::Rect bb;
	bb.size = _contentSize;
	if (bb.containsPoint(nsp))
	{
		return true;
	}

	return false;
}



bool Entity::onClickBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
	hitted = false;
	clickBeganPosition = touch->getLocation();
	if (hitTest(clickBeganPosition))
	{
		hitted = true;
	}

	if (!hitted)
	{
		return false;
	}

	pushDownEvent();
	return true;

}

void Entity::onClickMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
	clickMovePosition = touch->getLocation();

	moveEvent();
}

void Entity::onClickEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
	clickEndPosition = touch->getLocation();

	if (hitTest(clickEndPosition))
	{
		releaseUpEvent();
	}
	else
	{
		cancelUpEvent();
	}
}

void Entity::onClickCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
	cancelUpEvent();
}

void Entity::pushDownEvent()
{
	this->retain();
	if (clickCallback)
	{
		clickCallback(this, ClickEventType::BEGAN);
	}
	this->release();
}

void Entity::moveEvent()
{
	this->retain();
	if (clickCallback)
	{
		clickCallback(this, ClickEventType::MOVED);
	}
	this->release();
}

void Entity::releaseUpEvent()
{
	this->retain();
	if (clickCallback)
	{
		clickCallback(this, ClickEventType::ENDED);
	}
	this->release();
}

void Entity::cancelUpEvent()
{
	this->retain();
	if (clickCallback)
	{
		clickCallback(this, ClickEventType::CANCELED);
	}
	this->release();
}