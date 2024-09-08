#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"

class Player : public cocos2d::Ref
{
public:
	Player(cocos2d::Scene* gameScene, const cocos2d::Point& position);
	~Player();

	void fire();
	void stopFire();

	void updatePosition(const cocos2d::Vec2& position);
	cocos2d::Vec2 getPosition();
	cocos2d::Size getSize();
	cocos2d::Sprite* getSprite();

private:
	void shot(float dt);

	cocos2d::Scene* scene;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* planeSprite;

	cocos2d::Scheduler* scheduler;
};

#endif // _PLAYER_H_
