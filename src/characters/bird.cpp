#include "bird.h"
#include "../definitions.h"

USING_NS_CC;

Vector<Sprite*> Bird::birds;

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

	enemies.pushBack(sprite);
	birds.pushBack(sprite);
}

void Bird::removeOutOfScreenSprites()
{
	for (Sprite* bird : birds)
	{
		if (!isOnScreen(bird))
		{
			scene->removeChild(bird, true);
			enemies.eraseObject(bird);
			birds.eraseObject(bird);
			break;
		}
	}
}
