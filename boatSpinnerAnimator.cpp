#include "boatSpinnerAnimator.hpp"

void BoatSpinnerAnimator::animate(double time){
		angleY += speed * direction * 0.05f * (time / 0.001);
		angleY = glm::mod(angleY, 360.0f);
}


