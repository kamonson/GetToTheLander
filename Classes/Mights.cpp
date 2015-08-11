#include "Mights.h"
#include "Definitions.h"

USING_NS_CC;

//set pipe to visible screen size
Mights::Mights(){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//create a function to spawn mights
void Mights::SpawnMights(cocos2d::Layer *layer)
{
	CCLOG("SPAWN Mights");

	//Create mights

//for testing on pc C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\

	//auto topMights = Sprite::create("C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\MightsAndTights.png");
	//auto bottomMights = Sprite::create("C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\MightsAndTights.png");

//for running on platform
	auto topMights = Sprite::create("MightsAndTights.png");
	auto bottomMights = Sprite::create("MightsAndTights.png");

	//auto topMightsBody = PhysicsBody::createBox(topMights->getContentSize());
	//auto bottomMightsBody = PhysicsBody::createBox(bottomMights->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_MIGHTS_THRESHOLD){
		random = LOWER_SCREEN_MIGHTS_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_MIGHTS_THRESHOLD){
		random = UPPER_SCREEN_MIGHTS_THRESHOLD;
	}

	auto topMightsPosition = (random * visibleSize.height) + (topMights->getContentSize().height / 2);

	//topMightsBody->setDynamic(false);
	//bottomMightsBody->setDynamic(false);

	//topMightsBody->setCollisionBitmask(BKG_COLLISION_BITMASK);
	//bottomMightsBody->setCollisionBitmask(BKG_COLLISION_BITMASK);
	//topMightsBody->setContactTestBitmask(false);
	//bottomMightsBody->setContactTestBitmask(false);

	//topMights->setPhysicsBody(topMightsBody);
	//bottomMights->setPhysicsBody(bottomMightsBody);

	//set bottom mights to top and account for gap size
	topMights->setPosition(Point(visibleSize.width + topMights->getContentSize().width + origin.x, topMightsPosition));
	bottomMights->setPosition(Point(topMights->getPositionX(), topMightsPosition - (Sprite::create("Ball.png")->getContentSize().height*MIGHTS_GAP) - topMights->getContentSize().height));

	layer->addChild(topMights);
	layer->addChild(bottomMights);

	auto topMightsAction = MoveBy::create(MIGHTS_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));
	auto bottomMightsAction = MoveBy::create(MIGHTS_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));

	topMights->runAction(topMightsAction);
	bottomMights->runAction(bottomMightsAction);
}