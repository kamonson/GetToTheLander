#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) {
		sceneWorld = world;
	}
	void SpawnPipe(float dt);
		cocos2d::PhysicsWorld *sceneWorld;
		
		//declare contact
		bool onContactBegin(cocos2d::PhysicsContact &contact);

		//delcare movement
		bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event);

		void StopFlying(float dt);
		void update(float dt);

		Pipe pipe;

		//initialize with pointer because it does not have defualt constructor, use constructor passing a layer
		Bird *bird;

		//initialize points
		unsigned int score;

		cocos2d::Label *scoreLabel;

};

#endif // __GAME_SCENE_H__
