#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec3 colours;

uniform mat4 MVP;
uniform mat4 M;

out vec3 normal;
out vec3 colour;

void main() {
	mat4 normalMatrix = inverse(M);
	normalMatrix = transpose(normalMatrix);
	normal = normalize(mat3(normalMatrix) * normals);
	colour = colours;
  	gl_Position = MVP * vec4(vertex_position, 1.0);
}