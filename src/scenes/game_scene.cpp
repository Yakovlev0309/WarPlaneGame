#include "game_scene.h"
#include "game_over_scene.h"
#include "../definitions.h"
#include "../characters/bomber.h"
#include "../characters/fighter.h"
#include "../characters/bird.h"

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

	srand((unsigned)time(NULL));

	return true;
}

void Game::gameOver()
{
	mouseListener->setEnabled(false);
	contactListener->setEnabled(false);

	onMouseUp(nullptr);

	unscheduleAllCallbacks();
	unscheduleUpdate();

	Scene* scene = GameOver::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

	delete player;
}

bool Game::onContactBegin(const cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	switch (a->getCollisionBitmask() | b->getCollisionBitmask())
	{
	case (COLLISION_WITH_ENEMY_BITMASK):
		if (a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)
		{
			removeChild(b->getNode());
		}
		else if (b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)
		{
			removeChild(a->getNode());
		}
		gameOver();
		break;
	case COLLISION_WITH_BIRD_BITMASK:
		if (a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)
		{
			removeChild(b->getNode());
		}
		else if (b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK)
		{
			removeChild(a->getNode());
		}
		gameOver();
		break;
	case PLAYER_HIT_BITMASK:
		// remove bullet and target
		removeChild(a->getNode());
		removeChild(b->getNode());
		break;
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
	else if (gameTime >= 120)
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

	if (player->getPosition().y - player->getSize().height / 2 <= 10)
	{
		gameOver();
	}
}

void Game::updateGameTime(float dt)
{
	gameTime += dt;
}

void Game::spawnEnemy(float dt)
{
	float height = 0;
	float speed = 0;
	Enemy* enemy;

	switch (rand() % 3)
	{
	case 0:
		switch (rand() % 2)
		{
		case 0:
			height = visibleSize.height / 3 * CCRANDOM_0_1() + visibleSize.height / 3 * 2;
			speed = HIGH_SPEED;
			break;
		default:
			height = visibleSize.height / 3 * CCRANDOM_0_1() + visibleSize.height / 3;
			speed = MEDIUM_SPEED;
			break;
		}
		enemy = new Bomber(this, height, speed);
		break;
	case 1:
		height = visibleSize.height / 3 * CCRANDOM_0_1() + visibleSize.height / 3;
		switch (rand() % 2)
		{
		case 0:
			speed = HIGH_SPEED;
			break;
		default:
			speed = MEDIUM_SPEED;
			break;
		}
		enemy = new Fighter(this, height, speed);
		break;
	default:
		height = visibleSize.height / 3 * CCRANDOM_0_1();
		speed = LOW_SPEED;
		enemy = new Bird(this, height, speed);
		break;
	}
}
