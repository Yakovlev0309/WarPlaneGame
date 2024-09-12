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
	static void stopAllFirings();
	static void removeByPhysicsBody(cocos2d::PhysicsBody* body);
	static void removeAll();

	static void checkFightersForDodge(const cocos2d::Vec2& playerPosition, float lower, float higher);

	void dodge(float lower, float higher);
	void fire();

	static std::vector<Fighter*> fighters;
	static std::vector<Fighter*> firingFighters;

private:
	void shot();
	void stopFire();
};

#endif // _FIGHTER_H_
