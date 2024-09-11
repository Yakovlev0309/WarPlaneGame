#include "bird.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Bird*> Bird::birds;

Bird::Bird(float height, float speed)
{
	sprite = Sprite::create("images/bird.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	body->setCategoryBitmask(BIRD_COLLISION_BITMASK);
	body->setCollisionBitmask(COLLISION_WITH_BIRD_BITMASK);
	body->setContactTestBitmask(COLLISION_WITH_BIRD_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	birds.push_back(this);
}

Bird::~Bird()
{
	auto b = std::find(birds.begin(), birds.end(), this);
	if (b != birds.end())
	{
		birds.erase(b);
	}
	scene->removeChild(sprite, true);
}

void Bird::removeOutOfScreenSprites()
{
	for (Bird* bird : birds)
	{
		if (!isOnScreen(bird->sprite))
		{
			delete bird;
			break;
		}
	}
}

void Bird::removeByPhysicsBody(PhysicsBody* body)
{
	for (Bird* bird : birds)
	{
		if (bird->sprite->getPhysicsBody() == body)
		{
			delete bird;
			break;
		}
	}
}

void Bird::removeAll()
{
	for (Bird* bird : birds)
	{
		delete bird;
	}
	birds.clear();
}

void Bird::setYVelocity(float yVelocity)
{
	sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, yVelocity));
}

float Bird::getPositionY()
{
	return sprite->getPositionY();
}
