#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"
#include "enemy.h"

class Bird : public Enemy
{
public:
	static void create(float height, float speed);
	static void removeOutOfScreenSprites();

	static std::vector<cocos2d::Sprite*> birds;
};

#endif // _BIRD_H_
