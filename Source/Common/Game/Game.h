#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"

class GameObject;
class OpenGLTexture;
class Ball;
class Screen;
class Brick;
class Paddle;

class Game : public Screen
{
public:
  Game();
  ~Game();

  //Game lifecycle methods
  void update(double delta);
  void paint();
  void reset();
  
  //Game Over method, call this when to end the game
  void gameOver();
 

  //Screen name, must be implemented, it's a pure
  //virtual method in the Screen class
  const char* getName();
  
  //Screen event method, inherited from the screen class
  void screenWillAppear();

  //GameObject Methods
  void addGameObject(GameObject* gameObject);
  GameObject* getGameObjectByType(const char* type);

  //will create row and colums for bricks
  void makeBrick();
  
  void addSpeed();

  void restartGame();
  
  bool isItANewLevel();

private:
  //Mouse Events
  void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);

  //Key Events
  void keyUpEvent(int keyCode);

  //Vector to hold the GameObjects
  std::vector<GameObject*> m_GameObjects;
  
  //Timer variable to delay reseting the game has ended
  double m_GameOverTimer;
  
  double timerID;
  
   float currentBallSpeed;

  int m_LifeCounter;
  
  //int m_Level;
  
  bool deadEnd;
  
  short m_CurrentGameLevel;

  Paddle * m_Paddle;
  Ball * m_Ball;
  Brick * m_Brick;
 
  OpenGLTexture * m_Background;
  OpenGLTexture * m_GameOver;	
  OpenGLTexture * m_Life;
};

#endif