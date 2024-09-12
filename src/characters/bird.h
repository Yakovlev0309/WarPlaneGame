#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"
#include "enemy.h"

class Bird : public Enemy
{
public:
	Bird(float height, float speed);
	~Bird();

	static void removeOutOfScreenSprites();
	static void removeByPhysicsBody(cocos2d::PhysicsBody* body);
	static void removeAll();

	static void changeRandomBirdHeight(float lower, float higher);

	void changeHeight(float lower, float higher);

	static std::vector<Bird*> birds;

private:
	bool swing;
};

#endif // _BIRD_H_
