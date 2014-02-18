#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec3 uv;
layout(location = 3) in vec3 tangents;
layout(location = 4) in vec3 bitangents;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat3 MV;
uniform vec3 lightDirection;
uniform mat4 shadowMVP;

out vec3 texcoords;
out vec3 normal;
out vec3 tangent;
out vec3 bitangent;
out vec3 lightDirectionTS;
out vec3 eyeDirectionTS;
out vec4 shadowCoords;
out vec3 vertexPositionWS;


void main() {
	normal = normals;
	texcoords = uv;
	tangent = tangents;
	bitangent = bitangents;
	
	vec3 tangentCS = MV * tangents;
	vec3 normalCS = MV * normals;
	vec3 bitangentCS = MV * bitangents;
	
	vec3 vertexPositionCS = (V * M * vec4(vertex_position, 1.0)).xyz;
	vec3 eyeDirectionCS = vec3(0, 0, 0) - vertexPositionCS;
	
	vec3 lightPositionCS = (V * vec4(lightDirection, 1.0)).xyz;
	vec3 lightDirectionCS = lightPositionCS + eyeDirectionCS;
	
	// Position of the vertex, in worldspace : M * position
	vertexPositionWS = (M * vec4(vertex_position, 1.0)).xyz;
	
	mat3 TBN = transpose(mat3(tangentCS, bitangentCS, normalCS));
	lightDirectionTS = TBN * lightDirectionCS;
	eyeDirectionTS = TBN * eyeDirectionCS;
  	gl_Position = MVP * vec4(vertex_position, 1.0);
  	
  	shadowCoords = shadowMVP * vec4(vertex_position, 1.0);
}