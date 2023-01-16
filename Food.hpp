#ifndef FOOD_HPP
#define FOOD_HPP

#include<iostream>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Food {
public:
	Food();
	bool check_food(glm::vec3 snake_pos,float length);
	glm::vec4 getColor();
	glm::vec3 getPosition();
	void change_position();
private:
	glm::vec3 pos;
	glm::vec4 color;
	
};



#endif // !FOOD_HPP
