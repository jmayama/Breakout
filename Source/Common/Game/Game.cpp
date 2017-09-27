#include "Game.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "..//Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"


Game::Game()
{
  //Create a new paddle and ball
  addGameObject(new Paddle());
  addGameObject(new Ball());
 
  
  //Get textures
  m_Background = new OpenGLTexture(GAME_BACKGROUND_TEXTURE);
  m_Life = new OpenGLTexture(GAME_LIFE_TEXTURE);
  
  m_GameOver =  new OpenGLTexture(GAME_OVER_TEXTURE);
  
  m_CurrentGameLevel = GAME_LEVEL_1;

  //m_Ball = (Ball*)getGameObjectByType(GAME_BALL_TYPE);
  
  makeBrick();
  
  //Get values
  m_LifeCounter = 3;
  
  deadEnd = false;
  
  reset();
}


Game::~Game()
{

   //Delete all the GameObject's in the vector
    for(int i = 0; i < m_GameObjects.size(); i++)
    {
        delete m_GameObjects.at(i);
        m_GameObjects.at(i) = NULL;
    }
	   //Clear the pointers from the vector
        m_GameObjects.clear();

	if(m_Background != NULL)
    {
        delete m_Background;
        m_Background = NULL;
    }
	  if(m_Life != NULL)
    {
        delete m_Life;
        m_Life = NULL;
    }
	  
	  if( m_GameOver != NULL)
    {
        delete  m_GameOver;
        m_GameOver = NULL;
    }
	  
	  if (m_Ball != NULL)
	  {
	   delete  m_Ball;
        m_Ball = NULL;
	  }
	
}

void Game::update(double aDelta)
{ 
  
    if (isItANewLevel() == true)
	{
		//If we do increment the current game level.
		m_CurrentGameLevel++;
		addSpeed();
      
		//If it' set to the max level, set it to level 1.
		if (m_CurrentGameLevel > GAME_MAX_LEVEL)
		{
		    m_CurrentGameLevel = GAME_MIN_LEVEL;
		}

		//Reset the game.
		reset();
     }

		//If the GameOver Timer is greater that zero, countdown
		if(m_GameOverTimer > 0.0)
		{
	
		m_GameOverTimer -= aDelta;

		if(m_GameOverTimer < 0.0)
		{ 
				m_GameOverTimer = 0.0;
	  
		}
		return;
		}

		//m_Ball = (Ball*)getGameObjectByType(GAME_BALL_TYPE);
		//m_Brick = (Brick*)getGameObjectByType(GAME_BRICK_TYPE);
  
		//Cycle through all the game objects update them and check their collision detection
		for(int i = 0; i < m_GameObjects.size(); i++)
		{
		//Make sure the GameObject is active
		if(m_GameObjects.at(i)->getIsActive() == true)
		{
			//Update the GameObject
			m_GameObjects.at(i)->update(aDelta);
							
			//Check collision detection against the ball
			if(m_GameObjects.at(i) != m_Ball)
			{
			GameObject* gameObject = m_GameObjects.at(i);
			m_Ball->checkCollision(gameObject);
			}
		}
		}
	}


void Game::makeBrick()
{
    
   float brickHeight = GAME_BRICK_HEIGHT;
    float brickWidth = GAME_BRICK_WIDTH;
    float brickX = GAME_BRICK_SPACE;
    float brickY = 0;
    

    for (int column = 0; column < GAME_BRICK_COLUMNS; column++)
    {
        for (int row = 0; row < GAME_BRICK_ROWS; row++)
        {
            brickX = brickX + brickWidth;
			
			addGameObject(new Brick(brickX, brickY, row + 1));
           
        }
        
			brickX = GAME_BRICK_SPACE;
			brickY = brickY + brickHeight;

    }
};


void Game::paint()
{    
	
	//Paint background. Did not work properly in the brick paint method. Y? 
	OpenGLRenderer::getInstance()->drawTexture(m_Background, 0.0f, 0.0f , getWidth(), getHeight());
	

	if(deadEnd) 
	{
		//ScreenManager::getInstance()->switchScreen(GAME_OVER_MENU);
		OpenGLRenderer::getInstance()->drawTexture(m_GameOver,0.0f, 0.0f, getWidth(), getHeight());
	}
	else 
	{
		OpenGLRenderer::getInstance()->drawTexture(m_Background, 0.0f, 0.0f , getWidth(), getHeight());
	}
	

	//Variable to help put space between life graphics. The variable keeps the value into the loop and increment the distance between life each time.
    int lifeSpace = 0;
  
	//Will draw life texture according to LifeCounter. ball goes off screen -1 to lifeCounter so will draw 2 heart. 
    for (int i = 0; i < m_LifeCounter; i ++)
     {
	  OpenGLRenderer::getInstance()->drawTexture(m_Life, lifeSpace, 700.0f);
	  lifeSpace = lifeSpace + 60;
	 }

	//Cycle through and draw all the game objects
    for(int i = 0; i < m_GameObjects.size(); i++)
    {
    if(m_GameObjects.at(i)->getIsActive() == true)
    {
      m_GameObjects.at(i)->paint();
    }
  }
  
  //Draw the outer white walls
  OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
  OpenGLRenderer::getInstance()->setLineWidth(4.0f);
  OpenGLRenderer::getInstance()->drawLine(1.0f, 0.0f, 1.0f, getHeight());
  OpenGLRenderer::getInstance()->drawLine(0.0f, 1.0f, getWidth(), 1.0f);
  OpenGLRenderer::getInstance()->drawLine(getWidth() - 1, 0.0f, getWidth() - 1, getHeight());
  OpenGLRenderer::getInstance()->setLineWidth(1.0f);

  

}

void Game::reset()
{
  //Cycle through and reset all the game objects
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
	  
      m_GameObjects.at(i)->reset();
      
      if (m_GameObjects.at(i)->getType() == GAME_BALL_TYPE)
      {
         m_Ball = (Ball *)m_GameObjects.at(i);
      }
      
      if (m_GameObjects.at(i)->getType() == GAME_PADDLE_TYPE)
      {
         m_Paddle = (Paddle *)m_GameObjects.at(i);
      }
 
  }
		addSpeed();
		deadEnd = false;
		//Reset the game over timer to zero
		m_GameOverTimer = 0.0;
}

void Game::addSpeed()
{
    currentBallSpeed = m_Ball->getSpeed();
    //Check to see if the current level is the first level.
    if (m_CurrentGameLevel == GAME_MIN_LEVEL)
    {
		//Set the balls speed to the lowest speed.
		m_Ball->setSpeed(GAME_BALL_DEFAULT_SPEED);
    }
    else 
    {
        m_Ball->setSpeed(currentBallSpeed + (GAME_BALL_SPEED_INCREMENT*m_CurrentGameLevel));
    }
}


bool Game::isItANewLevel()
{
    for (int i = 0; i < m_GameObjects.size(); i++)
    {
        if(m_GameObjects.at(i)->getType() == GAME_BRICK_TYPE && m_GameObjects.at(i)->getIsActive() == true)
        {
			//If an active brick is found we know the game is not over yet, return true.
			return false;
        }
    }
			currentBallSpeed = currentBallSpeed  + GAME_BALL_SPEED_INCREMENT;
			//Increment the game lives.
			
			m_LifeCounter++; 
			return true;
}

void Game::restartGame()
{
    //Set the starting values.
    m_LifeCounter = 3;
    m_CurrentGameLevel = GAME_MIN_LEVEL;
    
    addSpeed();
    
    reset();
}

//Ball Update function call gameoVER EACH time the ball goes off screen
void Game::gameOver()
{
	
  //if(ball->getDirectionY() < ScreenManager::getInstance()->getScreenHeight()){
	
  //Check if player has life remaining.
  if(m_LifeCounter <= 1)
  {
	char choose = 'r';
	deadEnd = true;
	
	while(!choose){
	
	m_GameOverTimer = GAME_OVER_TIMER;

	keyUpEvent(choose);

	}
    //Default lives.
    m_LifeCounter = 3;
    
	//Reset the game to Level 1.
    m_CurrentGameLevel = GAME_MIN_LEVEL;
  }

  //We still have game lives.
  else
  {   
	--m_LifeCounter;
	m_Ball->reset();
   
  }
};


const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

void Game::screenWillAppear()
{
  OpenGLRenderer::getInstance()->setBackgroundColor(OpenGLColorCornflowerBlue());
}

void Game::addGameObject(GameObject* aGameObject)
{
  if(aGameObject != NULL)
  {
    m_GameObjects.push_back(aGameObject);
  }
}

GameObject* Game::getGameObjectByType(const char* aType)
{
  //Cycle through a find the game object (if it exists)
  for(unsigned int i = 0; i < m_GameObjects.size(); i++)
  {
    if(strcmp(m_GameObjects.at(i)->getType(), aType) == 0)
    {
      return m_GameObjects.at(i);
    }
  }
  return NULL;
}

void Game::mouseMovementEvent(float aDeltaX, float aDeltaY, float aPositionX, float aPositionY)
{
  //Set the paddle to the x position of the mouse
  Paddle* paddle = (Paddle*)getGameObjectByType(GAME_PADDLE_TYPE);

  //Safety check, paddle could be NULL
  if(paddle != NULL)
  {
    paddle->setX(aPositionX - (paddle->getWidth() / 2.0f));
  }
}

void Game::keyUpEvent(int aKeyCode)
{
	if(aKeyCode == KEYCODE_R)
	{
		restartGame();
		//reset();
	}

	else 
	{
	exit(0);
	}
	
}
