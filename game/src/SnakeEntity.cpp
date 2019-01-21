#include "SnakeEntity.hpp"
#include "MainGameSceneLayer.hpp"
#include "SpawnSnakeSegmentAction.hpp"

static constexpr const char* SNAKE_HEAD_RED = "MainScene/SnakeRed/SnakeHead.png";
static constexpr const char* SNAKE_BODY_RED = "MainScene/SnakeRed/SnakeBody.png";

static constexpr const char* SNAKE_HEAD_YELLOW = "MainScene/SnakeYelow/SnakeHead.png";
static constexpr const char* SNAKE_BODY_YELLOW = "MainScene/SnakeYelow/SnakeBody.png";

static constexpr int DEFAULT_NUM_SEGS_OF_BODY = 4;
static constexpr float SPAWN_SEGMENT_TIME_IN_SEC = 3.0f;
static constexpr float BONUS_SPEED_INTERVAL_IN_SEC = 5.0f;

bool SnakeEntity::bonusSpeed = false;

/*static*/ SnakeEntity* SnakeEntity::create(MainGameSceneLayer* Layer, const cocos2d::Vec2& Position)
{
	return new SnakeEntity(Layer, Position);
}

SnakeEntity::SnakeEntity(MainGameSceneLayer* Layer, const cocos2d::Vec2& Position)
	: layer(Layer)
	, moveDir(cocos2d::Vec2(0.0, 1.0f))
	, timeToChangeMoveDirInSec(cocos2d::random(1.0f, 5.0f))
	, totalTime(0.0f)
	, speed(200.0f)
	, snakeColor(cocos2d::random(1, 2))
	, bonusSpeedTime(0.0f)
{
	fixtureHead = new cocos2d::Sprite();
	auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(1.0f, 1.0f), cocos2d::PhysicsMaterial(0, 0, 0));

	physicsBody->setLinearDamping(1.0f);
	physicsBody->setAngularDamping(1.0f);
	physicsBody->setGravityEnable(false);
	fixtureHead->setPhysicsBody(physicsBody);

	layer->addChild(fixtureHead);

	auto resPath = snakeColor == 1 ? SNAKE_HEAD_RED : SNAKE_HEAD_YELLOW;
	auto head = SnakeBodySegment::create(*this, resPath);
	head->getPhysicsBody()->setContactTestBitmask(0xffffffff);
	head->setTag(SnakeEntity::getSnakeTag());
	layer->addChild(head);
	body.push_back(head);

	auto halfScaledHeight = (head->getContentSize().height / 2) * SnakeBodySegment::getScale();
	fixtureHead->setPosition(cocos2d::Vec2(Position.x, Position.y + halfScaledHeight));
	head->setPosition(Position);

	auto anchr1 = cocos2d::Vec2(0.0f, -1.f);
	auto anchr2 = cocos2d::Vec2(0.0f, halfScaledHeight);
	auto body1 = fixtureHead->getPhysicsBody();
	auto body2 = head->getPhysicsBody();

	auto joint = cocos2d::PhysicsJointPin::construct(body1, body2, anchr1, anchr2);
	joint->setCollisionEnable(false);
	layer->getPhysicsWorld()->addJoint(joint);
	joints.push_back(joint);


	for (int i = 0; i < DEFAULT_NUM_SEGS_OF_BODY; i++)
	{
		createSegment();
	}

	auto wait = cocos2d::DelayTime::create(SPAWN_SEGMENT_TIME_IN_SEC);
	auto create = SpawnSnakeSegmentAction::create(*this);
	auto sequence = cocos2d::Sequence::create(wait, create, NULL);
	fixtureHead->runAction(cocos2d::RepeatForever::create(sequence));
}

void SnakeEntity::update(float dt)
{
	if (bonusSpeed)
	{
		if (bonusSpeedTime >= BONUS_SPEED_INTERVAL_IN_SEC)
		{
			bonusSpeedTime = 0.0f;
			setBonusSpeed(false);
		}
		bonusSpeedTime += dt;
	}

	totalTime += dt;
	if (totalTime >= timeToChangeMoveDirInSec)
	{
		float angle = cocos2d::random(0.0f, 15.0f);
		moveDir.rotate(cocos2d::Vec2(0.0f, 0.0f), angle);
		moveDir.normalize();

		totalTime = 0.0f;
		timeToChangeMoveDirInSec = cocos2d::random(1.0f, 5.0f);
	}

	auto newSpeed = bonusSpeed ? 2.0f * speed : speed;
	auto newPos = fixtureHead->getPosition() + moveDir * dt * newSpeed;

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	if (newPos.x < 15.0f)
	{
		newPos.x = 15.0f;
	}

	if (newPos.x > visibleSize.width - 15.0f)
	{
		newPos.x = visibleSize.width - 15.0f;
	}

	if (newPos.y < 15.0f)
	{
		newPos.y = 15.0f;
	}

	if (newPos.y > visibleSize.height - 30.0f)
	{
		newPos.y = visibleSize.height - 30.0f;
	}

	fixtureHead->setPosition(newPos);
}

void SnakeEntity::removeSegment()
{
	layer->getPhysicsWorld()->removeJoint(joints.back());
	joints.pop_back();

	layer->removeChild(body.back());
	body.pop_back();

	if (body.empty())
	{
		layer->removeChild(fixtureHead);
	}
}

void SnakeEntity::createSegment()
{
	auto localHead = body.back();

	auto resPath = snakeColor == 1 ? SNAKE_BODY_RED : SNAKE_BODY_YELLOW;
	auto segment = SnakeBodySegment::create(*this, resPath);
	layer->addChild(segment);
	body.push_back(segment);

	auto shift = (segment->getContentSize().width / 2) * SnakeBodySegment::getScale();
	auto sHalfScaledHeight = (segment->getContentSize().height / 2) * SnakeBodySegment::getScale();

	auto hHalfScaledHeight = (localHead->getContentSize().height / 2) * SnakeBodySegment::getScale();
	auto position = localHead->getPosition() - cocos2d::Vec2(0.0f, hHalfScaledHeight) + cocos2d::Vec2(0.0f, shift);

	segment->setPosition(position);

	auto anchr1 = cocos2d::Vec2(0.0f, -1.f * hHalfScaledHeight + shift);
	auto anchr2 = cocos2d::Vec2(0.0f, sHalfScaledHeight - shift);
	auto body1 = localHead->getPhysicsBody();
	auto body2 = segment->getPhysicsBody();

	auto joint = cocos2d::PhysicsJointPin::construct(body1, body2, anchr1, anchr2);
	joint->setCollisionEnable(false);
	layer->getPhysicsWorld()->addJoint(joint);
	joints.push_back(joint);
}

bool SnakeEntity::isEmpty()
{
	return body.empty();
}

void SnakeEntity::setBonusSpeed(const bool value)
{
	bonusSpeed = value;
}

/*static*/ int SnakeEntity::getSnakeTag()
{
	return 20;
}