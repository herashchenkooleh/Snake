#include "EntitiesManager.hpp"
#include "SpawnCoinAction.hpp"

static constexpr const char* FLOWER_RES_PATH = "MainScene/Flower.png";
static constexpr const char* COIN_RES_PATH = "MainScene/Coin.png";

static constexpr float COINS_SPAWN_INTERVAL_IN_SEC = 3.0f;
static constexpr float COINS_LIFE_TIME_IN_SEC = 10.0f;

static constexpr float FLOWER_SCALE = 0.14f;
static constexpr float COIN_SCALE = 0.1f;

static constexpr float COINS_SPAWN_CYRCLE_RADIUS = 30;
static constexpr uint32_t COINS_SPAWN_TIME_IN_SEC = 1;
static constexpr uint32_t COINS_PER_SEC = 5;

/*static*/ EntitiesManager& EntitiesManager::instance()
{
	static EntitiesManager sInstance;

	return sInstance;
}

/*static*/ int EntitiesManager::getFlowerTag()
{
	return 10;
}

EntitiesManager::EntitiesManager()
{
}

EntitiesManager::~EntitiesManager()
{
}

void EntitiesManager::createFlower(MainGameSceneLayer* Layer, const cocos2d::Vec2& pos)
{
	auto flower = Entity::create(FLOWER_RES_PATH);
	if (flower)
	{
		flower->setTag(EntitiesManager::getFlowerTag());
		flower->setPosition(pos);
		flower->setScale(FLOWER_SCALE);

		auto width = flower->getContentSize().width;
		auto height = flower->getContentSize().height;

		auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(width, height), cocos2d::PhysicsMaterial(0.01f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(0xffffffff);
		flower->setPhysicsBody(physicsBody);

		auto wait = cocos2d::DelayTime::create(COINS_SPAWN_INTERVAL_IN_SEC);
		auto scaleG = cocos2d::ScaleTo::create(0.2f, FLOWER_SCALE * 2);
		auto create = SpawnCoinAction::create(Layer, pos);
		auto scaleL = cocos2d::ScaleTo::create(0.2f, FLOWER_SCALE);
		auto sequence = cocos2d::Sequence::create(wait, scaleG, create, scaleL, NULL);

		flower->runAction(cocos2d::RepeatForever::create(sequence));
		Layer->addChild(flower);
		flowers.push_back(flower);
	}
}

void EntitiesManager::createCoin(MainGameSceneLayer* Layer, const cocos2d::Vec2& pos)
{
	auto coin = Entity::create(COIN_RES_PATH);
	if (coin)
	{
		coin->setPosition(pos);
		coin->setScale(COIN_SCALE);

		coin->setClickCallback([=](Entity* sprite, Entity::ClickEventType type)
			{
				if (sprite && type == Entity::ClickEventType::ENDED)
				{
					sprite->stopAllActions();
					auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
					auto point = cocos2d::Vec2(120, visibleSize.height - 35);
					auto moveTo = cocos2d::MoveTo::create(0.3f, point);
					auto remove = cocos2d::RemoveSelf::create(false);
					auto sequence = cocos2d::Sequence::create(moveTo, remove, NULL);
					sprite->runAction(sequence);
					Layer->addCoins(COINS_PER_SEC);
				}
			}
		);

		auto position = genFinalCoinPosition();
		auto moveTo = cocos2d::MoveTo::create(COINS_SPAWN_TIME_IN_SEC, pos + position);
		auto wait = cocos2d::DelayTime::create(10.0f);
		auto remove = cocos2d::RemoveSelf::create(false);
		auto sequence = cocos2d::Sequence::create(moveTo, wait, remove, NULL);
		coin->runAction(sequence);


		Layer->addChild(coin);
	}
}

cocos2d::Vec2 EntitiesManager::genFinalCoinPosition() const
{
	auto x = cocos2d::random(-1.0f * COINS_SPAWN_CYRCLE_RADIUS, COINS_SPAWN_CYRCLE_RADIUS);
	auto y = cocos2d::random(-1.0f * COINS_SPAWN_CYRCLE_RADIUS, COINS_SPAWN_CYRCLE_RADIUS);

	return cocos2d::Vec2(x, y);
}

void EntitiesManager::createSnakeEntity(MainGameSceneLayer* Layer, const cocos2d::Vec2& pos)
{
	snakeEntities.push_back(SnakeEntity::create(Layer, pos));
}

void EntitiesManager::update(float dt)
{
	for (auto& snake: snakeEntities)
	{
		snake->update(dt);
	}

	auto removeFunc = [](SnakeEntity* snake)
	{
		return snake->isEmpty();
	};

	const auto newEnd(std::remove_if(std::begin(snakeEntities), std::end(snakeEntities), removeFunc));
	snakeEntities.erase(newEnd, std::end(snakeEntities));
}