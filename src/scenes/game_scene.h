#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "../characters/player.h"

class Game : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Game);

private:
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }

    void gameOver(float dt);
    void onMouseMove(cocos2d::EventMouse* event);
    void update(float dt);

    void moveBackground(float dt);
    void movePlayer(float dt);

    cocos2d::Sprite* background1;
    cocos2d::Sprite* background2;

    Player* player;
    cocos2d::Vec2 targetPlayerPosition;
    cocos2d::Rect playerZone;

    cocos2d::PhysicsWorld* sceneWorld;
};

#endif // _GAME_SCENE_H_
