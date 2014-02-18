#include "utils.hpp"
#include "renderer.hpp"
#include "cameraAnimator.hpp"
#include "boatSpinnerAnimator.hpp"
#include "objectAnimator.hpp"
#include "boatAnimator.hpp"
#include <glm/gtx/string_cast.hpp>

static double startTime;

//angles to allow rotation with the arrow keys
float angleX = 0.0f; //angle around x axis
float angleY = 160.0f; //angle around y axis
float angleZ = 0.0f;
float angleDirectionChange = 0.0f;
GLfloat offset = 0.0f;

bool tour = false;
bool motion = true;
bool right = false;
bool left = false;
bool speedup = false;
bool slowdown = false;
bool up = false;
bool down = false;
glm::vec3 cameraPosition = glm::vec3(15.0f, 0.0f, 95.0f);
glm::vec3 lightPosition = glm::normalize(glm::vec3(-20.0f, 25.0f, 20.0f));

Renderer render;
CameraAnimator cameraPath(15.0f, 0.0f, 95.0f, 0.0f, 160.0f, 0.0f, 0.5f);
BoatSpinnerAnimator spinner(8.5f, 7.0f, 14.0f, 0.0f, 180.0f, 0.0f, 4.0f);
BoatSpinnerAnimator spinner2(-25.0f, 7.0f, -1.0f, 0.0f, 180.0f, 0.0f, 4.0f);
ObjectAnimator waving(0.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f);
ObjectAnimator fishing(8.5f, 7.0f, 14.0f, 0.0f, 200.0f, 0.0f, 1.0f, 0.0f, 1.0f);
BoatAnimator movingBoat(-25.0f, 7.0f, -6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 7.0f, 14.0f, 6.0f);

GLuint cubeVAO;
GLuint moonVAO;
GLuint moonTexture;
GLuint moonNormalTexture;
GLuint cubeTexture;
GLuint boatVAO;
GLuint boatSpinnerVAO;
GLuint boatTexture;
GLuint clanger1VAO;
GLuint clanger2VAO;
GLuint clanger3VAO;
GLuint clangerWavingVAO;
GLuint clangerTexture1;
GLuint clangerTexture2;
GLuint clangerFishingVAO;
GLuint clangerBoatVAO;
GLuint fishingRodVAO;
GLuint fishingRodTexture;
GLuint lidsVAO;
GLuint lidsTexture;
GLuint musicTreesVAO;
GLuint musicTreesTexture;

GLuint shadowBuffer;
GLuint shadowTexture;

int cubeVerticesNum = 0;
int moonVerticesNum = 0;
int clanger1VerticesNum = 0;
int clanger2VerticesNum = 0;
int clanger3VerticesNum = 0;
int clangerWavingVerticesNum = 0;
int boatVerticesNum = 0;
int boatSpinnerVerticesNum = 0;
int clangerFishingVerticesNum = 0;
int fishingRodVerticesNum = 0;
int lidsVerticesNum = 0;
int musicTreesVerticesNum = 0;
int clangerBoatVerticesNum = 0;

//the compiled shaders
GLuint shaderProgramShadedColour;
GLuint shaderProgramTextureCubeMap;
GLuint shaderProgramTextureShaded;
GLuint shaderProgramAnimatedTextureShaded;
GLuint shaderProgramTextureShadedReflection;
GLuint shaderProgramTextureShadedSpecular;
GLuint shaderProgramBasicShadow;
GLuint shaderProgramTextureNormalMapShadows;


//processes the key presses
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}else if(key == GLFW_KEY_LEFT){
		if(action == GLFW_PRESS){
			left = true;
		}else if(action == GLFW_RELEASE){
			left = false;
		}
	}else if(key == GLFW_KEY_RIGHT){
		if(action == GLFW_PRESS){
			right = true;
		}else if(action == GLFW_RELEASE){
			right = false;
		}
	}else if(key == GLFW_KEY_UP && !tour){
		if(action == GLFW_PRESS){
			speedup = true;
		}else if(action == GLFW_RELEASE){
			speedup = false;
		}
	}else if(key == GLFW_KEY_DOWN && !tour){
		if(action == GLFW_PRESS){
			slowdown = true;
		}else if(action == GLFW_RELEASE){
			slowdown = false;
		}
	}else if(key == GLFW_KEY_T && action == GLFW_PRESS && !tour){
		tour = true;
		cameraPath.reset();
	}else if(key == GLFW_KEY_E && action == GLFW_PRESS && tour){
		tour = false;
		angleX = cameraPath.getAngleX();
		angleY = cameraPath.getAngleY();
		angleZ = cameraPath.getAngleZ();
		cameraPosition = cameraPath.getPosition();
	}else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS && !tour){
		motion = !motion;
	}else if(key == GLFW_KEY_PAGE_DOWN){
		if(action == GLFW_PRESS){
			down = true;
		}else if(action == GLFW_RELEASE){
			down = false;
		}
	}else if(key == GLFW_KEY_PAGE_UP){
		if(action == GLFW_PRESS){
			up = true;
		}else if(action == GLFW_RELEASE){
			up = false;
		}
	}else if(key == GLFW_KEY_P && action == GLFW_PRESS && !tour){
		cameraPosition = glm::vec3(65.0f, 0.0f, -33.7074f);
		angleX = 0.0f;
		angleY = 75.0f;
		angleZ = 0.0f;
	}else if(key == GLFW_KEY_H && action == GLFW_PRESS){
		std::cout << "----Help----" << std::endl;
		std::cout << "Press T for tour" << std::endl;
		std::cout << "Press E to exit tour" << std::endl;
		std::cout << "Press P to move to move to screenshot location" << std::endl;
		std::cout << "Press Space to pause or resume motion" << std::endl;
		std::cout << "Press H to display this help text" << std::endl;
		std::cout << "Press Q or Esc to exit" << std::endl;
		std::cout << "--Camera" << std::endl;
		std::cout << "Press Left to rotate camera to the left" << std::endl;
		std::cout << "Press Right to rotate camera to the right" << std::endl;
		std::cout << "Press Up to speed up forward motion" << std::endl;
		std::cout << "Press Down to slow down forward motion" << std::endl;
		std::cout << "Press Page Up to increase the camera elevation" << std::endl;
		std::cout << "Press Page Down to reduce the camera elevation" << std::endl;
	}
}

void setupShaders(){
	// Create and compile our GLSL program from the shaders
	shaderProgramShadedColour = LoadShaders( "vertexShadedColour.vert", "fragmentShadedColour.frag" );
	shaderProgramTextureCubeMap = LoadShaders("vertexTextureCubeMap.vert", "fragmentTextureCubeMap.frag");
	shaderProgramTextureShaded = LoadShaders("vertexTextureShaded.vert", "fragmentTextureShaded.frag");
	shaderProgramAnimatedTextureShaded = LoadShaders("vertexAnimatedTextureShaded.vert", "fragmentTextureShaded.frag");
	shaderProgramTextureShadedReflection = LoadShaders("vertexTextureShadedReflection.vert", "fragmentTextureShadedReflection.frag");
	shaderProgramTextureShadedSpecular = LoadShaders("vertexTextureShadedSpecular.vert", "fragmentTextureShadedSpecular.frag");
	shaderProgramBasicShadow = LoadShaders("vertexBasicShadow.vert", "fragmentBasicShadow.frag");
	shaderProgramTextureNormalMapShadows = LoadShaders("vertexTextureNormalMapShadows.vert", "fragmentTextureNormalMapShadows.frag");
}


//moves camera in direction it is facing until it hits boundary
glm::vec3 cameraMove(glm::vec3 position, double duration){
	if(motion){
		offset += (speedup) ? 0.0005f * (duration / 0.001f) : 0.0f;
		offset -= (slowdown) ? 0.0005f * (duration / 0.001f) : 0.0f;
		offset = glm::clamp(offset, 0.0f, 10.0f);

		angleY -= (left) ? 0.1f * (duration / 0.001f) : 0.0f;
		angleY += (right) ? 0.1f * (duration / 0.001f) : 0.0f;

		GLfloat cameraHeight = 0.0f;
		if(up){
			cameraHeight = -0.01f * (duration / 0.001f);
		}else if(down){
			cameraHeight =  0.01f * (duration / 0.001f);
		}

		GLfloat pitchRadian = angleX * (M_PI / 180); // X rotation
		GLfloat yawRadian   = angleY   * (M_PI / 180); // Y rotation

		GLfloat newPosX = offset *  sinf( yawRadian ) * cosf( pitchRadian );
		GLfloat newPosY = offset * -sinf( pitchRadian );
		GLfloat newPosZ = offset *  cosf( yawRadian ) * cosf( pitchRadian );
		return glm::vec3(glm::clamp(-newPosX + position.x, -65.0f, 65.0f), glm::clamp(-newPosY + position.y + cameraHeight, -50.0f, 0.0f), glm::clamp(newPosZ + position.z, -95.0f, 95.0f));
	}else{
		return position;
	}
}

glm::mat4 view(double duration){
	// Camera view matrix
	glm::mat4 View = glm::mat4(1.);
	if(tour){
		glm::vec3 translation = cameraPath.getPosition();
		View = glm::translate(View, translation);
		View = glm::translate(View, -translation);
		View = glm::rotate(View, cameraPath.getAngleX(), glm::vec3(1.0, 0.0, 0.0));
		View = glm::rotate(View, cameraPath.getAngleY(), glm::vec3(0.0, 1.0, 0.0));
		View = glm::rotate(View, cameraPath.getAngleZ(), glm::vec3(0.0, 0.0, 1.0));
		View = glm::translate(View, translation);
		cameraPosition = translation;
	}else{
		glm::vec3 translation = cameraMove(cameraPosition, duration);
		View = glm::translate(View, translation);
		View = glm::translate(View, -translation);
		View = glm::rotate(View, angleX, glm::vec3(1.0, 0.0, 0.0));
		View = glm::rotate(View, angleY, glm::vec3(0.0, 1.0, 0.0));
		View = glm::rotate(View, angleZ, glm::vec3(0.0, 0.0, 1.0));
		View = glm::translate(View, translation);
		cameraPosition = translation;
	}
	return View;
}

void mp(glm::vec3 offset, glm::vec3 rotation, GLfloat scaleValue, GLuint shaderProgram, glm::mat4 &View, bool shadow, bool shadowRendering){
	glm::mat4 Projection;
	//projection matrix varies depending on current render pass
	if(!shadow){
		Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100000.0f);
	}else{
		Projection = glm::ortho<float>(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
	}


	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0);

	Model = glm::translate(Model, offset);
	Model = glm::scale(Model, glm::vec3(scaleValue, scaleValue, scaleValue));
	Model = glm::rotate(Model, rotation.x, glm::vec3(1.0, 0.0, 0.0));
	Model = glm::rotate(Model, rotation.y, glm::vec3(0.0, 1.0, 0.0));
	Model = glm::rotate(Model, rotation.z, glm::vec3(0.0, 0.0, 1.0));

	glm::mat3 MV = glm::mat3(View * Model);

	glm::mat4 MVP = Projection * View * Model;

	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
	GLuint MV3x3ID = glGetUniformLocation(shaderProgram, "MV");
	GLuint ModelID = glGetUniformLocation(shaderProgram, "M");
	GLuint ViewID = glGetUniformLocation(shaderProgram, "V");

	// Send our matrices to the currently bound shader,
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(MV3x3ID, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);

	//if rendering with shadows send extra data needed to shader
	if(shadowRendering){
		glm::mat4 ProjectionShadow = glm::ortho<float>(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
		glm::mat4 v = glm::lookAt(lightPosition, glm::vec3(0,0,0), glm::vec3(0,1,0));
		glm::mat4 shadowMVP = ProjectionShadow * v * Model;
		glm::mat4 biasMatrix(0.5, 0.0, 0.0, 0.0,
		                     0.0, 0.5, 0.0, 0.0,
		                     0.0, 0.0, 0.5, 0.0,
		                     0.5, 0.5, 0.5, 1.0);
		shadowMVP = biasMatrix * shadowMVP;
		GLuint shadowMatrixID = glGetUniformLocation(shaderProgram, "shadowMVP");
		glUniformMatrix4fv(shadowMatrixID, 1, GL_FALSE, &shadowMVP[0][0]);
	}
}

//sends the light direction and colour to the given shader
void lighting(GLuint shaderProgram){
	GLuint LightID = glGetUniformLocation(shaderProgram, "lightDirection");
	glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);

	glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);
	GLuint ColourID = glGetUniformLocation(shaderProgram, "lightColour");
	glUniform3f(ColourID, colour.r, colour.g, colour.b);
}

//sends the texture and normal map texture to the given shader
void normalMap(GLuint shaderProgram, GLuint tex, GLuint normalTex, std::string texture1, std::string texture2){
	GLuint texID = glGetUniformLocation(shaderProgram, texture1.c_str());
	GLuint normalTexID = glGetUniformLocation(shaderProgram, texture2.c_str());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(texID, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glUniform1i(normalTexID, 1);
}

//sends the shadow map texture to the given shader
void shadowMap(GLuint shaderProgram){
	GLuint shadowTexID = glGetUniformLocation(shaderProgram, "shadowMap");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);
	glUniform1i(shadowTexID, 2);
}

//sends the cube map and texture to the given shader to allow for reflections
void reflections(GLuint shaderProgram, GLuint tex, GLuint cubeMap){
	GLuint texID = glGetUniformLocation(shaderProgram, "tex");
	GLuint normalTexID = glGetUniformLocation(shaderProgram, "cubeTex");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(texID, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
	glUniform1i(normalTexID, 1);
}

//sends the start and end weights to the given shader for animating an object
void animated(GLuint shaderProgram, ObjectAnimator &animator){
	GLuint startW = glGetUniformLocation(shaderProgram, "startW");
	glUniform1f(startW, animator.getStartWeight());

	GLuint endW = glGetUniformLocation(shaderProgram, "endW");
	glUniform1f(endW, animator.getEndWeight());
}

//much of this code modified from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
void shadows(){
	// Render to our shadow framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
	glViewport(0,0,1024,1024);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 v = glm::lookAt(lightPosition, glm::vec3(0,0,0), glm::vec3(0,1,0));

	glUseProgram (shaderProgramBasicShadow);
	glBindVertexArray (clanger1VAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clanger1VerticesNum);

	glBindVertexArray (clanger2VAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clanger2VerticesNum);

	glBindVertexArray (clanger3VAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clanger3VerticesNum);

	glBindVertexArray (clangerWavingVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clangerWavingVerticesNum);

	glBindVertexArray (moonVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, moonVerticesNum);

	glBindVertexArray (lidsVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, lidsVerticesNum);

	glBindVertexArray (musicTreesVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, musicTreesVerticesNum);

	glBindVertexArray (boatVAO);
	mp(glm::vec3(8.5f, 7.0f, 14.0f), glm::vec3(0.0f, 200.0f, 0.0f), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatVerticesNum);

	glBindVertexArray (clangerFishingVAO);
	mp(glm::vec3(8.5f, 7.0f, 14.0f), glm::vec3(0.0f, 200.0f, 0.0f), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clangerFishingVerticesNum);

	glBindVertexArray (fishingRodVAO);
	mp(glm::vec3(8.5f, 7.0f, 14.0f), glm::vec3(0.0f, 200.0f, 0.0f), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, fishingRodVerticesNum);

	glBindVertexArray (boatSpinnerVAO);
	mp(spinner.getPosition(), spinner.getRotation(), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatSpinnerVerticesNum);

	glBindVertexArray (boatVAO);
	mp(movingBoat.getPosition(), movingBoat.getRotation(), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatVerticesNum);

	glBindVertexArray (clangerBoatVAO);
	mp(movingBoat.getPosition(), movingBoat.getRotation(), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clangerBoatVerticesNum);

	glBindVertexArray (boatSpinnerVAO);
	mp(movingBoat.getPosition(), spinner2.getRotation(), 0.05f, shaderProgramBasicShadow, v, true, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatSpinnerVerticesNum);
}

void renderScene(){

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0,0,640,640);

	glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//moves animated objects
	double duration = glfwGetTime() - startTime;

	if(motion){
		if(tour){
			cameraPath.animate(duration);
		}
		spinner.animate(duration);
		spinner2.animate(duration);
		waving.animate(duration);
		movingBoat.animate(duration);
		fishing.animate(duration);
	}

	startTime = glfwGetTime();
	glm::mat4 v = view(duration);


	//turns off depth testing for skybox so that it is always further away than all other objects
	glDepthMask(GL_FALSE);

	glUseProgram (shaderProgramTextureCubeMap);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
	glBindVertexArray (cubeVAO);
	mp(glm::vec3(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, shaderProgramTextureCubeMap, v, false, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, cubeVerticesNum, GL_UNSIGNED_INT, (void*)0);

	glDepthMask(GL_TRUE);


	//render all objects to the screen
	glUseProgram (shaderProgramTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, clangerTexture1);
	glBindVertexArray (clanger1VAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramTextureShaded, v, false, false);
	lighting(shaderProgramTextureShaded);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clanger1VerticesNum);

	glUseProgram (shaderProgramTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, clangerTexture2);
	glBindVertexArray (clanger2VAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramTextureShaded, v, false, false);
	lighting(shaderProgramTextureShaded);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clanger2VerticesNum);

	glUseProgram (shaderProgramTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, clangerTexture1);
	glBindVertexArray (clanger3VAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramTextureShaded, v, false, false);
	lighting(shaderProgramTextureShaded);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clanger3VerticesNum);

	glUseProgram (shaderProgramAnimatedTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, clangerTexture2);
	glBindVertexArray (clangerWavingVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramAnimatedTextureShaded, v, false, false);
	lighting(shaderProgramAnimatedTextureShaded);
	animated(shaderProgramAnimatedTextureShaded, waving);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clangerWavingVerticesNum);

	glUseProgram (shaderProgramTextureNormalMapShadows);
	glBindTexture(GL_TEXTURE_2D, moonTexture);
	normalMap(shaderProgramTextureNormalMapShadows, moonTexture, moonNormalTexture, "tex", "normalTex");
	glBindVertexArray (moonVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramTextureNormalMapShadows, v, false, true);
	lighting(shaderProgramTextureNormalMapShadows);
	shadowMap(shaderProgramTextureNormalMapShadows);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, moonVerticesNum);

	glUseProgram (shaderProgramTextureShadedReflection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lidsTexture);
	reflections(shaderProgramTextureShadedReflection, lidsTexture, cubeTexture);
	glBindVertexArray (lidsVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramTextureShadedReflection, v, false, false);
	lighting(shaderProgramTextureShadedReflection);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, lidsVerticesNum);

	glUseProgram (shaderProgramTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, musicTreesTexture);
	glBindVertexArray (musicTreesVAO);
	mp(glm::vec3(0.0f, -7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f, shaderProgramTextureShaded, v, false, false);
	lighting(shaderProgramTextureShaded);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, musicTreesVerticesNum);

	glUseProgram (shaderProgramTextureShadedSpecular);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, boatTexture);
	glBindVertexArray (boatVAO);
	mp(glm::vec3(8.5f, 7.0f, 14.0f), glm::vec3(0.0f, 200.0f, 0.0f), 0.05f, shaderProgramTextureShadedSpecular, v, false, false);
	lighting(shaderProgramTextureShadedSpecular);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatVerticesNum);

	glUseProgram (shaderProgramTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, clangerTexture1);
	glBindVertexArray (clangerFishingVAO);
	mp(glm::vec3(8.5f, 7.0f, 14.0f), glm::vec3(0.0f, 200.0f, 0.0f), 0.05f, shaderProgramTextureShaded, v, false, false);
	lighting(shaderProgramTextureShaded);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clangerFishingVerticesNum);

	glUseProgram (shaderProgramAnimatedTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fishingRodTexture);
	glBindVertexArray (fishingRodVAO);
	mp(glm::vec3(8.5f, 7.0f, 14.0f), glm::vec3(0.0f, 200.0f, 0.0f), 0.05f, shaderProgramAnimatedTextureShaded, v, false, false);
	lighting(shaderProgramAnimatedTextureShaded);
	animated(shaderProgramAnimatedTextureShaded, fishing);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, fishingRodVerticesNum);

	glUseProgram (shaderProgramShadedColour);
	glBindVertexArray (boatSpinnerVAO);
	mp(spinner.getPosition(), spinner.getRotation(), 0.05f, shaderProgramShadedColour, v, false, false);
	lighting(shaderProgramShadedColour);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatSpinnerVerticesNum);

	glUseProgram (shaderProgramTextureShadedSpecular);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, boatTexture);
	glBindVertexArray (boatVAO);
	mp(movingBoat.getPosition(), movingBoat.getRotation(), 0.05f, shaderProgramTextureShadedSpecular, v, false, false);
	lighting(shaderProgramTextureShadedSpecular);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatVerticesNum);

	glUseProgram (shaderProgramTextureShaded);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, clangerTexture2);
	glBindVertexArray (clangerBoatVAO);
	mp(movingBoat.getPosition(), movingBoat.getRotation(), 0.05f, shaderProgramTextureShaded, v, false, false);
	lighting(shaderProgramTextureShaded);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, clangerBoatVerticesNum);

	glUseProgram (shaderProgramShadedColour);
	glBindVertexArray (boatSpinnerVAO);
	mp(movingBoat.getPosition(), spinner2.getRotation(), 0.05f, shaderProgramShadedColour, v, false, false);
	lighting(shaderProgramShadedColour);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, boatSpinnerVerticesNum);

	glClearColor(0., 0., 0., 1.);

}

int setupShadowBuffer(){
	glGenFramebuffers(1, &shadowBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);

	//using a depth texture so it can be sampled later to draw the shadows
	glGenTextures(1, &shadowTexture);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTexture, 0);

	glDrawBuffer(GL_NONE);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		return -1;
	}
	return 0;
}

int main( void ) {

	// Initialize GLFW
	if( !glfwInit() ) {
		exit( EXIT_FAILURE );
	}

	// Open an OpenGL window
	GLFWwindow* window;

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 640, "COMP3004", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);


	glload::LoadTest tst = glload::LoadFunctions();
	if(!tst){
		glfwTerminate();
		return -1;
	}

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER);
	const GLubyte* version = glGetString (GL_VERSION);
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	setupShaders();
	if(setupShadowBuffer() == -1){
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	glDepthMask( GL_TRUE );
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	std::cout << "Setting up data" << std::endl;

	cubeVAO = render.cube(cubeVerticesNum);
	cubeTexture = render.skybox();
	clanger1VAO = render.object(clanger1VerticesNum, "clanger1", false, false);
	clanger2VAO = render.object(clanger2VerticesNum, "clanger2", false, false);
	clanger3VAO = render.object(clanger3VerticesNum, "clanger3", false, false);
	clangerWavingVAO = render.animatedObject(clangerWavingVerticesNum, "clangerAnimated1", "clangerAnimated3");
	clangerTexture1 = render.texture("clanger1.png");
	clangerTexture2 = render.texture("clanger2.png");
	moonVAO = render.object(moonVerticesNum, "moon", true, false);
	moonTexture = render.texture("moon.png");
	moonNormalTexture = render.texture("moonNormalMap.png");

	boatVAO = render.object(boatVerticesNum, "boat", false, false);
	boatTexture = render.texture("metal.png");
	boatSpinnerVAO = render.object(boatSpinnerVerticesNum, "boatSpinner", false, true);

	clangerBoatVAO = render.object(clangerBoatVerticesNum, "boatClanger", false, false);

	clangerFishingVAO = render.object(clangerFishingVerticesNum, "fishingBoatClanger", false, false);
	fishingRodVAO = render.animatedObject(fishingRodVerticesNum, "fishingBoatRod", "fishingBoatRod2");
	fishingRodTexture = render.texture("fishingRod.png");

	lidsVAO = render.object(lidsVerticesNum, "lids", false, false);
	lidsTexture = render.texture("silverMetal.png");

	musicTreesVAO = render.object(musicTreesVerticesNum, "trees", false, false);
	musicTreesTexture = render.texture("wood.png");
	std::cout << "Done loading" << std::endl;
	startTime  =  glfwGetTime();

	// Main loop
	while( !glfwWindowShouldClose(window) ) {

		shadows();
		renderScene();
		// Swap front and back rendering buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();


	}
	// Close window and terminate GLFW
	glfwDestroyWindow(window);

	glfwTerminate();
	// Exit program
	exit( EXIT_SUCCESS );
}







