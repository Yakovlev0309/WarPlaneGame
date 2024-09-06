#include "splash_scene.h"
#include "main_menu_scene.h"
#include "../definitions.h"

USING_NS_CC;

Scene* Splash::createScene()
{
    return Splash::create();
}

bool Splash::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    scheduleOnce(CC_SCHEDULE_SELECTOR(Splash::openMainMenu), SPLASH_SCENE_TIME);

    Sprite* background = Sprite::create("images/splash.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(background);

    return true;
}

void Splash::openMainMenu(float dt)
{
    Scene* scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
