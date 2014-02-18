#include "cameraAnimator.hpp"

CameraAnimator::CameraAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat speedStart) : Animator(startX, startY, startZ, startAngleX, startAngleY, startAngleZ, speedStart){
	startPosition = glm::vec3(startX, startY, startZ);
	startRotation = glm::vec3(startAngleX, startAngleY, startAngleZ);
	section = 1;
	startSpeed = speedStart;
}

void CameraAnimator::animate(double time){
	//GLfloat pause = 0.5;
	switch(section){
	case 1: // 5 seconds
		if(direction == -1.0f){
			movementZ += (movementZ < 95.0f) ? speed * 0.013f * (time / 0.001) : 0.0f;
			movementX += (movementX < 15.0f) ? speed * 0.008f * (time / 0.001) : 0.0f;
			movementY -= (movementY > 0.0f) ? speed * 0.0018f * (time / 0.001) : 0.0f;
			angleY += (abs(angleY) < 160.0f) ? speed * 0.005f * (time / 0.001) : 0.0f;
		}else{
			movementZ -= (movementZ > 30.0f) ? speed * 0.013f * (time / 0.001) : 0.0f;
			movementX -= (movementX > -25.0f) ? speed * 0.008f * (time / 0.001) : 0.0f;
			movementY += (movementY < 9.0f) ? speed * 0.0018f * (time / 0.001) : 0.0f;
			angleY -= (abs(angleY) > 135.0f) ? speed * 0.005f * (time / 0.001) : 0.0f;

			//at end of section
			if(abs(angleY) <= 135.2f && movementY >=8.8f && movementX <= -24.8f && movementZ <= 30.2f){
				section = 2;
			}
		}
		break;
	case 2: // 7 seconds
		if(direction == -1.0f){
			movementZ += (movementZ < 30.0f) ? speed * 0.01071f * (time / 0.001) : 0.0f;
			movementY += (movementY < 9.0f) ? speed * 0.002f * (time / 0.001) : 0.0f;
			angleY -= (abs(angleY) > 135.0f) ? speed * 0.02786f * (time / 0.001) : 0.0f;

			//at end of section
			if(abs(angleY) <= 135.2f && movementY >=8.8f && movementX <= -24.8f && movementZ <= 30.2f){
				section = 1;
			}
		}else{
			movementZ -= (movementZ > -45.0f) ? speed * 0.01071f * (time / 0.001) : 0.0f;
			movementY -= (movementY > -5.0f) ? speed * 0.002f * (time / 0.001) : 0.0f;
			angleY += (abs(angleY) < 330.0f) ? speed * 0.02786f * (time / 0.001) : 0.0f;

			//at end of section
			if(abs(angleY) >= 329.8f && movementY <=-4.8f && movementZ <= -44.8f){
				section = 3;
			}
		}
		break;
	case 3: // 5 seconds
		if(direction == -1.0f){
			movementX -= (movementX > -25.0f) ? speed * 0.008f * (time / 0.001) : 0.0f;
			movementY -= (movementY > -5.0f) ? speed * 0.001f * (time / 0.001) : 0.0f;
			angleY -= (abs(angleY) < 330.0f) ? speed * 0.004f * (time / 0.001) : 0.0f;

			//at end of section
			if(abs(angleY) >= 329.8f && movementY <=-4.8f && movementZ <= -44.8f){
				section = 2;
			}
		}else{
			movementY += (movementY < 0.0f) ? speed * 0.001f * (time / 0.001) : 0.0f;
			movementX += (movementX < 15.0f) ? speed * 0.008f * (time / 0.001) : 0.0f;
			angleY += (abs(angleY) < 350.0f) ? speed * 0.004f * (time / 0.001) : 0.0f;

			//at end of section
			if(movementY >=-0.2f && movementX >= 14.8f && abs(angleY) >= 349.8f){
				section = 4;
			}
		}
		break;
	case 4: // 5 seconds
		if(direction == -1.0f){
			movementZ -= (movementZ > -45.0f) ? speed * 0.0076f * (time / 0.001) : 0.0f;
			angleY -= (abs(angleY) > 350.0f) ? speed * 0.016f * (time / 0.001) : 0.0f;

			//at end of section
			if(movementY >=-0.2f && movementX >= 14.8f && abs(angleY) >= 349.8f){
				section = 4;
			}
		}else{
			movementZ += (movementZ < -5.0f) ? speed * 0.0076f * (time / 0.001) : 0.0f;
			angleY += (abs(angleY) < 430.0f) ? speed * 0.016f * (time / 0.001) : 0.0f;

			//at end of section
			if(movementZ >=-7.2f && abs(angleY) >= 429.8f){
				section = 5;
			}
		}

		break;
	case 5: // 8 seconds
		angleY = glm::mod(angleY, 360.0f);
		if(direction == -1.0f){
			movementZ -= (movementZ > -5.0f) ? speed * 0.01275f * (time / 0.001) : 0.0f;
			angleY -= (abs(angleY) > 70.0f) ? speed * 0.0075f * (time / 0.001) : 0.0f;

			//at end of section
			if(movementZ >=-7.2f && abs(angleY) >= 429.8f){
				section = 5;
			}
		}else{
			movementZ += (movementZ < 95.0f) ? speed * 0.01275f * (time / 0.001) : 0.0f;
			angleY += (abs(angleY) < 130.0f) ? speed * 0.0075f * (time / 0.001) : 0.0f;

			//at end of section
			if(abs(angleY) >= 99.8f && movementZ >= 94.8f){
				section = 6;

			}
		}
		break;
	case 6:
		angleY += (abs(angleY) < 230.0f) ? speed * 0.005f * (time / 0.001) : 0.0f;
		if(angleY >= 229.8f){
			std::cout << "End of tour" << std::endl;
			section = 7;
		}
		break;
	case 7:
		break;
	}

}

void CameraAnimator::reset(){
	movementX = startPosition.x;
	movementY = startPosition.y;
	movementZ = startPosition.z;

	angleX = startRotation.x;
	angleY = startRotation.y;
	angleZ = startRotation.z;

	section = 1;

	speed = startSpeed;
}

