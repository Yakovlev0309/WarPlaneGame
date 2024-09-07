#include "game_scene.h"
#include "game_over_scene.h"
#include "../definitions.h"
#include "../characters/fighter.h"

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

	//PhysicsBody* playerZoneBody = PhysicsBody::createEdgeBox(Size(visibleSize.width / 3, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//playerZoneBody->setCategoryBitmask(PLAYER_ZONE_COLLISION_BITMASK);
	//playerZoneBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

	//Node* playerZoneNode = Node::create();
	//playerZoneNode->setContentSize(Size(visibleSize.width / 3, visibleSize.height));
	//playerZoneNode->setPhysicsBody(playerZoneBody);
	//playerZone = playerZoneNode->getBoundingBox();
	//addChild(playerZoneNode);

	player = new Player(this, Vec2(visibleSize.width / 2 / 3 + origin.x, visibleSize.height / 2 + origin.y));
	targetPlayerPosition = player->getPosition();

	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	schedule(CC_SCHEDULE_SELECTOR(Game::spawnEnemy), 3.0f);

	scheduleUpdate();

	return true;
}

void Game::gameOver()
{
	Scene* scene = GameOver::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

bool Game::onContactBegin(const cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == ENEMY_COLLISION_BITMASK && b->getCollisionBitmask() == PLAYER_COLLISION_BITMASK ||
		a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK && b->getCollisionBitmask() == ENEMY_COLLISION_BITMASK)
	{
		gameOver();
	}

	return true;
}

void Game::onMouseMove(EventMouse* event)
{
	Vec2 mouseLocation = event->getLocation();
	mouseLocation.y = Director::getInstance()->getVisibleSize().height - mouseLocation.y;
	if (playerZone.containsPoint(mouseLocation))
	{
		targetPlayerPosition = mouseLocation;
	}
	else
	{
		targetPlayerPosition.y = mouseLocation.y;
	}
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
	// FIXME сделать возможным движение по 1/3 экрана

	if (std::abs(targetPlayerPosition.x - player->getPosition().x) > 2 ||
		std::abs(targetPlayerPosition.y - player->getPosition().y) > 2)
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
	Fighter* fighter = new Fighter(this, Point(visibleSize.width, visibleSize.height * CCRANDOM_0_1()));
	MoveBy* fighterAction = MoveBy::create(visibleSize.width / FIGHTER_SPEED, Vec2(-visibleSize.width - fighter->getSize().width / 2, 0));
	fighter->move(fighterAction);
}
