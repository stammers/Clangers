#include "common.hpp"
#include "animator.hpp"

class BoatAnimator : public Animator{

public:
	BoatAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startSpeed, GLfloat startCentreX, GLfloat startCentreZ, GLfloat circleRadius);
	void animate(double time);

private:
	GLfloat angle;
	GLfloat centreX;
	GLfloat centreZ;
	GLfloat radius;
};
