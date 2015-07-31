#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

//set pipe to visible screen size
Pipe::Pipe(){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//create a function to spawn pipe
void Pipe::SpawnPipe(cocos2d::Layer *layer)
{
	CCLOG("SPAWN PIPE");

	//Create pipe

	auto topPipe = Sprite::create("Pipe.png");
	auto bottomPipe = Sprite::create("Pipe.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_PIPE_THRESHOLD){
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD){
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height / 2);

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	//set bottom pipe to top and account for gap size
	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
	bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - (Sprite::create("Ball.png")->getContentSize().height*PIPE_GAP) - topPipe->getContentSize().height));

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));
	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	//create a physics body to create points
	auto pointNode = Node::create();
	auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP));
	//enable collision detection
	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);
	//set position between pipes
	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - ((Sprite::create("Ball.png")->getContentSize().height*PIPE_GAP) / 2)));

	layer->addChild(pointNode);

	auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));

	pointNode->runAction(pointNodeAction);
}