#include "enemy.h"
#include "../definitions.h"

USING_NS_CC;

Scene* Enemy::scene = nullptr;
Size Enemy::visibleSize;
Vec2 Enemy::origin;

Enemy::Enemy() : sprite(nullptr)
{

}

Enemy::~Enemy()
{
	if (sprite)
	{
		sprite->unscheduleUpdate();
		sprite->unscheduleAllCallbacks();

		if (scene)
		{
			scene->removeChild(sprite, true);
		}
	}
}

void Enemy::init(Scene* gameScene)
{
	scene = gameScene;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

bool Enemy::isOnScreen()
{
	if (sprite->getPosition().x <= visibleSize.width + sprite->getContentSize().width &&
		sprite->getPosition().x >= -sprite->getContentSize().width)
		//if (sprite->getPosition().x >= -sprite->getContentSize().width)
	{
		return true;
	}
	return false;
}

bool Enemy::isOnRightSideOfScreen()
{
	if (sprite->getPosition().x <= visibleSize.width + sprite->getContentSize().width &&
		sprite->getPosition().x >= visibleSize.width / 2 + sprite->getContentSize().width)
	{
		return true;
	}
	return false;
}
