#include "Rocks.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

//set pipe to visible screen size
Rocks::Rocks(){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//create a function to spawn rocks
void Rocks::SpawnRocks(cocos2d::Layer *layer)
{
	CCLOG("SPAWN Rocks");

	//Create rocks

	//for testing on pc C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\

	//auto topRocks = Sprite::create("C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\Rocks.png");
	//auto bottomRocks = Sprite::create("C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\Rocks.png");

	//for running on platform
	auto topRocks = Sprite::create("Rocks.png");
	auto bottomRocks = Sprite::create("Rocks.png");

	auto topRocksBody = PhysicsBody::createBox(topRocks->getContentSize());
	auto bottomRocksBody = PhysicsBody::createBox(bottomRocks->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_ROCKS_THRESHOLD){
		random = LOWER_SCREEN_ROCKS_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_ROCKS_THRESHOLD){
		random = UPPER_SCREEN_ROCKS_THRESHOLD;
	}

	auto topRocksPosition = (random * visibleSize.height) + (topRocks->getContentSize().height / 2);

	topRocksBody->setDynamic(false);
	bottomRocksBody->setDynamic(false);

	topRocksBody->setCollisionBitmask(ROCKS_COLLISION_BITMASK);
	bottomRocksBody->setCollisionBitmask(ROCKS_COLLISION_BITMASK);
	topRocksBody->setContactTestBitmask(true);
	bottomRocksBody->setContactTestBitmask(true);

	topRocks->setPhysicsBody(topRocksBody);
	bottomRocks->setPhysicsBody(bottomRocksBody);

	topRocks->setTag(RockTagNum);
	RockTagNum++;
	bottomRocks->setTag(RockTagNum);
	RockTagNum++;

	//set bottom Rocks to top and account for gap size
	topRocks->setPosition(Point(visibleSize.width + topRocks->getContentSize().width + origin.x, topRocksPosition));
	bottomRocks->setPosition(Point(topRocks->getPositionX(), topRocksPosition - (Sprite::create("Ball.png")->getContentSize().height*ROCKS_GAP) - topRocks->getContentSize().height));

	layer->addChild(topRocks, 1000);
	layer->addChild(bottomRocks, 1000);

	/*auto topRocksAction =  MoveBy::create(ROCKS_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));*/

	auto topRocksAction = MoveBy::create(ROCKS_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));

	auto bottomRocksAction = MoveBy::create(ROCKS_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width*1.5, 0));

	topRocks->runAction(topRocksAction);
	bottomRocks->runAction(bottomRocksAction);
}