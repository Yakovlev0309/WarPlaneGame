#ifndef _BOMBER_H_
#define _BOMBER_H_

#include "cocos2d.h"
#include "enemy.h"

class Bomber : public Enemy
{
public:
	Bomber(cocos2d::Scene* gameScene, float height, float speed);
	~Bomber();

private:
	cocos2d::Scheduler* scheduler;
};

#endif // _BOMBER_H_
