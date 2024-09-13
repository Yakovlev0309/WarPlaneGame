#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(unsigned int gameScore, unsigned int gameTime);

    virtual bool init();

    CREATE_FUNC(GameOver);

private:
    void openMenu(cocos2d::Ref* sender);
    void retry(cocos2d::Ref* sender);
};

#endif // _GAME_OVER_SCENE_H_
