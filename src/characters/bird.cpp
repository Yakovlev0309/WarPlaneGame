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
	for (int i = 0; i < birds.size(); ++i)
	{
		try
		{
			delete birds.at(i);
		}
		catch(...) {}
	}
	birds.clear();
}

void Bird::changeRandomBirdHeight(float lower, float higher)
{
	if (birds.size() > 0)
	{
		birds.at(rand() % birds.size())->changeHeight(lower, higher);
	}
}

void Bird::changeHeight(float lower, float higher)
{
	if (rand() % int(1 / CHANCE_TO_CHANGE_BIRD_HEIGHT) == 0)
	{
		float speed = 0;
		if (sprite->getPositionY() - BIRD_HEIGHT_SPEED * BIRD_HEIGHT_TIME > lower)
		{
			if (sprite->getPositionY() + BIRD_HEIGHT_SPEED * BIRD_HEIGHT_TIME < higher)
			{
				speed = rand() % 2 == 0 ? -BIRD_HEIGHT_SPEED : BIRD_HEIGHT_SPEED;
			}
			else
			{
				speed = -BIRD_HEIGHT_SPEED;
			}
		}
		else
		{
			if (sprite->getPositionY() + BIRD_HEIGHT_SPEED * BIRD_HEIGHT_TIME < higher)
			{
				speed = BIRD_HEIGHT_SPEED;
			}
		}

		sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, speed));

		std::function<void(float)> stopChangingHeight = [&](float dt) {
			sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, 0));
			};

		sprite->scheduleOnce(stopChangingHeight, BIRD_HEIGHT_TIME, "stopChangingHeightFunction");
	}
}
