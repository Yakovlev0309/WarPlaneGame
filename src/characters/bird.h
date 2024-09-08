#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"
#include "enemy.h"

class Bird : public Enemy
{
public:
	Bird(cocos2d::Scene* gameScene, float height, float speed);
	~Bird();

private:
	cocos2d::Scheduler* scheduler;
};

#endif // _BIRD_H_
