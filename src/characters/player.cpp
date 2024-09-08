#include "player.h"
#include "../definitions.h"

USING_NS_CC;

Player::Player(Scene* gameScene, const Point& position) : scene(gameScene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	scheduler = Director::getInstance()->getScheduler();

	planeSprite = Sprite::create("images/player.png");
	planeSprite->setPosition(position);

	PhysicsBody* planeBody = PhysicsBody::createBox(planeSprite->getContentSize());
	planeBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	planeBody->setContactTestBitmask(true);
	planeBody->setGravityEnable(false);
	planeBody->setRotationEnable(false);

	planeSprite->setPhysicsBody(planeBody);

	scene->addChild(planeSprite, 100);
}

void Player::fire()
{
	scheduler->schedule(SEL_SCHEDULE(&Player::shot), this, PLAYER_GUN_RATE, false);
}

void Player::shot(float dt)
{
	Sprite* bulletSprite = Sprite::create("images/bullet.png");
	bulletSprite->setPosition(planeSprite->getPosition());

	PhysicsBody* body = PhysicsBody::createBox(bulletSprite->getContentSize());
	body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(true);
	body->setVelocity(Vec2(BULLET_VELOCITY, 0)); // ???

	bulletSprite->setPhysicsBody(body);

	scene->addChild(bulletSprite, 90);

	//MoveBy* shotAction = MoveBy::create(visibleSize.width / BULLET_SPEED, Vec2(visibleSize.width, 0));
	//CallFunc* callback = CallFunc::create([&]() {
	//	scene->removeChild(bulletSprite);
	//	});
	//Sequence* shotSequence = Sequence::create(shotAction, callback, nullptr);
	//bulletSprite->runAction(shotSequence);
}

void Player::stopFire()
{
	scheduler->unschedule(SEL_SCHEDULE(&Player::shot), this);
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
