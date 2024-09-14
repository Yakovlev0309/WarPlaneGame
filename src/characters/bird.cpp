#include "bird.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Bird*> Bird::birds;

Bird::Bird(float height, float speed)
{
	sprite = Sprite::create("images/bird.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize() * 0.8);
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

	swing = false;
	std::function<void(float)> swingFunc = [&](float dt) {
		if (swing)
		{
			sprite->setTexture("images/bird.png");
		}
		else
		{
			sprite->setTexture("images/bird_swing.png");
		}
		swing = !swing;
		};

	sprite->schedule(swingFunc, 0.2f, "swingFunc");
}

Bird::~Bird()
{
	auto b = std::find(birds.begin(), birds.end(), this);
	if (b != birds.end())
	{
		birds.erase(b);
	}
}

void Bird::removeOutOfScreenSprites()
{
	for (Bird* bird : birds)
	{
		if (!bird->isOnScreen())
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
	if (rand() % int(1 / BIRD_CHANCE_TO_CHANGE_HEIGHT) == 0)
	{
		float speed = 0;
		if (sprite->getPositionY() - BIRD_Y_SPEED * BIRD_HEIGHT_CHANGING_TIME > lower)
		{
			if (sprite->getPositionY() + BIRD_Y_SPEED * BIRD_HEIGHT_CHANGING_TIME < higher)
			{
				speed = rand() % 2 == 0 ? -BIRD_Y_SPEED : BIRD_Y_SPEED;
			}
			else
			{
				speed = -BIRD_Y_SPEED;
			}
		}
		else
		{
			if (sprite->getPositionY() + BIRD_Y_SPEED * BIRD_HEIGHT_CHANGING_TIME < higher)
			{
				speed = BIRD_Y_SPEED;
			}
		}

		sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, speed));

		std::function<void(float)> stopChangingHeight = [&](float dt) {
			sprite->getPhysicsBody()->setVelocity(Vec2(sprite->getPhysicsBody()->getVelocity().x, 0));
			};

		sprite->scheduleOnce(stopChangingHeight, BIRD_HEIGHT_CHANGING_TIME, "stopChangingHeightFunction");
	}
}
