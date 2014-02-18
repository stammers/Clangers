#version 330 core
in vec3 normal;
in vec3 colour;

uniform vec3 lightDirection;
uniform vec3 lightColour;

out vec4 frag_colour;

void main () {
	float theta = dot(normal, lightDirection);
	vec3 ambient = vec3(0.2, 0.2, 0.2) * colour * lightColour;
	vec3 colourNew = ambient + lightColour * colour * clamp(theta, 0.0, 1.0);
	frag_colour = vec4(colourNew, 1.0);
}
