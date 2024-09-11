#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"

class Enemy
{
public:
	static void init(cocos2d::Scene* gameScene);

protected:
	static bool isOnScreen(cocos2d::Sprite* sprite);
	static bool isOnRightSideOfScreen(cocos2d::Sprite* sprite);

	static cocos2d::Scene* scene;
	static cocos2d::Size visibleSize;
	static cocos2d::Vec2 origin;

	//static cocos2d::Scheduler* scheduler;

	static std::vector<cocos2d::Sprite*> enemies;
};

#endif // _ENEMY_H_
