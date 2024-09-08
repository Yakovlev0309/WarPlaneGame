#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "cocos2d.h"

class Fighter
{
public:
	Fighter(cocos2d::Scene* gameScene, const cocos2d::Point& position);

	cocos2d::Size getSize();
	cocos2d::Sprite* getSprite();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* sprite;
};

#endif // _FIGHTER_H_

