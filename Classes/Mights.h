#ifndef __MIGHTS_H__
#define __MIGHTS_H__

#include "cocos2d.h"

class Mights
{
public:
	Mights();

	void SpawnMights(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
    
};

#endif // __MIGHTS_H__
