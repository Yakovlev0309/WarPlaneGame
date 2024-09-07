#include "game_over_scene.h"
#include "main_menu_scene.h"
#include "../definitions.h"

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

    MenuItemImage* menuButton = MenuItemImage::create("images/menu_button.png", "images/menu_button_clicked.png", CC_CALLBACK_1(GameOver::openMenu, this));
    menuButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));

    Menu* menu = Menu::create(menuButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);

    return true;
}

void GameOver::openMenu(cocos2d::Ref* sender)
{
    Scene* scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
