#include "fighter.h"
#include "../definitions.h"

USING_NS_CC;

Vector<Sprite*> Fighter::fighters;
Scheduler* Fighter::scheduler;

void Fighter::create(float height, float speed)
{
	scheduler = Director::getInstance()->getScheduler();

	Sprite* sprite = Sprite::create("images/fighter.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	enemies.pushBack(sprite);
	fighters.pushBack(sprite);
}

void Fighter::removeOutOfScreenSprites()
{
	for (Sprite* fighter : fighters)
	{
		if (!isOnScreen(fighter))
		{
			scene->removeChild(fighter, true);
			enemies.eraseObject(fighter);
			fighters.eraseObject(fighter);
			break;
		}
	}
}

//void Fighter::fire()
//{
//	scheduler->schedule(SEL_SCHEDULE(&Fighter::shot), this, PLAYER_GUN_RATE, false);
//}
//
//void Fighter::shot(float dt)
//{
//	Sprite* bulletSprite = Sprite::create("images/bullet.png");
//	bulletSprite->setPosition(sprite->getPosition());
//
//	PhysicsBody* body = PhysicsBody::createBox(bulletSprite->getContentSize());
//	body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
//	body->setContactTestBitmask(true);
//	body->setGravityEnable(true);
//	body->setVelocity(Vec2(-BULLET_SPEED, 0));
//
//	bulletSprite->setPhysicsBody(body);
//
//	scene->addChild(bulletSprite, 90);
//}
//
//void Fighter::stopFire()
//{
//	scheduler->unschedule(SEL_SCHEDULE(&Fighter::shot), this);
//}
