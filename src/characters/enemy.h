#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"

class Enemy
{
public:
	static void init(cocos2d::Scene* gameScene);

protected:
	bool isOnScreen();
	bool isOnRightSideOfScreen();

	static cocos2d::Scene* scene;
	static cocos2d::Size visibleSize;
	static cocos2d::Vec2 origin;

	cocos2d::Sprite* sprite;
};

#endif // _ENEMY_H_
