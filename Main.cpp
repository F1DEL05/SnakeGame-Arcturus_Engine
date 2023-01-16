#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"ShaderProgram.hpp"
#include"Square.hpp"
#include"Food.hpp"
#include<vector>
#include<thread>
#include<chrono>
#include<Windows.h>
#include<mmsystem.h>
#include<irrKlang.h>
const int w = 700, h = 700;
const char* title = "Snake Game";
float length = 0.05f;
float speed = 0.002f;
float vertices[] = {
	 length / 2, length / 2,0.0f,
	 length / 2,-length / 2,0.0f,
	-length / 2,-length / 2,0.0f,

	 length / 2, length / 2,0.0f,
	-length / 2,-length / 2,0.0f,
	-length / 2, length / 2,0.0f
};
std::vector<Square*> SquareList;
void draw_Square(Shader& program) {
	for (auto square:SquareList)
	{
		program.setVec4("uColor", square->getColor());
		program.setVec3("uPosition", square->getPosition());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void move() {
	for (auto square:SquareList)
	{
		square->move(length);
	}
}
void draw_Food(Shader& program,Food* food) {
	program.setVec3("uPosition", food->getPosition());
	program.setVec4("uColor", food->getColor());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void AddToTail() {
	glm::vec3 last_pos = SquareList[SquareList.size() - 1]->getPosition();
	Square::DIRECTION last_dir = SquareList[SquareList.size() - 1]->getDirection();
	switch (last_dir)
	{
	case Square::DIRECTION_RIGHT:
		last_pos += glm::vec3(-length,0,0);
		break;
	case Square::DIRECTION_LEFT:
		last_pos += glm::vec3(length, 0, 0);
		break;
	case Square::DIRECTION_UP:
		last_pos += glm::vec3(0,-length, 0);
		break;
	case Square::DIRECTION_DOWN:
		last_pos += glm::vec3(0, length, 0);
		break;
	}
	Square* square = new Square(last_pos, glm::vec4(1.0, 0, 0, 1), length,last_dir);
	square->setDirection(last_dir);
	SquareList.push_back(square);
}

void set_dir() {
	Square::DIRECTION tail_dir = SquareList[SquareList.size() - 1]->getDirection();
	for (int i=SquareList.size()-1;i>0;i--)
	{
		SquareList[i]->setDirection(SquareList[i-1]->getDirection());
	}
}
int main() {
	if (!glfwInit())
	{
		std::cout << "glfw baslatilamadi !";
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(w, h,title, NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window==nullptr)
	{
		std::cout << "Pencere Baslatilamadi !";
		glfwTerminate();
	}
	glewExperimental = GLFW_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		std::cout << "Glew Baslatilamadi !";
		glfwTerminate();
		glfwDestroyWindow(window);
	}

	Shader program;
	program.AddShaderFromFile("./Shaders/vshader.glsl", Shader::VERTEX_SHADER);
	program.CompileShader(Shader::VERTEX_SHADER);
	program.AddShaderFromFile("./Shaders/fshader.glsl", Shader::FRAGMENT_SHADER);
	program.CompileShader(Shader::FRAGMENT_SHADER);
	program.AttachToProgram(Shader::VERTEX_SHADER);
	program.AttachToProgram(Shader::FRAGMENT_SHADER);
	program.LinkProgram();

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	program.ConnectVariable("uPosition");
	program.ConnectVariable("uColor");
	SquareList.push_back(new Square(glm::vec3(0, 0, 0), glm::vec4(0, 1, 0, 1), length,Square::DIRECTION_RIGHT));
	Food* food = new Food();
	int point = 0;
	irrklang::ISoundEngine* sound = irrklang::createIrrKlangDevice();
	sound->play2D("asd.wav", true);
	system("cls");
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		if (glfwGetKey(window,GLFW_KEY_ESCAPE))
		{
			glfwTerminate();
			glfwDestroyWindow(window);
			break;
		}
		if (glfwGetKey(window,GLFW_KEY_F))
		{
			AddToTail();
		}
		if (glfwGetKey(window,GLFW_KEY_RIGHT))
		{
			if (SquareList[0]->getDirection()!=-Square::DIRECTION_RIGHT)
			{
				SquareList[0]->setDirection(Square::DIRECTION_RIGHT);
			}
			


		}
		if (glfwGetKey(window,GLFW_KEY_LEFT))
		{
			if (SquareList[0]->getDirection() != -Square::DIRECTION_LEFT)
			{
				SquareList[0]->setDirection(Square::DIRECTION_LEFT);
			}

		}
		if (glfwGetKey(window,GLFW_KEY_UP))
		{
			if (SquareList[0]->getDirection() != -Square::DIRECTION_UP)
			{
				SquareList[0]->setDirection(Square::DIRECTION_UP);
			}

		}
		if (glfwGetKey(window,GLFW_KEY_DOWN))
		{
			if (SquareList[0]->getDirection() != -Square::DIRECTION_DOWN)
			{
				SquareList[0]->setDirection(Square::DIRECTION_DOWN);
			}

		}
		move();
		set_dir();
		if (SquareList[0]->getPosition().x> 1.0f+length/2 || SquareList[0]->getPosition().x<-1.0f-length/2)
		{
			glfwTerminate(); 
			glfwDestroyWindow(window);
			std::cout <<std::endl<< "Duvara Carptin !";
			break;
		}
		if (SquareList[0]->getPosition().y> 1.0f+(3*length/2) || SquareList[0]->getPosition().y<-1.0f-(3*length/2))
		{
			glfwTerminate(); 
			glfwDestroyWindow(window);
			std::cout <<std::endl<< "Duvara Carptin !";
			break;
		}
		if (food->check_food(SquareList[0]->getPosition(),length))
		{
			point++;
			std::cout << std::endl << "Puan :" << point;
			AddToTail();
			food->change_position();

		}
		glUseProgram(program.getProgramID());
		glBindVertexArray(VAO);
		draw_Food(program, food);
		draw_Square(program);
		glBindVertexArray(0);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));


		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	sound->stopAllSounds();
	std::cout << std::endl << "\n Kapatmak icin Herhangi Bir Tusa Basiniz ....";
	std::cin.get();
	return 0;
}