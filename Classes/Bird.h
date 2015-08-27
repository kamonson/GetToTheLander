#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Bird
{
public:
	Bird(cocos2d::Layer * layer);
	//added sound inline to ensure play
	void Fall();
	void Fly(){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Wing.mp3", 0, 1.0, 0.0, 0.5);
		isFalling = false;
		y = flappyBird->getPositionY();
	};
	void StopFlying() { isFalling = true; }
	bool getFalling(){ return isFalling; }
	void setFalling(bool fall){ isFalling = fall; };
	float getPosX();
	float getPosY();


private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	//make sprite landerjumper

	cocos2d::Sprite *flappyBird;

	bool isFalling;

	float x;
	float y;
};

#endif // __BIRD_H__
