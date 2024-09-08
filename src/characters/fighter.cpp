#include "fighter.h"
#include "../definitions.h"

USING_NS_CC;

Fighter::Fighter(Scene* gameScene, float height, float speed)
{
	scene = gameScene;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	scheduler = Director::getInstance()->getScheduler();

	sprite = Sprite::create("images/fighter.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	sprite->setPhysicsBody(body);

	scene->addChild(sprite, 100);
}

Fighter::~Fighter()
{
	scene->removeChild(sprite);
}

void Fighter::fire()
{
	scheduler->schedule(SEL_SCHEDULE(&Fighter::shot), this, PLAYER_GUN_RATE, false);
}

void Fighter::shot(float dt)
{
	Sprite* bulletSprite = Sprite::create("images/bullet.png");
	bulletSprite->setPosition(sprite->getPosition());

	PhysicsBody* body = PhysicsBody::createBox(bulletSprite->getContentSize());
	body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(true);
	body->setVelocity(Vec2(-BULLET_SPEED, 0));

	bulletSprite->setPhysicsBody(body);

	scene->addChild(bulletSprite, 90);
}

void Fighter::stopFire()
{
	scheduler->unschedule(SEL_SCHEDULE(&Fighter::shot), this);
}
