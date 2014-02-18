#include "common.hpp"
#include "animator.hpp"

class BoatSpinnerAnimator : public Animator{

public:
	BoatSpinnerAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startSpeed) : Animator(startX, startY, startZ, startAngleX, startAngleY, startAngleZ, startSpeed){};
	void animate(double time);

};
