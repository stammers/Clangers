#include "objectAnimator.hpp"

ObjectAnimator::ObjectAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startWeight, GLfloat endWeight, GLfloat startSpeed) : Animator(startX, startY, startZ, startAngleX, startAngleY, startAngleZ, startSpeed){
	startW = startWeight;
	endW = endWeight;
	forward = true;
}

//changes the start and end weights so the object can move
void ObjectAnimator::animate(double time){

		if(forward){
			startW += speed * 0.001 * (time / 0.001);
			endW -= speed * 0.001 * (time / 0.001);
		}else{
			startW -= speed * 0.001 * (time / 0.001);
			endW += speed * 0.001 * (time / 0.001);
		}

		if(startW > 1.0f){
				forward = false;
		}else if(endW > 1.0f){
			forward = true;
		}



}

GLfloat ObjectAnimator::getStartWeight(){
	return startW;
}

GLfloat ObjectAnimator::getEndWeight(){
	return endW;
}


