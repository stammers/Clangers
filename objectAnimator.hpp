#include "animator.hpp"

class ObjectAnimator : public Animator{

public:
	ObjectAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat startWeight, GLfloat endWeight, GLfloat startSpeed);
	void animate(double time);
	GLfloat getStartWeight();
	GLfloat getEndWeight();

private:
	GLfloat startW;
	GLfloat endW;
	bool forward;
};
