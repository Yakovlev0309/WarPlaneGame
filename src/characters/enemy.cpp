#include "enemy.h"
#include "../definitions.h"

USING_NS_CC;

Scene* Enemy::scene = nullptr;
Size Enemy::visibleSize;
Vec2 Enemy::origin;
Vector<Sprite*> Enemy::enemies;

void Enemy::init(Scene* gameScene)
{
	scene = gameScene;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

bool Enemy::isOnScreen(Sprite* sprite)
{
	//return scene->getBoundingBox().containsPoint(sprite->getPosition());

	if (sprite->getPosition().x <= visibleSize.width + sprite->getContentSize().width &&
		sprite->getPosition().x >= -sprite->getContentSize().width)
	{
		return true;
	}
	return false;
}
