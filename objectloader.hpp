#ifndef OBJECTLOADER_HPP_
#define OBJECTLOADER_HPP_

#include "common.hpp"

class ObjectLoader{
public:
	bool loadOBJ(std::string vertex_file_path,std::vector<glm::vec3> & vertices,std::vector<glm::vec3> & uvs,std::vector<glm::vec3> & normals, std::vector<glm::vec3> & colours, bool verticesOnly);
};



#endif /* OBJECTLOADER_HPP_ */
