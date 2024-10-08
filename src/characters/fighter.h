#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "cocos2d.h"
#include "enemy.h"

class Fighter : public Enemy
{
public:
	Fighter(float height, float dpeed);
	~Fighter();

	static void removeOutOfScreenSprites();
	static Fighter* getByPhysicsBody(cocos2d::PhysicsBody* body);
	static void removeAll();

	static void checkFightersForDodge(const cocos2d::Vec2& playerPosition, float lower, float higher);

	void dodge(float lower, float higher);
	void fire();

	void getDamage(unsigned int damage);

	unsigned int getCurrentHealth();

	static std::vector<Fighter*> fighters;
	static std::vector<Fighter*> firingFighters;

private:
	void shot();
	void stopFire();

	unsigned int currentHealth;
};

#endif // _FIGHTER_H_
