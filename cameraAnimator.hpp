#include "common.hpp"
#include "animator.hpp"

class CameraAnimator : public Animator{

public:
	CameraAnimator(GLfloat startX, GLfloat startY, GLfloat startZ, GLfloat startAngleX, GLfloat startAngleY, GLfloat startAngleZ, GLfloat speedStart);
	void animate(double time);
	void reset();

private:
	glm::vec3 startPosition;
	glm::vec3 startRotation;
	GLfloat startSpeed;
	int section;

};
