#include <string>
#include <fstream>

#include "utils.hpp"

using namespace std;

//Shader loading code modified from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, ios::in);
	if(VertexShaderStream.is_open()){
		string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, ios::in);
	if(FragmentShaderStream.is_open()){
		string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , 0);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	//only print an error if there is one
	if(&VertexShaderErrorMessage[0] != NULL){
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
	}


	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , 0);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	//only print an error if there is one
	if(&FragmentShaderErrorMessage[0] != NULL){
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
	}


	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void checkErrors(){
	// check OpenGL error
	bool error = false;
	GLenum err = glGetError();
		switch (err) {
		case GL_NO_ERROR:
			std::cout << "No Error" << std::endl;
			break;

		case GL_INVALID_ENUM:
			std::cout <<  "GL_INVALID_ENUM" << std::endl;
			error = true;
			break;

		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE" << std::endl;
			error = true;
			break;

		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION" << std::endl;
			error = true;
			break;

		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW" << std::endl;
			error = true;
			break;

		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW" << std::endl;
			error = true;
			break;

		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
			error = true;
			break;
		}
	if(error){
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
}



