#include "game_over_scene.h"
#include "main_menu_scene.h"
#include "game_scene.h"
#include "../definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOver::createScene(unsigned int gameScore)
{
    score = gameScore;
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

    MenuItemImage* retryButton = MenuItemImage::create("images/retry_button.png", "images/retry_button_clicked.png", CC_CALLBACK_1(GameOver::retry, this));
    retryButton->setPosition(Point(visibleSize.width / 2 + origin.x, menuButton->getPosition().y - menuButton->getContentSize().height * 2));

    Menu* menu = Menu::create(menuButton, retryButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);

    UserDefault* scoreDB = UserDefault::getInstance();
    int highScore = scoreDB->getIntegerForKey("HIGHSCORE", 0);
    if (score > highScore)
    {
        highScore = score;
        scoreDB->setIntegerForKey("HIGHSCORE", highScore);
        scoreDB->flush();
    }

    Label* currentScoreLabel = Label::createWithTTF(std::to_string(score), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE_FACTOR);
    currentScoreLabel->setColor(Color3B::WHITE);
    currentScoreLabel->setPosition(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y);
    addChild(currentScoreLabel);

    Label* highScoreLabel = Label::createWithTTF(std::to_string(highScore), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE_FACTOR);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(highScoreLabel);

    return true;
}

void GameOver::openMenu(cocos2d::Ref* sender)
{
    Scene* scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOver::retry(cocos2d::Ref* sender)
{
    Scene* scene = Game::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
