#include "game_scene.h"
#include "game_over_scene.h"
#include "../definitions.h"
//#include "../characters/fighter.h"

USING_NS_CC;

Scene* Game::createScene()
{
	Scene* scene = Game::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // red obstacles lines
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	Game* layer = Game::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool Game::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	background1 = Sprite::create("images/game.png");
	background1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(background1);
	background2 = Sprite::create("images/game.png");
	background2->setPosition(Point(visibleSize.width * 1.5, background1->getPositionY()));
	addChild(background2);

	gameTime = 0;
	schedule(CC_SCHEDULE_SELECTOR(Game::updateGameTime), 1.0f);

	player = new Player(this, Vec2(visibleSize.width / 2 / 3 + origin.x, visibleSize.height / 2 + origin.y));
	targetPlayerPosition = player->getPosition();

	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(Game::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Game::onMouseUp, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	schedule(CC_SCHEDULE_SELECTOR(Game::spawnEnemy), 2.0f);

	scheduleUpdate();

	return true;
}

void Game::gameOver()
{
	contactListener->setEnabled(false);
	mouseListener->setEnabled(false);
	unscheduleAllCallbacks();
	unscheduleUpdate();
	Scene* scene = GameOver::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

bool Game::onContactBegin(const cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() | b->getCollisionBitmask()) == GAME_OVER_BITMASK)
	{
		removeChild(a->getNode());
		removeChild(b->getNode());
		gameOver();
	}
	else if ((a->getCollisionBitmask() | b->getCollisionBitmask()) == PLAYER_HIT_BITMASK)
	{
		removeChild(a->getNode());
		removeChild(b->getNode());
	}

	return true;
}

void Game::onMouseMove(EventMouse* event)
{
	Vec2 mouseLocation = event->getLocation();
	mouseLocation.y = Director::getInstance()->getVisibleSize().height - mouseLocation.y;

	if (mouseLocation.x < visibleSize.width / 3 - player->getSize().width / 2)
	{
		targetPlayerPosition = mouseLocation;
	}
	else
	{
		targetPlayerPosition.y = mouseLocation.y;
	}
}

void Game::onMouseDown(EventMouse* event)
{
	player->fire();
}

void Game::onMouseUp(EventMouse* event)
{
	player->stopFire();
}

void Game::update(float dt)
{
	moveBackground(dt);
	movePlayer(dt);
}

void Game::moveBackground(float dt)
{
	static unsigned int acceleration = 1;
	if (gameTime >= 30)
	{
		acceleration = 2;
	}
	if (gameTime >= 120)
	{
		acceleration = 4;
	}

	background1->setPositionX(background1->getPositionX() - BACKGROUND_SPEED * dt * acceleration);
	background2->setPositionX(background2->getPositionX() - BACKGROUND_SPEED * dt * acceleration);

	if (background1->getPositionX() < -visibleSize.width / 2)
	{
		background1->setPositionX(background2->getPositionX() + visibleSize.width);
	}
	if (background2->getPositionX() < -visibleSize.width / 2)
	{
		background2->setPositionX(background1->getPositionX() + visibleSize.width);
	}
}

void Game::movePlayer(float dt)
{
	if (std::abs(targetPlayerPosition.x - player->getPosition().x) > 5 || // FIXME
		std::abs(targetPlayerPosition.y - player->getPosition().y) > 5)
	{
		Vec2 direction = targetPlayerPosition - player->getPosition();
		direction.normalize();

		Vec2 newPosition = player->getPosition() + direction * PLAYER_SPEED * dt;

		player->updatePosition(newPosition);
	}
}

void Game::updateGameTime(float dt)
{
	gameTime += dt;
}

void Game::spawnEnemy(float dt)
{
	Sprite* sprite = Sprite::create("images/fighter.png");
	sprite->setPosition(Point(visibleSize.width + sprite->getContentSize().width / 2, visibleSize.height / 3 * 2 * CCRANDOM_0_1() + visibleSize.height / 3));

	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setGravityEnable(false);
	body->setVelocity(Vec2(-FIGHTER_SPEED, 0));

	sprite->setPhysicsBody(body);

	addChild(sprite, 10);

	//MoveBy* action = MoveBy::create(visibleSize.width / FIGHTER_SPEED, Vec2(-visibleSize.width, 0));
	//CallFunc* callback = CallFunc::create([&]() {
	//	removeChild(sprite);
	//	});
	//Sequence* sequence = Sequence::create(action, callback, nullptr);
	//sprite->runAction(sequence);
}
