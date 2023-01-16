#include "Food.hpp"
Food::Food() {
	if ((rand() % 2) == 1)
	{
		pos = glm::vec3((rand() % 1) + (float)rand() / (float)RAND_MAX, (rand() % 1) + (float)rand() / (float)RAND_MAX, 0.0f);
	}
	else {
		pos = glm::vec3((rand() % 1) - (float)rand() / (float)RAND_MAX, (rand() % 1) - (float)rand() / (float)RAND_MAX, 0.0f);
	}
	color = glm::vec4(1, 1, 0, 1);
}
bool Food::check_food(glm::vec3 snake_pos,float length) {
	if (abs(snake_pos.x-pos.x)<=length && abs(snake_pos.y-pos.y)<=length)
	{
		return true;
	}
	else {
		return false;
	}
}
void Food::change_position() {
	if ((rand() % 2) == 1)
	{
		pos = glm::vec3((rand() % 1) + ((float)rand() / (float)RAND_MAX)-0.1, (rand() % 1) + ((float)rand() / (float)RAND_MAX) - 0.1, 0.0f);
	}
	else {
		pos = glm::vec3((rand() % 1) - ((float)rand() / (float)RAND_MAX)+0.1, (rand() % 1) - ((float)rand() / (float)RAND_MAX)+0.1, 0.0f);
	}
}
glm::vec4 Food::getColor() {
	return color;
}
glm::vec3 Food::getPosition() {
	return pos;
}
