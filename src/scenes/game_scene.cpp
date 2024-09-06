#include "game_scene.h"
#include "game_over_scene.h"
#include "../definitions.h"

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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("images/game.png");
	background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(background);

	PhysicsBody* playerZoneBody = PhysicsBody::createEdgeBox(Size(visibleSize.width / 3, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	playerZoneBody->setContactTestBitmask(true);

	Node* playerZoneNode = Node::create();
	playerZoneNode->setContentSize(Size(visibleSize.width / 3, visibleSize.height));
	//playerZoneNode->setPosition(Point(origin.x, origin.y));
	playerZoneNode->setPhysicsBody(playerZoneBody);
	playerZone = playerZoneNode->getBoundingBox();
	addChild(playerZoneNode);

	player = new Player(this, playerZoneNode->getPosition());

	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void Game::gameOver(float dt)
{
	Scene* scene = GameOver::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void Game::onMouseMove(EventMouse* event)
{
	Vec2 mouseLocation = event->getLocation();
	mouseLocation.y = Director::getInstance()->getVisibleSize().height - mouseLocation.y;
	if (playerZone.containsPoint(mouseLocation))
	{
		player->updatePosition(mouseLocation);
	}
	else
	{
		player->updatePosition(Vec2(player->getPosition().x, mouseLocation.y));
	}
}
