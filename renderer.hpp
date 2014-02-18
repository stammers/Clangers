
#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "common.hpp"
#include "sphere.hpp"
#include "objectloader.hpp"

class Renderer{
public:
	GLuint sphere(int subdivisions, int &verticesNum);
	GLuint object(int &verticesNum, std::string name, bool normalMap, bool perVertexColour);
	GLuint animatedObject(int &verticesNum, std::string start, std::string end);
	GLuint texture(std::string name);
	GLuint skybox();
	GLuint cube(int &verticesNum);

private:
	Sphere sphereObject;
	ObjectLoader loader;
	GLuint setupBuffers(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec3> uvs, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents);
	GLuint setupBuffers(std::vector<glm::vec3> verticesStart, std::vector<glm::vec3> verticesEnd, std::vector<glm::vec3> normalsStart, std::vector<glm::vec3> normalsEnd, std::vector<glm::vec3> uvsStart, std::vector<glm::vec3> uvsEnd);
	GLuint setupBuffers(std::vector<glm::vec3> points, std::vector<unsigned int> indices);
	GLuint setupBuffers(std::vector<glm::vec3> points, std::vector<unsigned int> indices, std::vector<glm::vec3> normals);
};



#endif /* RENDERER_HPP_ */
