#include "player.h"
#include "../definitions.h"

USING_NS_CC;

Player::Player(Scene* gameScene, const Point& position)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	planeSprite = Sprite::create("images/player.png");
	planeSprite->setPosition(position);

	PhysicsBody* planeBody = PhysicsBody::createBox(planeSprite->getContentSize());
	planeBody->setCategoryBitmask(PLAYER_COLLISION_BITMASK);
	planeBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	planeBody->setContactTestBitmask(true);
	planeBody->setGravityEnable(false);

	planeSprite->setPhysicsBody(planeBody);

	gameScene->addChild(planeSprite, 100); // why 100?
}

void Player::updatePosition(const Vec2& position)
{
	planeSprite->setPosition(position);
}

Vec2 Player::getPosition()
{
	return planeSprite->getPosition();
}

Size Player::getSize()
{
	return planeSprite->getContentSize();
}
