#include "results_scene.h"
#include "main_menu_scene.h"
#include "../definitions.h"

USING_NS_CC;

Scene* Results::createScene()
{
    return Results::create();
}

bool Results::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* background = Sprite::create("images/main_menu.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(background);

    MenuItemImage* menuButton = MenuItemImage::create("images/menu_button.png", "images/menu_button_clicked.png", CC_CALLBACK_1(Results::openMainMenu, this));
    menuButton->setPosition(Point(visibleSize.width / 10, visibleSize.height - menuButton->getContentSize().height * 2));

    Menu* menu = Menu::create(menuButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);

    UserDefault* resultsDB = UserDefault::getInstance();
    int highScore = resultsDB->getIntegerForKey("HIGHSCORE", 0);
    int biggestTime = resultsDB->getIntegerForKey("BIGGEST_TIME", 0);

    Label* highScoreLabel = Label::createWithTTF("highscore: " + std::to_string(highScore), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE_FACTOR);
    highScoreLabel->setColor(Color3B::WHITE);
    highScoreLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    addChild(highScoreLabel);

    Label* biggestTimeLabel = Label::createWithTTF("biggest game time: " + std::to_string(biggestTime), "fonts/Marker Felt.ttf", visibleSize.height * GAME_TIME_FONT_SIZE_FACTOR);
    biggestTimeLabel->setColor(Color3B::WHITE);
    biggestTimeLabel->setPosition(Point(visibleSize.width / 2, highScoreLabel->getPositionY() - highScoreLabel->getContentSize().height - biggestTimeLabel->getContentSize().height));
    addChild(biggestTimeLabel);

    return true;
}

void Results::openMainMenu(Ref* sender)
{
    Scene* scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
