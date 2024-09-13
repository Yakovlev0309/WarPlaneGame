#include "meteorite.h"
#include "../definitions.h"

USING_NS_CC;

Meteorite::Meteorite(float xPosition)
{
	sprite = Sprite::create("images/meteorite.png");
	sprite->setPosition(Vec2(xPosition, visibleSize.height + sprite->getContentSize().height));

	PhysicsBody* body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	body->setGravityEnable(false);
	body->setRotationEnable(true);

	if (rand() % 2 == 0)
	{
		body->setVelocity(Vec2(-METEORITE_X_SPEED, -METEORITE_Y_SPEED));
	}
	else
	{
		body->setVelocity(Vec2(METEORITE_X_SPEED, -METEORITE_Y_SPEED));
	}

	body->setCategoryBitmask(METEORITE_COLLISION_BITMASK);
	body->setCollisionBitmask(
		METEORITE_COLLISION_WITH_PLAYER_BITMASK | 
		METEORITE_COLLISION_WITH_BOMBER_BITMASK | 
		METEORITE_COLLISION_WITH_FIGHTER_BITMASK);
	body->setContactTestBitmask(
		METEORITE_COLLISION_WITH_PLAYER_BITMASK | 
		METEORITE_COLLISION_WITH_BOMBER_BITMASK | 
		METEORITE_COLLISION_WITH_FIGHTER_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}
}
