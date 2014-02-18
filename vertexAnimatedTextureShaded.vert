#version 330 core

layout(location = 0) in vec3 vertex_positionStart;
layout(location = 1) in vec3 vertex_positionEnd;
layout(location = 2) in vec3 normalsStart;
layout(location = 3) in vec3 normalsEnd;
layout(location = 4) in vec3 uvStart;
layout(location = 5) in vec3 uvEnd;

uniform mat4 MVP;
uniform mat4 M;
uniform float startW;
uniform float endW;

out vec3 texcoords;
out vec3 normal;

void main() {
  	//get a sum of weights and work out factors for each target
  	float sumW = startW + endW;
  	float startF = startW / sumW;
  	float endF = endW / sumW;

 	//interpolate targets to give us current pose
 	vec3 vertex_position = startF * vertex_positionStart + endF * vertex_positionEnd;
	vec3 normals = startF * normalsStart + endF * normalsEnd;
	vec3 uv = startF * uvStart + endF * uvEnd;
  
	mat4 normalMatrix = inverse(M);
	normalMatrix = transpose(normalMatrix);
	normal = normalize(mat3(normalMatrix) * normals);
	texcoords = uv;
	
  	gl_Position = MVP * vec4(vertex_position, 1.0);
}