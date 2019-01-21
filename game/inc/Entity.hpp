#pragma once

#include <vector>
#include <functional>
#include <cocos2d.h>

class Entity : public cocos2d::Sprite
{
public:
	enum class ClickEventType
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELED
	};

	using ClickCallback = std::function<void(Entity*, Entity::ClickEventType)>;

public:
	static Entity* create(const std::string& ResFilePath, cocos2d::PhysicsBody* body = nullptr);

	void setClickCallback(ClickCallback callback);

	float getTotalTime() const;
	void zeroTotalTIme();

	void initTouchable();

	bool hitTest(const cocos2d::Vec2 &pt);

	bool onClickBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
	void onClickMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
	void onClickEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
	void onClickCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

	void pushDownEvent();
	void moveEvent();

	virtual void releaseUpEvent();
	virtual void cancelUpEvent();

private:
	ClickCallback clickCallback;

	float totalTime;

	bool hitted;
	cocos2d::EventListenerTouchOneByOne* clickListener;
	cocos2d::Vec2 clickBeganPosition;
	cocos2d::Vec2 clickMovePosition;
	cocos2d::Vec2 clickEndPosition;
};