#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "cocos2d.h"
#include "enemy.h"

class Fighter : public Enemy
{
public:
	Fighter(cocos2d::Scene* gameScene, float height, float speed);
	~Fighter();

	void fire();
	void stopFire();

private:
	void shot(float dt);

	cocos2d::Scheduler* scheduler;
};

#endif // _FIGHTER_H_
