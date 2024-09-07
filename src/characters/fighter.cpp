#include "fighter.h"
#include "../definitions.h"

USING_NS_CC;

Fighter::Fighter(Scene* gameScene, const Point& position)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	sprite = Sprite::create("images/fighter.png");
	sprite->setPosition(position);

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setCategoryBitmask(ENEMY_COLLISION_BITMASK);
	body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(false);

	sprite->setPhysicsBody(body);

	gameScene->addChild(sprite, 10); // why 10?
}

void Fighter::move(MoveBy* action)
{
	sprite->runAction(action);
}

Size Fighter::getSize()
{
	return sprite->getContentSize();
}
