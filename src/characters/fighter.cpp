#include "fighter.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Fighter*> Fighter::fighters;
std::vector<Fighter*> Fighter::firingFighters;

Fighter::Fighter(float height, float speed)
{
	sprite = Sprite::create("images/fighter.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	body->setCategoryBitmask(FIGHTER_COLLISION_BITMASK);
	body->setCollisionBitmask(PLAYER_HIT_FIGHTER_BITMASK | COLLISION_WITH_FIGHTER_BITMASK);
	body->setContactTestBitmask(PLAYER_HIT_FIGHTER_BITMASK | COLLISION_WITH_FIGHTER_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	enemies.push_back(sprite);
	fighters.push_back(this);
}

Fighter::~Fighter()
{
	stopFire();
	auto enemy = std::find(enemies.begin(), enemies.end(), sprite);
	if (enemy != enemies.end())
	{
		enemies.erase(enemy);
	}
	auto fighter = std::find(fighters.begin(), fighters.end(), this);
	if (fighter != fighters.end())
	{
		fighters.erase(fighter);
	}
	scene->removeChild(sprite, true);
}

void Fighter::removeOutOfScreenSprites()
{
	// TODO удалять все спрайты за экраном, а не только первый попавшийся
	for (Fighter* fighter : fighters)
	{
		if (!isOnScreen(fighter->sprite))
		{
			delete fighter;
			break;
		}
	}
}

void Fighter::stopAllFirings()
{
	for (int i = 0; i < firingFighters.size(); ++i)
	{
		firingFighters.at(i)->stopFire();
	}
	firingFighters.clear();

	// Удаление всех истребителей
	//for (int i = 0; i < fighters.size(); ++i)
	//{
	//	delete fighters.at(i);
	//}
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

		scene->schedule(shotLambda, PLAYER_GUN_RATE, "fireFunction");
		scene->scheduleOnce(stopFireLambda, FIGHTER_FIRE_TIME, "stopFireFunction");
	}
}

void Fighter::shot()
{
	Sprite* bulletSprite = Sprite::create("images/fighter_bullet.png");
	bulletSprite->setPosition(sprite->getPosition());

	PhysicsBody* body = PhysicsBody::createBox(bulletSprite->getContentSize());
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
	scene->unschedule("fireFunction");
	auto fighter = std::find(firingFighters.begin(), firingFighters.end(), this);
	if (fighter != firingFighters.end())
	{
		firingFighters.erase(fighter);
	}
}
