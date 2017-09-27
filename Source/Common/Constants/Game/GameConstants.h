#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

//Game Constants
extern const char* GAME_SCREEN_NAME;
extern const double GAME_OVER_TIMER;

//Ball Constants
extern const float GAME_BALL_RADIUS_PERCENTAGE;
extern const float GAME_BALL_DEFAULT_SPEED;
extern const float GAME_BALL_SPEED_INCREMENT;
extern const char* GAME_BALL_TYPE;
extern const char* GAME_BALL_TEXTURE;

//Paddle Constants
extern const float GAME_PADDLE_WIDTH_PERCENTAGE;
extern const float GAME_PADDLE_HEIGHT_PERCENTAGE;
extern const float GAME_PADDLE_Y_PERCENTAGE;
extern const char* GAME_PADDLE_TYPE;
extern const char* GAME_PADDLE_TEXTURE;



//Brick Constants
extern const float GAME_BRICK_WIDTH_PERCENTAGE;
extern  const float GAME_BRICK_HEIGHT_PERCENTAGE;
extern const float GAME_BRICK_Y_PERCENTAGE;
extern const float GAME_BRICK_HEIGHT;
extern const float GAME_BRICK_WIDTH;
extern const int GAME_BRICK_ROWS;
extern const int GAME_BRICK_COLUMNS;
extern const int GAME_BRICK_SPACE;
extern const char* GAME_BRICK_TYPE;
extern const char* GAME_BRICK_TEXTURE;



//Background Constants
extern const char* GAME_BACKGROUND_TEXTURE;

//Life Constants
extern const char* GAME_LIFE_TEXTURE;

//GameOver Constants
extern const char* GAME_OVER_TEXTURE;
extern const char* GAME_OVER_MENU;

//Level Constants
extern const  int GAME_LEVEL_1;
extern const  int GAME_LEVEL_2;
extern const  int GAME_LEVEL_3;
extern const  int GAME_LEVEL_4;
extern const  int GAME_LEVEL_5;
extern const int GAME_MAX_LEVEL;
extern const int GAME_MIN_LEVEL;


#endif 