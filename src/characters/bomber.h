#ifndef _BOMBER_H_
#define _BOMBER_H_

#include "cocos2d.h"
#include "enemy.h"

class Bomber : public Enemy
{
public:
	static void create(float height, float speed);
	static void removeOutOfScreenSprites();

	static cocos2d::Vector<cocos2d::Sprite*> bombers;
};

#endif // _BOMBER_H_
