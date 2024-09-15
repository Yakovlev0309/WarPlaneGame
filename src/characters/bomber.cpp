#include "bomber.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Bomber*> Bomber::bombers;

Bomber::Bomber(float height, float speed) : currentHealth(BOMBER_HEALTH)
{
	sprite = Sprite::create("images/bomber.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	float dx = 105;
	float dy = 44;
	Vec2* points = new Vec2[6]{
		Vec2(205 - dx, 5 - dy),
		Vec2(205 - dx, 83 - dy),
		Vec2(185 - dx, 50 - dy),
		Vec2(5 - dx, 50 - dy),
		Vec2(5 - dx, 10 - dy),
		Vec2(185 - dx, 10 - dy)
	};
	PhysicsBody* body = PhysicsBody::createPolygon(points, 6);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	body->setCategoryBitmask(BOMBER_COLLISION_BITMASK);
	body->setCollisionBitmask(
		PLAYER_HIT_BOMBER_BITMASK |
		COLLISION_WITH_BOMBER_BITMASK |
		METEORITE_COLLISION_WITH_BOMBER_BITMASK);
	body->setContactTestBitmask(
		PLAYER_HIT_BOMBER_BITMASK |
		COLLISION_WITH_BOMBER_BITMASK |
		METEORITE_COLLISION_WITH_BOMBER_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	bombers.push_back(this);
}

Bomber::~Bomber()
{
	auto bomber = std::find(bombers.begin(), bombers.end(), this);
	if (bomber != bombers.end())
	{
		bombers.erase(bomber);
	}
}

void Bomber::removeOutOfScreenSprites()
{
	std::vector<Bomber*> forDeletion;
	for (Bomber* bomber : bombers)
	{
		if (!bomber->isOnScreen())
		{
			forDeletion.push_back(bomber);
		}
	}
	for (Bomber* bomber : forDeletion)
	{
		delete bomber;
	}
}

Bomber* Bomber::getByPhysicsBody(PhysicsBody* body)
{
	for (Bomber* bomber : bombers)
	{
		if (bomber->sprite->getPhysicsBody() == body)
		{
			return bomber;
		}
	}
	return nullptr;
}

void Bomber::removeAll()
{
	for (int i = 0; i < bombers.size(); ++i)
	{
		try
		{
			delete bombers.at(i);
		}
		catch (...) {}
	}
	bombers.clear();
}

void Bomber::getDamage(PhysicsBody* body, unsigned int damage)
{
	for (Bomber* bomber : bombers)
	{
		if (bomber->sprite->getPhysicsBody() == body)
		{
			bomber->getDamage(damage);
			break;
		}
	}
}

void Bomber::getDamage(unsigned int damage)
{
	currentHealth -= damage;
}

unsigned int Bomber::getCurrentHealth()
{
	return currentHealth;
}

