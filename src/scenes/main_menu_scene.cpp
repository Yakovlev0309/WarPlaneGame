#include "main_menu_scene.h"
#include "game_scene.h"
#include "../definitions.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* background = Sprite::create("images/main_menu.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(background);

    MenuItemImage* playButton = MenuItemImage::create("images/play_button.png", "images/play_button_clicked.png", CC_CALLBACK_1(MainMenu::startGame, this));
    playButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    Menu* menu = Menu::create(playButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);

    return true;
}

void MainMenu::startGame(Ref* sender)
{
    Scene* scene = Game::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
