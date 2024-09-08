#include "bird.h"
#include "../definitions.h"

USING_NS_CC;

Bird::Bird(Scene* gameScene, float height, float speed)
{
	scene = gameScene;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	scheduler = Director::getInstance()->getScheduler();

	sprite = Sprite::create("images/bird.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	sprite->setPhysicsBody(body);

	scene->addChild(sprite, 100);
}

Bird::~Bird()
{
	scene->removeChild(sprite);
}
