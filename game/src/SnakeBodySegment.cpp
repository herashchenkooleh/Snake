#include "SnakeBodySegment.hpp"
#include "MainGameScene.hpp"
#include "SnakeEntity.hpp"

static constexpr float SNAKE_SCALE = 0.07f;
static constexpr const char* SNAKE_LINK_RES_PATH = "";

/*static*/ SnakeBodySegment* SnakeBodySegment::create(SnakeEntity& Parent, const std::string& ResFilePath)
{
	auto pSprite = new SnakeBodySegment(Parent);
	if (pSprite &&  pSprite->initWithFile(ResFilePath))
	{
		pSprite->scheduleUpdate();
		pSprite->autorelease();
		pSprite->initTouchable();
		pSprite->setScale(SNAKE_SCALE);

		auto shift = pSprite->getContentSize().width;

		auto width = pSprite->getContentSize().width;
		auto height = pSprite->getContentSize().height - shift;

		auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(width, height), cocos2d::PhysicsMaterial(0.01f, 0.0f, 0.0f));

		physicsBody->setLinearDamping(1.0f);
		physicsBody->setAngularDamping(1.0f);
		physicsBody->setGravityEnable(false);
		pSprite->setPhysicsBody(physicsBody);

		pSprite->setClickCallback([](Entity* sprite, Entity::ClickEventType type)
			{
				auto segment = dynamic_cast<SnakeBodySegment*>(sprite);
				if (segment && type == Entity::ClickEventType::ENDED)
				{
					segment->getSnake().removeSegment();
				}
			}
		);

		return pSprite;
	}

	return nullptr;
}

/*static*/ float SnakeBodySegment::getScale()
{
	return SNAKE_SCALE;
}

SnakeBodySegment::SnakeBodySegment(SnakeEntity& Parent)
	: parent(Parent)
{
}

SnakeEntity& SnakeBodySegment::getSnake()
{
	return parent;
}

const SnakeEntity& SnakeBodySegment::getSnake() const
{
	return parent;
}