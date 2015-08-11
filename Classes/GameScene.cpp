#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//let see colision
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//make gravity
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/BKGMusic.mp3",true);
	//create a background for game
	//for testing on pc
	//auto backgroundSprite = Sprite::create("C:\\Users\\Kyle\\Documents\\GitHub\\GetToTheLander\\Resources\\iphone\\GameBackground.png");
	//for platform:
	auto backgroundSprite = Sprite::create("GameBackground.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	
	auto edgeBody = PhysicsBody::createBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
	edgeBody->setCollisionBitmask(EDGE_COLLISION_BITMASK);
	edgeBody->setDynamic(true);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(-100, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	//spawn Rocks based on screen size
	this->schedule(schedule_selector(GameScene::SpawnRocks), ROCKS_SPAWN_FREQUENCY * visibleSize.width);
	
	//spawn pipes based on screen size
	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width );

	//spawn Mights based on screen size
	this->schedule(schedule_selector(GameScene::SpawnMights), MIGHTS_SPAWN_FREQUENCY * visibleSize.width);


	//initialize bird
	bird = new Bird(this);

	//add listener for contact
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	score = 0;

	//create a string to hold the running score in cocos library (auto could work)
	__String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
	scoreLabel->setColor(Color3B::WHITE);
	//set score position
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
	//high value denotes forward position
	this->addChild(scoreLabel, 10000);

	//add listener for touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	//number of param is calback number
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->scheduleUpdate();

    return true;
}

//make pipes
void GameScene::SpawnPipe(float dt){
	pipe.SpawnPipe(this);
}

//response to contact with obstacle
bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//if something colides with something else
	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKS_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && ROCKS_COLLISION_BITMASK == a->getCollisionBitmask()) /*|| (BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && EDGE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && EDGE_COLLISION_BITMASK == a->getCollisionBitmask())*/){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");
		auto scene = GameOverScene::createScene( score);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		//output score on death
		// CCLOG("SCORE: %i", score); no need to write to output, score in game
		//end bkg music
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
	{ 
	//	CCLOG("Point Scored");no longer needed to write to output
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");
		score ++;
		__String *tempScore = __String::createWithFormat("%i", score);
		scoreLabel->setString(tempScore->getCString());	
	}
	else if ((EDGE_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (EDGE_COLLISION_BITMASK == a->getCollisionBitmask() && ROCKS_COLLISION_BITMASK == b->getCollisionBitmask())){
		//remove sprites as they get near edge--fine tune the number 100 is close
		if (b->getNode()->getPositionX() < 100){
			b->getNode()->removeFromParent();
		}
	}
	return true;
}


//make Mights
void GameScene::SpawnMights(float dt){
	mights.SpawnMights(this);
}

//make Rocks
void GameScene::SpawnRocks(float dt){
	rocks.SpawnRocks(this);
}

////response to contact with obstacle
//bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){
//	PhysicsBody *a = contact.getShapeA()->getBody();
//	PhysicsBody *b = contact.getShapeB()->getBody();
//
//	//if something colides with something else
//	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())){
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");
//		auto scene = GameOverScene::createScene(score);
//		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
//		//output score on death
//		// CCLOG("SCORE: %i", score); no need to write to output, score in game
//	}
//	else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
//	{
//		//	CCLOG("Point Scored");no longer needed to write to output
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");
//		score++;
//		__String *tempScore = __String::createWithFormat("%i", score);
//		scoreLabel->setString(tempScore->getCString());
//	}
//	return true;
//}


//implement touch
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
	bird->Fly();

	this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);

	return true;
}

//implement stop flying

void GameScene::StopFlying(float dt)
{
	bird->StopFlying();
}

void GameScene::update(float dt)
{
	bird->Fall();
}