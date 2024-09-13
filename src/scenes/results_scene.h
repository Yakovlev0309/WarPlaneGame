#ifndef _RESULTS_SCENE_H_
#define _RESULTS_SCENE_H_

#include "cocos2d.h"

class Results : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Results);

private:
    void openMainMenu(Ref* sender);
};

#endif // _RESULTS_SCENE_H_
