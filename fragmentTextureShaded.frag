#version 330 core

in vec3 texcoords;
in vec3 normal;

uniform sampler2D tex;
uniform vec3 lightDirection;
uniform vec3 lightColour;

out vec4 frag_colour;

void main () {
	float theta = dot(normal, lightDirection);
	vec3 ambient = vec3(0.15, 0.15, 0.15) * texture2D(tex, texcoords.xy).xyz * lightColour;
	vec3 colour = lightColour * texture2D(tex, texcoords.xy).xyz * clamp(theta, 0.0, 1.0);
   	frag_colour = vec4(ambient + colour, 1.0);
}
