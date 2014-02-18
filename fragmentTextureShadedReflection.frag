#version 330 core

in vec3 texcoords;
in vec3 normal;
in vec3 vertexPositionCS;
in vec3 eyeDirectionCS;
in vec3 lightDirectionCS;

uniform sampler2D tex;
uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform mat4 MV;
uniform mat4 V;
uniform samplerCube cubeTex;

out vec4 frag_colour;

void main () {
	float theta = dot(normal, lightDirection);
	vec3 ambient = vec3(0.15, 0.15, 0.15) * texture2D(tex, texcoords.xy).rgb * lightColour;
	vec3 diffuse = vec3(0.7, 0.7, 0.7) * lightColour * texture2D(tex, texcoords.xy).rgb * clamp(theta, 0.0, 1.0);
	
	vec3 eye = normalize(eyeDirectionCS);
	vec3 reflectValue = reflect(normalize(lightDirectionCS), normal);
	float alpha = clamp(dot(eye, reflectValue ), 0.0, 1.0);
	
	vec3 specular = vec3(0.3, 0.3, 0.3) * lightColour * pow(alpha, 5.0);
	
	/* reflect ray around normal from eye to surface */
	vec3 incident_eye = normalize (eyeDirectionCS);
	
	vec3 reflected = reflect (incident_eye, normal);
	// convert from eye to world space
	reflected = vec3 (inverse (V) * vec4 (reflected, 0.0));
	
   	frag_colour = vec4(ambient + diffuse + specular + texture (cubeTex, reflected).xyz, 1.0);
   	
   

}