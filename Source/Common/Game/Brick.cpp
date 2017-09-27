#include "GameObject.h"
#include "Brick.h"
#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "../Constants/Constants.h"
#include "../Screen Manager/ScreenManager.h"
#include "../OpenGL/OpenGL.h"
#include "../OpenGL/OpenGltextureLoader.h"
#include "../OpenGL/OpenGLRenderer.h"


Brick::Brick(int x, int y, int lvl) : GameObject()
{
    m_Brick = new OpenGLTexture(GAME_BRICK_TEXTURE);
    m_BrickStartX = x;
    m_BrickStartY = y;
    m_whatLevel = lvl;
   
}

Brick::~Brick()
{
	
	 if(m_Brick != NULL)
    {
        delete m_Brick;
        m_Brick = NULL;
    }

}

void Brick::update(double aDelta)
{

}

void Brick::reset()
{
	
  //Reset the paddle's width and height
  setWidth(GAME_BRICK_WIDTH);
  setHeight(GAME_BRICK_HEIGHT);
  
  //Reset the x and y position
  setX(m_BrickStartX);
  setY(m_BrickStartY);

  //Reset the paddle to active
  setIsActive(true);
  
 
} 

const char* Brick::getType()
{
  return GAME_BRICK_TYPE;
}



void Brick::paint()
{	
	OpenGLRenderer::getInstance()->drawTexture(m_Brick, getX(), getY(), getWidth(), getHeight());
}
	

void Brick::setSize(float aWidth, float aHeight)
{
  setWidth(aWidth);
  setHeight(aHeight);
}

void Brick::setWidth(float aWidth)
{
  m_Width = aWidth;
}

void Brick::setHeight(float aHeight)
{
  m_Height = aHeight;
}

void Brick::getSize(float &aWidth, float &aHeight)
{
  aWidth = getWidth();
  aHeight = getHeight();
}

float Brick::getWidth()
{
  return m_Width;
}

float Brick::getHeight()
{
  return m_Height;
}

int Brick::getWhatLVL()
{
	return m_whatLevel;
}




