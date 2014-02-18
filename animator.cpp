#include "animator.hpp"

Animator::Animator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startSpeed){
	movementX = startX;
	movementY = startY;
	movementZ = startZ;
	direction = 1.0f;
	angleX = startAngleX;
	angleY = startAngleY;
	angleZ = startAngleZ;
	speed = startSpeed;
}

//basic animation round in a square
void Animator::animate(double time){
	if(direction == 1){
		if(movementY <= -1.0f && movementX < 1.0f){
			movementX += 0.0005f * (time / 0.001);
		}else if(movementY >= 1.0f && movementX > -1.0f){
			movementX -= direction * 0.0005f * (time / 0.001);
		}else if(movementX >= 1.0f && movementY < 1.0f){
			movementY += direction * 0.0005f * (time / 0.001);
		}else if(movementX <= -1.0f && movementY > -1.0f){
			movementY -= direction * 0.0005f * (time / 0.001);
		}
	}else{
		if(movementY <= -1.0f && movementX >= -1.0f){
			movementX -= 0.0005f * (time / 0.001);
		}else if(movementY >= 1.0f && movementX <= 1.0f){
			movementX += direction * 0.0005f * (time / 0.001);
		}else if(movementX >= 1.0f && movementY >= -1.0f){
			movementY -= direction * 0.0005f * (time / 0.001);
		}else if(movementX <= -1.0f && movementY <= 1.0f){
			movementY += direction * 0.0005f * (time / 0.001);
		}
	}

}

void Animator::changeDirection(){
	direction = -1 * direction;
}

GLfloat Animator::getX(){
	return movementX;
}

GLfloat Animator::getY(){
	return movementY;
}

GLfloat Animator::getZ(){
	return movementZ;
}

glm::vec3 Animator::getPosition(){
	return glm::vec3(movementX, movementY, movementZ);
}

GLfloat Animator::getAngleX(){
	return angleX;
}

GLfloat Animator::getAngleY(){
	return angleY;
}

GLfloat Animator::getAngleZ(){
	return angleZ;
}

glm::vec3 Animator::getRotation(){
	return glm::vec3(angleX, angleY, angleZ);
}

void Animator::increaseSpeed(){
	speed += (speed < 10.0) ? 0.01f : 0.0f;
}

void Animator::decreaseSpeed(){
	speed -= (speed > 0.0) ? 0.01f : 0.0f;
	if(speed > -0.01f && speed < 0.01f){
		speed = 0.0f;
	}
}


