#include "game_over_scene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

bool GameOver::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* background = Sprite::create("images/game_over.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(background);

    return true;
}
