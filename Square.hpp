#ifndef SQUARE_HPP
#include<iostream>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Square {
public :
	enum DIRECTION
	{
		DIRECTION_RIGHT=1,
		DIRECTION_LEFT=-1,
		DIRECTION_UP=2,
		DIRECTION_DOWN=-2,
	};
	Square(glm::vec3 position,glm::vec4 color,float length,Square::DIRECTION dir);
	void move();
	void setDirection(Square::DIRECTION dir);
	Square::DIRECTION getDirection();
	glm::vec3 getPosition();
	glm::vec4 getColor();
	void setPosition(glm::vec3 position);
	void setColor(glm::vec4 color);
	void move(float speed);

private:
	glm::vec3 position=glm::vec3(0.0f,0.0f,0.0f);
	glm::vec4 color=glm::vec4(0.5f,0.5f,0.5f,1.0f);
	float length=0.05f;
	Square::DIRECTION direction = DIRECTION_RIGHT;
};
#endif