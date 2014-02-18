#ifndef ANIMATOR_HPP_
#define ANIMATOR_HPP_

#include "common.hpp"

class Animator{

public:
	Animator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startSpeed);
	void animate(double time);
	void changeDirection();
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	glm::vec3 getPosition();
	GLfloat getAngleX();
	GLfloat getAngleY();
	GLfloat getAngleZ();
	glm::vec3 getRotation();
	void increaseSpeed();
	void decreaseSpeed();


protected:
	GLfloat movementX;
	GLfloat movementY;
	GLfloat movementZ;
	GLfloat direction; //direction to move in 1 for forward, -1 for backwards
	GLfloat angleX; //angle to rotate by around X axis
	GLfloat angleY; //angle to rotate by around Y axis
	GLfloat angleZ; //angle to rotate by around Z axis
	GLfloat speed;

};



#endif /* ANIMATOR_HPP_ */
