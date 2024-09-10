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

	Bomber::init(this);
	Fighter::init(this);
	Bird::init(this);

	currentBird = nullptr;

	gameTime = 0;
	gameTimeLabel = Label::createWithTTF("seconds: 0", "fonts/Marker Felt.ttf", visibleSize.height * GAME_TIME_FONT_SIZE_FACTOR);
	gameTimeLabel->setColor(Color3B::ORANGE);
	gameTimeLabel->setPosition(Point(SCORE_N_TIME_PADDING_FACTOR * visibleSize.width + gameTimeLabel->getContentSize().width / 2,
		visibleSize.height - gameTimeLabel->getContentSize().height));
	addChild(gameTimeLabel, 200);

	score = 0;
	scoreLabel = Label::createWithTTF("score: 0", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE_FACTOR);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setPosition(Point(SCORE_N_TIME_PADDING_FACTOR * visibleSize.width + scoreLabel->getContentSize().width / 2,
		visibleSize.height - scoreLabel->getContentSize().height - gameTimeLabel->getContentSize().height));
	addChild(scoreLabel, 200);

	schedule(CC_SCHEDULE_SELECTOR(Game::updateGameTime), 1.0f);
	schedule(CC_SCHEDULE_SELECTOR(Game::spawnEnemy), 1.0f);
	schedule(CC_SCHEDULE_SELECTOR(Game::changeRandomBirdHeight), BIRD_HEIGHT_CHANGING_INTERVAL);
	schedule(CC_SCHEDULE_SELECTOR(Game::removeOutOfScreenEnemies), OUT_OF_SCREEN_REMOVING_INTERVAL);

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

	Scene* scene = GameOver::createScene(score);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

	delete player;
}

bool Game::onContactBegin(const cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	switch (a->getCategoryBitmask() | b->getCategoryBitmask())
	{
	case COLLISION_WITH_ENEMY_BITMASK: case COLLISION_WITH_BIRD_BITMASK:
		// remove enemy or bird
		if (a->getCategoryBitmask() == PLAYER_COLLISION_BITMASK)
		{
			removeChild(b->getNode());
		}
		else
		{
			removeChild(a->getNode());
		}
		gameOver();
		break;
	case PLAYER_HIT_BITMASK:
		// remove bullet and target
		removeChild(a->getNode());
		removeChild(b->getNode());
		score++;
		scoreLabel->setString("score: " + std::to_string(score));
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
	if (std::abs(targetPlayerPosition.x - player->getPosition().x) > 5 || // TODO исправить
		std::abs(targetPlayerPosition.y - player->getPosition().y) > 5)
	{
		Vec2 direction = targetPlayerPosition - player->getPosition();
		direction.normalize();

		Vec2 newPosition = player->getPosition() + direction * PLAYER_SPEED * dt;

		player->updatePosition(newPosition);
	}

	if (player->getPosition().y - player->getSize().height / 2 <= visibleSize.height * GROUND_HEIGHT_FACTOR)
	{
		gameOver();
	}
}

void Game::updateGameTime(float dt)
{
	gameTime += dt;
	gameTimeLabel->setString("seconds: " + std::to_string(gameTime));
}

void Game::spawnEnemy(float dt)
{
	float height = 0;
	float speed = 0;

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
		Bomber::create(height, speed);
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
		Fighter::create(height, speed);
		break;
	default:
		height = (visibleSize.height / 3 - visibleSize.height * GROUND_HEIGHT_FACTOR) * CCRANDOM_0_1() + visibleSize.height * GROUND_HEIGHT_FACTOR;
		speed = LOW_SPEED;
		Bird::create(height, speed);
		break;
	}
}

void Game::changeRandomBirdHeight(float dt)
{
	if (Bird::birds.size() > 0)
	{
		if (rand() % 2 == 0) // 50% chance to change the height
		{
			float lower = visibleSize.height * GROUND_HEIGHT_FACTOR;
			float higher = visibleSize.height / 3;

			int index = rand() % Bird::birds.size();
			int minus = rand() % 2;

			currentBird = Bird::birds.at(index);

			if (minus == 0)
			{
				if (currentBird->getPositionY() - BIRD_HEIGHT_SPEED * BIRD_HEIGHT_TIME > lower)
				{
					currentBird->getPhysicsBody()->setVelocity(Vec2(currentBird->getPhysicsBody()->getVelocity().x, -BIRD_HEIGHT_SPEED));
					scheduleOnce(CC_SCHEDULE_SELECTOR(Game::resetCurrentBirdVelocity), BIRD_HEIGHT_TIME);
				}
			}
			else
			{
				if (currentBird->getPositionY() + BIRD_HEIGHT_SPEED * BIRD_HEIGHT_TIME < higher)
				{
					currentBird->getPhysicsBody()->setVelocity(Vec2(currentBird->getPhysicsBody()->getVelocity().x, BIRD_HEIGHT_SPEED));
					scheduleOnce(CC_SCHEDULE_SELECTOR(Game::resetCurrentBirdVelocity), BIRD_HEIGHT_TIME);
				}
			}
		}
	}
}

void Game::resetCurrentBirdVelocity(float dt)
{
	currentBird->getPhysicsBody()->setVelocity(Vec2(currentBird->getPhysicsBody()->getVelocity().x, 0));
	currentBird = nullptr;
}

void Game::removeOutOfScreenEnemies(float dt)
{
	Bomber::removeOutOfScreenSprites();
	Fighter::removeOutOfScreenSprites();
	Bird::removeOutOfScreenSprites();
}
