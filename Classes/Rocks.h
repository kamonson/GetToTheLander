#ifndef __ROCKS_H__
#define __ROCKS_H__

#include "cocos2d.h"

class Rocks
{
public:
	Rocks();

	void SpawnRocks(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	int RockTagNum=0;
    
};

#endif // __ROCKS_H__
