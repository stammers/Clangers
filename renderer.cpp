#include "renderer.hpp"
#include <algorithm>
#include "resourceLoader.hpp"
#include <memory>

GLuint Renderer::setupBuffers(std::vector<glm::vec3> points, std::vector<glm::vec3> normals, std::vector<glm::vec3> uvs, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents){

	GLuint vao = 0;
	glGenVertexArrays (1, &vao); //create new vertex array object
	glBindVertexArray (vao); //bind as current vertex array object

	GLuint points_vbo = 0;
	glGenBuffers (1, &points_vbo); // generate empty buffer
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo); //bind as current buffer
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), &points[0], GL_STATIC_DRAW); //copy points into buffer

	GLuint normals_vbo = 0;
	glGenBuffers (1, &normals_vbo); // generate empty buffer
	glBindBuffer (GL_ARRAY_BUFFER, normals_vbo); //bind as current buffer
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

	GLuint uvs_vbo = 0;
	glGenBuffers (1, &uvs_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, uvs_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

	if(tangents.size() > 0){ //only creates buffers for tangents and bitangents if they are used, prevents crash on nvidia machines on windows
		GLuint tangents_vbo = 0;
		glGenBuffers (1, &tangents_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, tangents_vbo);
		glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * tangents.size(), &tangents[0], GL_STATIC_DRAW);

		GLuint bitangents_vbo = 0;
		glGenBuffers (1, &bitangents_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, bitangents_vbo);
		glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * bitangents.size(), &bitangents[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray (3);
		glBindBuffer (GL_ARRAY_BUFFER, tangents_vbo);
		glVertexAttribPointer (3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray (4);
		glBindBuffer (GL_ARRAY_BUFFER, bitangents_vbo);
		glVertexAttribPointer (4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //defines the layout of our first vertex buffer; "0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats (GL_FLOAT) in the buffer.

	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray (2);
	glBindBuffer (GL_ARRAY_BUFFER, uvs_vbo);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);

	return vao;
}

GLuint Renderer::setupBuffers(std::vector<glm::vec3> verticesStart, std::vector<glm::vec3> verticesEnd, std::vector<glm::vec3> normalsStart, std::vector<glm::vec3> normalsEnd, std::vector<glm::vec3> uvsStart, std::vector<glm::vec3> uvsEnd){

	GLuint vao = 0;
	glGenVertexArrays (1, &vao); //create new vertex array object
	glBindVertexArray (vao); //bind as current vertex array object

	GLuint verticesStart_vbo = 0;
	glGenBuffers (1, &verticesStart_vbo); // generate empty buffer
	glBindBuffer (GL_ARRAY_BUFFER, verticesStart_vbo); //bind as current buffer
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * verticesStart.size(), &verticesStart[0], GL_STATIC_DRAW); //copy points into buffer

	GLuint verticesEnd_vbo = 0;
	glGenBuffers (1, &verticesEnd_vbo); // generate empty buffer
	glBindBuffer (GL_ARRAY_BUFFER, verticesEnd_vbo); //bind as current buffer
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * verticesEnd.size(), &verticesEnd[0], GL_STATIC_DRAW);

	GLuint normalsStart_vbo = 0;
	glGenBuffers (1, &normalsStart_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, normalsStart_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * normalsStart.size(), &normalsStart[0], GL_STATIC_DRAW);

	GLuint normalsEnd_vbo = 0;
	glGenBuffers (1, &normalsEnd_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, normalsEnd_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * normalsEnd.size(), &normalsEnd[0], GL_STATIC_DRAW);

	GLuint uvsStart_vbo = 0;
	glGenBuffers (1, &uvsStart_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, uvsStart_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * uvsStart.size(), &uvsStart[0], GL_STATIC_DRAW);

	GLuint uvsEnd_vbo = 0;
	glGenBuffers (1, &uvsEnd_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, uvsEnd_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec3) * uvsEnd.size(), &uvsEnd[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, verticesStart_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //defines the layout of our first vertex buffer; "0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats (GL_FLOAT) in the buffer.

	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, verticesEnd_vbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray (2);
	glBindBuffer (GL_ARRAY_BUFFER, normalsStart_vbo);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray (3);
	glBindBuffer (GL_ARRAY_BUFFER, normalsEnd_vbo);
	glVertexAttribPointer (3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray (4);
	glBindBuffer (GL_ARRAY_BUFFER, uvsStart_vbo);
	glVertexAttribPointer (4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray (5);
	glBindBuffer (GL_ARRAY_BUFFER, uvsEnd_vbo);
	glVertexAttribPointer (5, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
	return vao;
}

//returns a VAO reference which is set up to contain one element buffer containing the indices
//and one array buffer containing the vertices
GLuint Renderer::setupBuffers(std::vector<glm::vec3> points, std::vector<unsigned int> indices){

	GLuint vao = 0;
	glGenVertexArrays (1, &vao); //create new vertex array object
	glBindVertexArray (vao); //bind as current vertex array object

	// Generate a buffer for the indices
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	GLuint points_vbo = 0;
	glGenBuffers (1, &points_vbo); // generate empty buffer
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo); //bind as current buffer
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * points.size(), &points[0], GL_STATIC_DRAW); //copy points into buffer


	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //defines the layout of our first vertex buffer; "0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats (GL_FLOAT) in the buffer.

	return vao;
}

GLuint Renderer::setupBuffers(std::vector<glm::vec3> points, std::vector<unsigned int> indices, std::vector<glm::vec3> normals){

	GLuint vao = 0;
	glGenVertexArrays (1, &vao); //create new vertex array object
	glBindVertexArray (vao); //bind as current vertex array object

	// Generate a buffer for the indices
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	GLuint points_vbo = 0;
	glGenBuffers (1, &points_vbo); // generate empty buffer
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo); //bind as current buffer
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * points.size(), &points[0], GL_STATIC_DRAW); //copy points into buffer

	GLuint normals_vbo = 0;
	glGenBuffers (1, &normals_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * normals.size(), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //defines the layout of our first vertex buffer; "0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats (GL_FLOAT) in the buffer.
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	return vao;
}

GLuint Renderer::sphere(int subdivisions, int &verticesNum){

	std::vector<glm::vec3> points = sphereObject.calculateSpherePoints(subdivisions);

	std::vector<unsigned int> indices = sphereObject.getIndices();
	verticesNum = indices.size();
	return setupBuffers(points, indices, points);
}

GLuint Renderer::object(int &verticesNum, std::string name, bool normalMap, bool perVertexColour){
	// Read our .obj file
	std::string objectName = "./resources/objects/" + name + ".obj";
	std::vector< glm::vec3 > vertices;


	std::vector< glm::vec3 > uvs;
	std::vector< glm::vec3 > normals;
	std::vector<glm::vec3> colours;
	bool res = loader.loadOBJ(objectName, vertices, uvs, normals, colours, false);

	//if it can't load from the object file with uvs and normals then try again
	//but just look for vertices
	if(!res){
		res = loader.loadOBJ(objectName, vertices, uvs, normals, colours, true);
	}
	verticesNum = vertices.size();

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	//calculate the tangents and bitangents if normal mapping is to be used
	if(normalMap){
		for(int i=0; i < verticesNum; i+=3){
			// Shortcuts for vertices
			glm::vec3 & v0 = vertices[i+0];
			glm::vec3 & v1 = vertices[i+1];
			glm::vec3 & v2 = vertices[i+2];

			// Shortcuts for UVs
			glm::vec3 & uv0 = uvs[i+0];
			glm::vec3 & uv1 = uvs[i+1];
			glm::vec3 & uv2 = uvs[i+2];

			// Edges of the triangle : position delta
			glm::vec3 deltaPos1 = v1-v0;
			glm::vec3 deltaPos2 = v2-v0;

			// UV delta
			glm::vec3 deltaUV1 = uv1-uv0;
			glm::vec3 deltaUV2 = uv2-uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
			glm::vec3 tangent1 = glm::normalize(tangent - normals[i] * glm::dot(normals[i], tangent));
			glm::vec3 tangent2 = glm::normalize(tangent - normals[i+1] * glm::dot(normals[i+1], tangent));
			glm::vec3 tangent3 = glm::normalize(tangent - normals[i+2] * glm::dot(normals[i+2], tangent));
			glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

			tangents.push_back(tangent1);
			tangents.push_back(tangent2);
			tangents.push_back(tangent3);

			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);

		}
	}

	if(perVertexColour){
		return setupBuffers(vertices, normals, colours, tangents, bitangents);
	}else{
		return setupBuffers(vertices, normals, uvs, tangents, bitangents);
	}

}

GLuint Renderer::animatedObject(int &verticesNum, std::string start, std::string end){
	std::vector<glm::vec3> colours;

	std::string startObjectName = "./resources/objects/" + start + ".obj";
	std::vector< glm::vec3 > verticesStart;
	std::vector< glm::vec3 > uvsStart;
	std::vector< glm::vec3 > normalsStart;

	bool res = loader.loadOBJ(startObjectName, verticesStart, uvsStart, normalsStart, colours, false);

	//if it can't load from the object file with uvs and normals then try again
	//but just look for vertices
	if(!res){
		res = loader.loadOBJ(startObjectName, verticesStart, uvsStart, normalsStart, colours, true);
	}
	verticesNum = verticesStart.size();

	std::string endObjectName = "./resources/objects/" + end + ".obj";
	std::vector< glm::vec3 > verticesEnd;
	std::vector< glm::vec3 > uvsEnd;
	std::vector< glm::vec3 > normalsEnd;
	res = loader.loadOBJ(endObjectName, verticesEnd, uvsEnd, normalsEnd, colours, false);

	//if it can't load from the object file with uvs and normals then try again
	//but just look for vertices
	if(!res){
		res = loader.loadOBJ(endObjectName, verticesEnd, uvsEnd, normalsEnd, colours, true);
	}


	return setupBuffers(verticesStart, verticesEnd, normalsStart, normalsEnd, uvsStart, uvsEnd);


}

GLuint Renderer::texture(std::string name){
	name = "./resources/textures/" + name;
	FILE * file = fopen(name.c_str(), "r");
	if( file == NULL ){
		std::cout << "Can't open the file " << name << std::endl;
		return 0;
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
	std::auto_ptr<glimg::ImageSet> imageSet(glimg::loaders::stb::LoadFromFile(name));
	glimg::CreateTexture(textureID, imageSet.get(), 0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return textureID;
}

GLuint Renderer::skybox(){
	std::string name = "./resources/textures/nebula2.dds";
	FILE * file = fopen(name.c_str(), "r");
	if( file == NULL ){
		std::cout << "Can't open the file " << name << std::endl;
		return 0;
	}
	GLuint textureID;
	//ResourceLoader loader;
	//int width = 4096;
	//int height = 4096;
	glGenTextures(1, &textureID);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	std::auto_ptr<glimg::ImageSet> imageSet(glimg::loaders::dds::LoadFromFile(name));
	textureID = glimg::CreateTexture(imageSet.get(), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//GLenum imageFormat;
	//imageFormat = glimg::GetInternalFormat(image.GetFormat(),0);
	//glimg::Dimensions dims = imageSet->GetDimensions();
	//GLenum imageFormat = (GLenum)glimg::GetInternalFormat(imageSet->GetFormat(), 0);

	//	for(int i = 0; i < 6; i++){
	//		glimg::SingleImage image = imageSet->GetImage(0, 0, i);
	//		glimg::Dimensions dimensions = image.GetDimensions();
	//		std::cout << dimensions.height << std::endl;
	//		glimg::OpenGLPixelTransferParams params =  glimg::GetUploadFormatType(image.GetFormat(), 0);
	//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB8, dimensions.width, dimensions.height, 0, params.format, params.type, image.GetImageData());
	//		//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, dimensions.width, dimensions.height, 0, params.format, params.type, imageSet->GetImage(0, 0, 1).GetImageData());
	//		//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, dimensions.width, dimensions.height, 0, params.format, params.type, imageSet->GetImage(0, 0, 2).GetImageData());
	//		//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, dimensions.width, dimensions.height, 0, params.format, params.type, imageSet->GetImage(0, 0, 3).GetImageData());
	//		//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, dimensions.width, dimensions.height, 0, params.format, params.type, imageSet->GetImage(0, 0, 4).GetImageData());
	//		//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, dimensions.width, dimensions.height, 0, params.format, params.type, imageSet->GetImage(0, 0, 5).GetImageData());
	//		//glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, params.format, dimensions.width, dimensions.height, 0, image.GetImageByteSize(), image.GetImageData());
	//	}

	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, loader.LoadBMP("./resources/posx.bmp"));
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, loader.LoadBMP("./resources/negx.bmp"));
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, loader.LoadBMP("./resources/posy.bmp"));
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, loader.LoadBMP("./resources/negy.bmp"));
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, loader.LoadBMP("./resources/posz.bmp"));
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, loader.LoadBMP("./resources/negz.bmp"));

	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return textureID;

}

GLuint Renderer::cube(int &verticesNum){
	std::vector<glm::vec3> points;
	std::vector<unsigned int> indices;
	float size = 50.0f;

	points.push_back(glm::vec3(-size, -size, -size)); //0
	points.push_back(glm::vec3(-size, -size, size)); //1
	points.push_back(glm::vec3(-size, size, size)); //2
	points.push_back(glm::vec3(-size, size, -size)); //3
	points.push_back(glm::vec3(size, size, -size)); //4
	points.push_back(glm::vec3(size, -size, -size)); //5
	points.push_back(glm::vec3(size, -size, size)); //6
	points.push_back(glm::vec3(size, size, size)); //7

	//back upper
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	//back lower
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(4);

	//base back
	indices.push_back(6);
	indices.push_back(0);
	indices.push_back(5);

	//base front
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(0);

	//top front
	indices.push_back(7);
	indices.push_back(2);
	indices.push_back(3);

	//top back
	indices.push_back(7);
	indices.push_back(4);
	indices.push_back(3);

	//right upper
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(4);

	//right lower
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(6);

	//left lower
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	//left upper
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);


	//front lower
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(1);

	//front upper
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(7);

	std::vector<glm::vec3> colours;
	colours.push_back(glm::vec3(0.0, 0.0, 1.0));
	colours.push_back(glm::vec3(0.0, 1.0, 0.0));
	colours.push_back(glm::vec3(1.0, 0.0, 0.0));
	colours.push_back(glm::vec3(1.0, 1.0, 0.0));

	colours.push_back(glm::vec3(1.0, 0.0, 1.0));
	colours.push_back(glm::vec3(0.0, 1.0, 1.0));
	colours.push_back(glm::vec3(1.0, 1.0, 1.0));
	colours.push_back(glm::vec3(1.0, 0.5, 0.5));

	verticesNum = indices.size();
	return setupBuffers(points, indices);
}



