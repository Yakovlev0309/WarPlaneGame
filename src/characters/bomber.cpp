#include "bomber.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Bomber*> Bomber::bombers;

Bomber::Bomber(float height, float speed)
{
	sprite = Sprite::create("images/bomber.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	body->setCategoryBitmask(BOMBER_COLLISION_BITMASK);
	body->setCollisionBitmask(PLAYER_HIT_BOMBER_BITMASK | COLLISION_WITH_BOMBER_BITMASK);
	body->setContactTestBitmask(PLAYER_HIT_BOMBER_BITMASK | COLLISION_WITH_BOMBER_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	enemies.push_back(sprite);
	bombers.push_back(this);
}

Bomber::~Bomber()
{
	auto enemy = std::find(enemies.begin(), enemies.end(), sprite);
	if (enemy != enemies.end())
	{
		enemies.erase(enemy);
	}
	auto bomber = std::find(bombers.begin(), bombers.end(), this);
	if (bomber != bombers.end())
	{
		bombers.erase(bomber);
	}
	scene->removeChild(sprite, true);
}

void Bomber::removeOutOfScreenSprites()
{
	for (Bomber* bomber : bombers)
	{
		if (!isOnScreen(bomber->sprite))
		{
			delete bomber;
			break;
		}
	}
}

void Bomber::removeByPhysicsBody(PhysicsBody* body)
{
	for (Bomber* bomber : bombers)
	{
		if (bomber->sprite->getPhysicsBody() == body)
		{
			delete bomber;
			break;
		}
	}
}
