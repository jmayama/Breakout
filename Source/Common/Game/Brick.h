//#pragma once

#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class OpenGLTexture;
class Ball;

class Brick : public GameObject
{
    public:
	
	//Brick();
	Brick(int x, int y, int space);
	~Brick();

	//Implementing the pure virtual lifecycle methods from GameObject
	void update(double delta);
    void paint();
	
	//Overriding the virtual reset method from GameObject
    void reset();
   
    //Implementing the pure virtual type method from GameObject
    const char* getType();
	

	//Setter size methods
    void setSize(float width, float height);
    void setWidth(float width);
    void setHeight(float height);
	
  
    //Getter size methods
    void getSize(float &width, float &height);
    float getWidth();
    float getHeight();
    int getWhatLVL();

    protected:
    float m_Width;
    float m_Height;
	
	float x_brick;
	float y_brick;
	
	float m_BrickRow;
	float m_BrickColumn;
	
	float m_BrickSpace;
	
	float m_BrickStartX;
	float m_BrickStartY;
	
    int m_whatLevel;

	OpenGLTexture * m_Brick;
   

};
#endif
