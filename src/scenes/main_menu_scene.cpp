#include "main_menu_scene.h"
#include "game_scene.h"
#include "results_scene.h"
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
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);

    MenuItemImage* resultsButton = MenuItemImage::create("images/results_button.png", "images/results_button_clicked.png", CC_CALLBACK_1(MainMenu::results, this));
    resultsButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

    MenuItemImage* playButton = MenuItemImage::create("images/play_button.png", "images/play_button_clicked.png", CC_CALLBACK_1(MainMenu::startGame, this));
    playButton->setPosition(Point(visibleSize.width / 2, resultsButton->getPositionY() + resultsButton->getContentSize().height / 2 + playButton->getContentSize().height));

    MenuItemImage* exitButton = MenuItemImage::create("images/exit_button.png", "images/exit_button_clicked.png", CC_CALLBACK_1(MainMenu::exit, this));
    exitButton->setPosition(Point(visibleSize.width / 2, resultsButton->getPositionY() - resultsButton->getContentSize().height / 2 - exitButton->getContentSize().height));

    Menu* menu = Menu::create(playButton, resultsButton, exitButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);

    return true;
}

void MainMenu::startGame(Ref* sender)
{
    Scene* scene = Game::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenu::results(Ref* sender)
{
     Scene* scene = Results::createScene();
     Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenu::exit(Ref* sender)
{
    Director::getInstance()->end();
}
