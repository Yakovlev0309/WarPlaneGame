#ifndef  _DEFINITIONS_H_
#define  _DEFINITIONS_H_

#define TRANSITION_TIME 0.5
#define SPLASH_SCENE_TIME 2.0

// collision bitmasks
#define PLAYER_COLLISION_BITMASK 0x0001
#define ENEMY_COLLISION_BITMASK 0x0010
#define BULLET_COLLISION_BITMASK 0x0100
#define BIRD_COLLISION_BITMASK 0x1000

// result bitmasks
#define COLLISION_WITH_ENEMY_BITMASK 0x0011
#define PLAYER_HIT_BITMASK 0x0110
#define COLLISION_WITH_BIRD_BITMASK 0x1001

// player and background speeds
#define PLAYER_SPEED 300.0
#define BACKGROUND_SPEED 200.0

// enemies speeds
#define LOW_SPEED 150.0
#define MEDIUM_SPEED 300.0
#define HIGH_SPEED 450.0

// bullets and guns
#define BULLET_SPEED 500.0
#define PLAYER_GUN_RATE 0.1

#endif // _DEFINITIONS_H_
