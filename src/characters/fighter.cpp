#include "fighter.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Fighter*> Fighter::fighters;
std::vector<Fighter*> Fighter::firingFighters;

Fighter::Fighter(float height, float speed)
{
	sprite = Sprite::create("images/fighter.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	float dx = 50;
	float dy = 31;
	Vec2* points = new Vec2[6]{
		Vec2(95 - dx, 5 - dy),
		Vec2(95 - dx, 57 - dy),
		Vec2(60 - dx, 50 - dy),
		Vec2(5 - dx, 50 - dy),
		Vec2(5 - dx, 30 - dy),
		Vec2(60 - dx, 30 - dy)
	};
	PhysicsBody* body = PhysicsBody::createPolygon(points, 6);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	body->setCategoryBitmask(FIGHTER_COLLISION_BITMASK);
	body->setCollisionBitmask(
		PLAYER_HIT_FIGHTER_BITMASK | 
		COLLISION_WITH_FIGHTER_BITMASK | 
		METEORITE_COLLISION_WITH_FIGHTER_BITMASK);
	body->setContactTestBitmask(
		PLAYER_HIT_FIGHTER_BITMASK | 
		COLLISION_WITH_FIGHTER_BITMASK | 
		METEORITE_COLLISION_WITH_FIGHTER_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	fighters.push_back(this);
}

Fighter::~Fighter()
{
	//stopFire();
	auto fighter = std::find(fighters.begin(), fighters.end(), this);
	if (fighter != fighters.end())
	{
		fighters.erase(fighter);
	}
}

void Fighter::removeOutOfScreenSprites()
{
	std::vector<Fighter*> forDeletion;
	for (Fighter* fighter : fighters)
	{
		if (!fighter->isOnScreen())
		{
			forDeletion.push_back(fighter);
		}
	}
	for (Fighter* fighter : forDeletion)
	{
		delete fighter;
	}
}

void Fighter::removeByPhysicsBody(PhysicsBody* body)
{
	for (Fighter* fighter : fighters)
	{
		if (fighter->sprite->getPhysicsBody() == body)
		{
			delete fighter;
			break;
		}
	}
}

void Fighter::removeAll()
{
	for (int i = 0; i < fighters.size(); ++i)
	{
		try
		{
			delete fighters.at(i);
		}
		catch (...) {}
	}
	fighters.clear();
}

void Fighter::checkFightersForDodge(const cocos2d::Vec2& playerPosition, float lower, float higher)
{
	for (int i = 0; i < fighters.size(); ++i)
	{
		if (fighters.at(i)->sprite->getPositionX() > playerPosition.x &&
			fighters.at(i)->sprite->getPositionY() >= playerPosition.y - fighters.at(i)->sprite->getContentSize().height &&
			fighters.at(i)->sprite->getPositionY() <= playerPosition.y + fighters.at(i)->sprite->getContentSize().height)
		{
			fighters.at(i)->dodge(lower, higher);
		}
	}
}

void Fighter::dodge(float lower, float higher)
{
	float speed = 0;
	if (sprite->getPositionY() - FIGHTER_DODGING_Y_SPEED * FIGHTER_DODGING_TIME > lower)
	{
		if (sprite->getPositionY() + FIGHTER_DODGING_Y_SPEED * FIGHTER_DODGING_TIME < higher)
		{
			speed = rand() % 2 == 0 ? -FIGHTER_DODGING_Y_SPEED : FIGHTER_DODGING_Y_SPEED;
		}
		else
		{
			speed = -FIGHTER_DODGING_Y_SPEED;
		}
	}
	else
	{
		if (sprite->getPositionY() + FIGHTER_DODGING_Y_SPEED * FIGHTER_DODGING_TIME < higher)
		{
			speed = FIGHTER_DODGING_Y_SPEED;
		}
	}

	sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, speed));

	std::function<void(float)> stopDodging = [&](float dt) {
		sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, 0));
		};

	sprite->scheduleOnce(stopDodging, FIGHTER_DODGING_TIME, "stopDodgingFunction");
}

void Fighter::fire()
{
	//if (isOnRightSideOfScreen(sprite))
	{
		firingFighters.push_back(this);

		std::function<void(float)> shotLambda = [&](float dt) {
			shot();
			};
		std::function<void(float)> stopFireLambda = [&](float dt) {
			stopFire();
			};

		sprite->schedule(shotLambda, PLAYER_GUN_RATE, "fireFunction");
		sprite->scheduleOnce(stopFireLambda, FIGHTER_FIRE_TIME, "stopFireFunction");
	}
}

void Fighter::shot()
{
	Sprite* bulletSprite = Sprite::create("images/fighter_bullet.png");
	bulletSprite->setPosition(sprite->getPosition());

	PhysicsBody* body = PhysicsBody::createBox(bulletSprite->getContentSize() * 0.8);
	body->setGravityEnable(true);
	body->setVelocity(Vec2(-FIGHTER_BULLET_SPEED + sprite->getPhysicsBody()->getVelocity().x, 0));

	body->setCategoryBitmask(FIGHTER_BULLET_COLLISION_BITMASK);
	body->setCollisionBitmask(FIGHTER_HIT_PLAYER_BITMASK);
	body->setContactTestBitmask(FIGHTER_HIT_PLAYER_BITMASK);

	bulletSprite->setPhysicsBody(body);

	scene->addChild(bulletSprite, 90);
}

void Fighter::stopFire()
{
	sprite->unschedule("fireFunction");
	auto fighter = std::find(firingFighters.begin(), firingFighters.end(), this);
	if (fighter != firingFighters.end())
	{
		firingFighters.erase(fighter);
	}
}
