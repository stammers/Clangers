#include "objectloader.hpp"

bool ObjectLoader::loadOBJ(std::string path,std::vector<glm::vec3> & vertices,std::vector<glm::vec3> & uvs,std::vector<glm::vec3> & normals, std::vector<glm::vec3> & colours, bool verticesOnly){
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec3> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec3> temp_colours;
	bool usingColours = false;

	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		std::cout << "Can't open the file " << path << std::endl;
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			break;
		}

		if ( strcmp( lineHeader, "v" ) == 0 ){ //vertex
			glm::vec3 vertex;
			glm::vec3 colour;
			int matches = fscanf(file, "%f %f %f %f %f %f\n", &vertex.x, &vertex.y, &vertex.z, &colour.x, &colour.y, &colour.z );
			temp_vertices.push_back(vertex);

			//if there's 6 matches then using per vertex colour as well
			if(matches == 6){
				temp_colours.push_back(colour);
				usingColours = true;
			}
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){ //uv coordinates
			glm::vec3 uv;
			fscanf(file, "%f %f %f\n", &uv.x, &uv.y, &uv.z);
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){ //normal
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){ //face
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches;
			if(verticesOnly){
				matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			}else{
				matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			}
			if (matches == 9){
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}else if(matches == 3){
				verticesOnly = true;
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
			}else{
				printf("Can only read in shapes made from triangles\n");
				return false;
			}

		}else{ // Probably a comment, eat up the rest of the line
			char otherCharacters[1000];
			fgets(otherCharacters, 1000, file);
		}
	}
	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex-1];


		// Put the attributes in buffers
		vertices.push_back(vertex);

		if(usingColours){
			glm::vec3 colour = temp_colours[vertexIndex-1];
			colours.push_back(colour);
		}


		if(!verticesOnly){
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 uv = temp_uvs[uvIndex-1];
			glm::vec3 normal = temp_normals[normalIndex-1];
			uvs.push_back(uv);
			normals.push_back(normal);
		}

	}
	return true;
}




