#include "player.h"
#include "../definitions.h"

USING_NS_CC;

Player::Player(Scene* gameScene, const Point& position) : scene(gameScene), currentHealth(PLAYER_HEALTH)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	scheduler = Director::getInstance()->getScheduler();

	planeSprite = Sprite::create("images/player.png");
	planeSprite->setPosition(position);

	float dx = 50;
	float dy = 31;
	Vec2* points = new Vec2[6] {
		Vec2(5 - dx, 5 - dy),
		Vec2(5 - dx, 57 - dy),
		Vec2(40 - dx, 50 - dy),
		Vec2(95 - dx, 50 - dy),
		Vec2(95 - dx, 30 - dy),
		Vec2(40 - dx, 30 - dy)
	};
	PhysicsBody* planeBody = PhysicsBody::createPolygon(points, 6);
	planeBody->setGravityEnable(false);
	planeBody->setRotationEnable(false);

	planeBody->setCategoryBitmask(PLAYER_COLLISION_BITMASK);
	planeBody->setCollisionBitmask(
		COLLISION_WITH_BOMBER_BITMASK | 
		COLLISION_WITH_FIGHTER_BITMASK | 
		COLLISION_WITH_BIRD_BITMASK | 
		FIGHTER_HIT_PLAYER_BITMASK | 
		METEORITE_COLLISION_WITH_PLAYER_BITMASK);
	planeBody->setContactTestBitmask(COLLISION_WITH_BOMBER_BITMASK | 
		COLLISION_WITH_FIGHTER_BITMASK | 
		COLLISION_WITH_BIRD_BITMASK | 
		FIGHTER_HIT_PLAYER_BITMASK | 
		METEORITE_COLLISION_WITH_PLAYER_BITMASK);

	planeSprite->setPhysicsBody(planeBody);

	scene->addChild(planeSprite, 100);

	hearts.reserve(HEARTS_COUNT);
	for (int i = 0; i < HEARTS_COUNT; ++i)
	{
		Sprite* heart = Sprite::create("images/heart.png");
		heart->setPosition(Point(heart->getContentSize().width * 2 + heart->getContentSize().width * i, visibleSize.height - heart->getContentSize().height));
		scene->addChild(heart, 200);
		hearts.push_back(heart);
	}
}

Player::~Player()
{
	scene->removeChild(planeSprite);
}

void Player::fire()
{
	scheduler->schedule(SEL_SCHEDULE(&Player::shot), this, PLAYER_GUN_RATE, false);
}

void Player::shot(float dt)
{
	Sprite* bulletSprite = Sprite::create("images/bullet.png");
	bulletSprite->setPosition(planeSprite->getPosition());

	PhysicsBody* body = PhysicsBody::createBox(bulletSprite->getContentSize() * 0.8);
	body->setGravityEnable(true);
	body->setVelocity(Vec2(BULLET_SPEED, 0));

	body->setCategoryBitmask(BULLET_COLLISION_BITMASK);
	body->setCollisionBitmask(PLAYER_HIT_BOMBER_BITMASK | PLAYER_HIT_FIGHTER_BITMASK);
	body->setContactTestBitmask(PLAYER_HIT_BOMBER_BITMASK | PLAYER_HIT_FIGHTER_BITMASK);

	bulletSprite->setPhysicsBody(body);

	scene->addChild(bulletSprite, 90);
}

void Player::stopFire()
{
	scheduler->unschedule(SEL_SCHEDULE(&Player::shot), this);
}

void Player::getDamage(unsigned int damage)
{
	currentHealth -= damage;

	if (currentHealth < hearts.size() * HEALTH_IN_ONE_HEART)
	{
		scene->removeChild(hearts[hearts.size() - 1], true);
		hearts.erase(--hearts.end());
	}
}

bool Player::hasHealth()
{
	if (currentHealth == 0)
	{
		return false;
	}
	return true;
}

void Player::death()
{
	for (Sprite* heart : hearts)
	{
		scene->removeChild(heart, true);
	}
	hearts.clear();
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

Sprite* Player::getSprite()
{
	return planeSprite;
}
