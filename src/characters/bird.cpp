#include "bird.h"
#include "../definitions.h"

USING_NS_CC;

std::vector<Sprite*> Bird::birds;

void Bird::create(float height, float speed)
{
	Sprite* sprite = Sprite::create("images/bird.png");
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

	enemies.push_back(sprite);
	birds.push_back(sprite);
}

void Bird::removeOutOfScreenSprites()
{
	for (Sprite* bird : birds)
	{
		if (!isOnScreen(bird))
		{
			scene->removeChild(bird, true);
			auto enemy = std::find(enemies.begin(), enemies.end(), bird);
			if (enemy != enemies.end())
			{
				enemies.erase(enemy);
			}
			auto b = std::find(birds.begin(), birds.end(), bird);
			if (b != birds.end())
			{
				birds.erase(b);
			}
			break;
		}
	}
}
