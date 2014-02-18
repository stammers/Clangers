#version 330 core

in vec3 texcoords;

uniform samplerCube cubeMap;

out vec4 frag_colour;

void main () {
  frag_colour = texture(cubeMap, texcoords);
}
