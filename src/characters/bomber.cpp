#include "bomber.h"
#include "../definitions.h"

USING_NS_CC;

Vector<Sprite*> Bomber::bombers;

void Bomber::create(float height, float speed)
{
	Sprite* sprite = Sprite::create("images/bomber.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, height));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setVelocity(Vec2(-speed, 0));

	body->setCategoryBitmask(ENEMY_COLLISION_BITMASK);
	body->setCollisionBitmask(PLAYER_HIT_BITMASK | COLLISION_WITH_ENEMY_BITMASK);
	body->setContactTestBitmask(PLAYER_HIT_BITMASK | COLLISION_WITH_ENEMY_BITMASK);

	sprite->setPhysicsBody(body);

	if (scene)
	{
		scene->addChild(sprite, 100);
	}

	enemies.pushBack(sprite);
	bombers.pushBack(sprite);
}

void Bomber::removeOutOfScreenSprites()
{
	for (Sprite* bomber : bombers)
	{
		if (!isOnScreen(bomber))
		{
			scene->removeChild(bomber, true);
			enemies.eraseObject(bomber);
			bombers.eraseObject(bomber);
			break;
		}
	}
}
