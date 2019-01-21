#include "SpawnSnakeSegmentAction.hpp"
#include "SnakeEntity.hpp"

/*static*/ SpawnSnakeSegmentAction* SpawnSnakeSegmentAction::create(SnakeEntity& Snake)
{
	return new SpawnSnakeSegmentAction(Snake);
}

void SpawnSnakeSegmentAction::update(float time)
{
	snake.createSegment();
}

SpawnSnakeSegmentAction::SpawnSnakeSegmentAction(SnakeEntity& Snake)
	: snake(Snake)

{
}

SpawnSnakeSegmentAction::~SpawnSnakeSegmentAction()
{
}