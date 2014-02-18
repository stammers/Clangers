#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec3 uv;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightDirection;

out vec3 texcoords;
out vec3 normal;
out vec3 eyeDirectionCS;
out vec3 lightDirectionCS;

void main() {
	mat4 normalMatrix = inverse(M);
	normalMatrix = transpose(normalMatrix);
	normal = normalize(mat3(normalMatrix) * normals);
	texcoords = uv;
	
	vec3 vertexPositionCS = ( V * M * vec4(vertex_position, 1.0)).xyz;
	eyeDirectionCS = vec3(0.0 ,0.0, 0.0) - vertexPositionCS;

	vec3 lightPositionCS = ( V * M * vec4(lightDirection, 1.0)).xyz;
	lightDirectionCS = lightPositionCS + eyeDirectionCS;
	
  	gl_Position = MVP * vec4(vertex_position, 1.0);
}