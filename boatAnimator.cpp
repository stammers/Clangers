#include "boatAnimator.hpp"

BoatAnimator::BoatAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startSpeed, GLfloat startCentreX, GLfloat startCentreZ, GLfloat circleRadius) : Animator(startX, startY, startZ, startAngleX, startAngleY, startAngleZ, startSpeed){
	angle = 0.0f;
	centreX = startCentreX;
	centreZ = startCentreZ;
	radius = circleRadius;
}

//moves round in a circle, always facing direction of travel
void BoatAnimator::animate(double time){

	GLfloat tempAngle = speed * direction * 0.0005f * (time / 0.001);
	angle += tempAngle;
	angle = glm::mod(angle, static_cast<GLfloat>(2*M_PI));

	GLfloat newMovementZ = centreZ + sin(angle) * radius;
	GLfloat changeZ = newMovementZ - movementZ;
	movementZ = newMovementZ;
	GLfloat newMovementX = centreX + cos(angle) * radius;
	GLfloat changeX = newMovementX - movementX;
	movementX = newMovementX;

	if(changeZ < 0.0f){
		angleY = 180 -90 + ((atan(changeX/changeZ) * 180) / M_PI);
	}else{
		angleY = -90 + ((atan(changeX/changeZ) * 180) / M_PI);
	}

}


