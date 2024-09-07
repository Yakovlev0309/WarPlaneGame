#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "cocos2d.h"

class Fighter
{
public:
	Fighter(cocos2d::Scene* gameScene, const cocos2d::Point& position);

	void move(cocos2d::MoveBy* action);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* sprite;
};

#endif // _FIGHTER_H_

