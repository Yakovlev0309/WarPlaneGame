#include "game_scene.h"
#include "game_over_scene.h"
#include "../definitions.h"

USING_NS_CC;

Scene* Game::createScene()
{
    return Game::create();
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

    return true;
}

void Game::gameOver(float dt)
{
    Scene* scene = GameOver::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
