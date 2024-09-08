#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"

class Player
{
public:
	Player(cocos2d::Scene* gameScene, const cocos2d::Point& position);

	void updatePosition(const cocos2d::Vec2& position);
	cocos2d::Vec2 getPosition();
	cocos2d::Size getSize();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* planeSprite;
};

#endif // _PLAYER_H_

