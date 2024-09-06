#ifndef _SPLASH_SCENE_H_
#define _SPLASH_SCENE_H_

#include "cocos2d.h"

class Splash : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Splash);

private:
    void openMainMenu(float dt);
};

#endif // _SPLASH_SCENE_H_
