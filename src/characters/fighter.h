#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "cocos2d.h"
#include "enemy.h"

class Fighter : public Enemy
{
public:
	static void create(float height, float speed);
	static void removeOutOfScreenSprites();

	static void fire();
	static void stopFire();

	static cocos2d::Vector<cocos2d::Sprite*> fighters;

private:
	static void shot(float dt);

	static cocos2d::Scheduler* scheduler;
};

#endif // _FIGHTER_H_
