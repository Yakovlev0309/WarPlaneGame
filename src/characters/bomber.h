#ifndef _BOMBER_H_
#define _BOMBER_H_

#include "cocos2d.h"
#include "enemy.h"

class Bomber : public Enemy
{
public:
	Bomber(float height, float dpeed);
	~Bomber();

	static void removeOutOfScreenSprites();
	static void removeByPhysicsBody(cocos2d::PhysicsBody* body);
	static void removeAll();

	static std::vector<Bomber*> bombers;
};

#endif // _BOMBER_H_
