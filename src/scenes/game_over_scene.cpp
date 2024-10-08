#include "game_over_scene.h"
#include "main_menu_scene.h"
#include "game_scene.h"
#include "../definitions.h"

USING_NS_CC;

unsigned int currentScore = 0;
unsigned int currentTime = 0;

Scene* GameOver::createScene(unsigned int gameScore, unsigned int gameTime)
{
    currentScore = gameScore;
    currentTime = gameTime;
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

    MenuItemImage* retryButton = MenuItemImage::create("images/retry_button.png", "images/retry_button_clicked.png", CC_CALLBACK_1(GameOver::retry, this));
    retryButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 5 * 2));
    
    MenuItemImage* menuButton = MenuItemImage::create("images/menu_button.png", "images/menu_button_clicked.png", CC_CALLBACK_1(GameOver::openMenu, this));
    menuButton->setPosition(Point(visibleSize.width / 2, retryButton->getPosition().y - retryButton->getContentSize().height / 2 - menuButton->getContentSize().height));

    Menu* menu = Menu::create(menuButton, retryButton, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);

    UserDefault* resultsDB = UserDefault::getInstance();
    int highScore = resultsDB->getIntegerForKey("HIGHSCORE", 0);
    if (currentScore > highScore)
    {
        highScore = currentScore;
        resultsDB->setIntegerForKey("HIGHSCORE", highScore);
        resultsDB->flush();
    }
    int biggestTime = resultsDB->getIntegerForKey("BIGGEST_TIME", 0);
    if (currentTime > biggestTime)
    {
        biggestTime = currentTime;
        resultsDB->setIntegerForKey("BIGGEST_TIME", biggestTime);
        resultsDB->flush();
    }

    Label* currentScoreLabel = Label::createWithSystemFont("score: " + std::to_string(currentScore), RESULTS_FONT, visibleSize.height * SCORE_FONT_SIZE_FACTOR);
    currentScoreLabel->setColor(Color3B::WHITE);
    currentScoreLabel->setPosition(visibleSize.width / 5, visibleSize.height / 2);
    addChild(currentScoreLabel);

    Label* currentTimeLabel = Label::createWithSystemFont("game time: " + std::to_string(currentTime) + " s", RESULTS_FONT, visibleSize.height * GAME_TIME_FONT_SIZE_FACTOR);
    currentTimeLabel->setColor(Color3B::WHITE);
    currentTimeLabel->setPosition(visibleSize.width / 5, visibleSize.height / 2 - currentTimeLabel->getContentSize().height);
    addChild(currentTimeLabel);

    Label* highScoreLabel = Label::createWithSystemFont("highscore: " + std::to_string(highScore), RESULTS_FONT, visibleSize.height * SCORE_FONT_SIZE_FACTOR);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width / 5 * 4, visibleSize.height / 2));
    addChild(highScoreLabel);

    Label* biggestTimeLabel = Label::createWithSystemFont("biggest game time: " + std::to_string(biggestTime) + " s", RESULTS_FONT, visibleSize.height * GAME_TIME_FONT_SIZE_FACTOR);
    biggestTimeLabel->setColor(Color3B::YELLOW);
    biggestTimeLabel->setPosition(Point(visibleSize.width / 5 * 4, visibleSize.height / 2 - biggestTimeLabel->getContentSize().height));
    addChild(biggestTimeLabel);

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
