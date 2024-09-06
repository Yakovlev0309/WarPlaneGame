#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MainMenu);

private:
    void startGame(Ref* sender);
};

#endif // _MAIN_MENU_SCENE_H_
