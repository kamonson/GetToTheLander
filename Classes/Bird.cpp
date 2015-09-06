#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//make sprite img
	flappyBird = Sprite::create("Ball.png");
	flappyBird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//give sprite circle physics
	auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width / 2);
	flappyBody->setDynamic(true);

	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);

	flappyBird->setPhysicsBody(flappyBody);

	layer->addChild(flappyBird, 100);

	isFalling = true;
}

void Bird::Fall(){
	if (true == isFalling)
	{
		//eliminate motion from contact...may delete
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
		y = flappyBird->getPositionY();

	}
	else{
		//eliminate motion from contact...may delete
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + (BIRD_FALLING_SPEED * visibleSize.height));

	}
}

float Bird::getPosX(){
	return flappyBird->getPositionX();
};

float Bird::getPosY(){
	return y;
};
