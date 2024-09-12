#ifndef  _DEFINITIONS_H_
#define  _DEFINITIONS_H_

#define TRANSITION_TIME 0.5
#define SPLASH_SCENE_TIME 2.0

#define GAME_TIME_FONT_SIZE_FACTOR 0.05
#define SCORE_FONT_SIZE_FACTOR 0.05

#define OUT_OF_SCREEN_REMOVING_INTERVAL 3.0

#define GROUND_HEIGHT_FACTOR 0.05
#define SCORE_N_TIME_PADDING_FACTOR 0.05

// categories bitmasks
#define PLAYER_COLLISION_BITMASK         0x000001
#define BOMBER_COLLISION_BITMASK         0x000010
#define FIGHTER_COLLISION_BITMASK        0x000100
#define BULLET_COLLISION_BITMASK         0x001000
#define BIRD_COLLISION_BITMASK           0x010000
#define FIGHTER_BULLET_COLLISION_BITMASK 0x100000
										 
// collisions bitmasks					 
#define COLLISION_WITH_BOMBER_BITMASK    0x000011
#define COLLISION_WITH_FIGHTER_BITMASK   0x000101
#define PLAYER_HIT_BOMBER_BITMASK        0x001010
#define PLAYER_HIT_FIGHTER_BITMASK       0x001100
#define COLLISION_WITH_BIRD_BITMASK      0x010001
#define FIGHTER_HIT_PLAYER_BITMASK		 0x100001

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

// bird height
#define BIRD_HEIGHT_SPEED 50.0
#define BIRD_HEIGHT_TIME 1.0
#define BIRD_HEIGHT_CHANGING_INTERVAL (BIRD_HEIGHT_TIME + 1.0)

// fighter fire
#define FIGHTER_GUN_RATE PLAYER_GUN_RATE
#define FIGHTER_BULLET_SPEED BULLET_SPEED
#define FIGHTER_FIRE_TIME 1.0
#define FIGHTER_FIRE_INTERVAL (FIGHTER_FIRE_TIME + 1.0)

// fighter height
#define CHECK_FIGHTERS_DODGE_INTERVAL 0.5
#define FIGHTER_DODGING_SPEED 200.0
#define FIGHTER_DODGING_TIME 0.5
//#define FIGHTER_DODGING_INTERVAL (FIGHTER_DODGING_TIME + 1.0)

#endif // _DEFINITIONS_H_
