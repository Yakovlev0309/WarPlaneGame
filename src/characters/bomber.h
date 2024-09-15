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
	static Bomber* getByPhysicsBody(cocos2d::PhysicsBody* body);
	static void removeAll();

	static void getDamage(cocos2d::PhysicsBody* body, unsigned int damage);
	void getDamage(unsigned int damage);

	unsigned int getCurrentHealth();

	static std::vector<Bomber*> bombers;

private:
	unsigned int currentHealth;
};

#endif // _BOMBER_H_
