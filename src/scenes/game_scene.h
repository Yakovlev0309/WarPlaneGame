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

    void gameOver();
    bool onContactBegin(const cocos2d::PhysicsContact& contact);
    void onMouseMove(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseUp(cocos2d::EventMouse* event);
    void update(float dt);

    void moveBackground(float dt);
    void movePlayer(float dt);
    void updateGameTime(float dt);

    void spawnEnemy(float dt);
    void changeRandomBirdHeight(float dt);
    void resetCurrentBirdVelocity(float dt);
    void randomFightersFire(float dt);
    void removeOutOfScreenEnemies(float dt);
    void checkFightersForDodge(float dt);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* background1;
    cocos2d::Sprite* background2;

    Player* player;
    cocos2d::Vec2 targetPlayerPosition;

    cocos2d::PhysicsWorld* sceneWorld;

    cocos2d::EventListenerPhysicsContact* contactListener;
    cocos2d::EventListenerMouse* mouseListener;

    int currentBirdIndex;
    int currentFighterIndex;

    unsigned int gameTime;
    unsigned int score;

    cocos2d::Label* gameTimeLabel;
    cocos2d::Label* scoreLabel;
};

#endif // _GAME_SCENE_H_
