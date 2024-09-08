#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"

class Enemy : public cocos2d::Ref
{
protected:
	Enemy();

	cocos2d::Scene* scene;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* sprite;
};

#endif // _ENEMY_H_
