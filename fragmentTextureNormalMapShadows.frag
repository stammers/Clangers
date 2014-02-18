#version 330 core

//Much of the shadow code was modifier from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/


in vec3 texcoords;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec3 lightDirectionTS;
in vec3 normalTS;
in vec4 shadowCoords;
in vec3 vertexPositionWS;

uniform sampler2D tex;
uniform sampler2D normalTex;
uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform sampler2D shadowMap;

out vec4 frag_colour;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

// Returns a random number based on a vec3 and an int.
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

void main () {
	//Normal Lighting
	vec3 normalTS = texture2D(normalTex, vec2(texcoords.x, -texcoords.y)).rgb *2.0 - 1.0;
	float theta = dot(normalTS, lightDirection);
	float thetaOriginal = dot(normal, lightDirection);
	vec3 ambient = vec3(0.1, 0.1, 0.1) * texture2D(tex, texcoords.xy).xyz * lightColour;
	vec3 colour = vec3(0.15, 0.15, 0.15) * lightColour * texture2D(tex, texcoords.xy).xyz * clamp(theta, 0.0, 1.0);
	vec3 colour2 = lightColour * texture2D(tex, texcoords.xy).xyz * clamp(thetaOriginal, 0.0, 1.0);
	
	

	//Shadows
	//float visibility = texture( shadowMap, vec3(shadowCoords.xy, (shadowCoords.z)/shadowCoords.w) );
	float bias = 0.005*tan(acos(theta));
	bias = clamp(bias, 0, 0.01);
	float visibility = 1.0;
	for (int i = 0; i < 4; i++){
		int index = int(16.0  *random(floor(vertexPositionWS.xyz * 1000.0), i)) % 16;
  		visibility -= 0.3 * (1.0 - texture(shadowMap, vec3(shadowCoords.xy + poissonDisk[index] / 4000.0,  (shadowCoords.z - bias) / shadowCoords.w).xy).z);
	}

	
   	frag_colour = vec4(visibility * (colour + colour2), 1.0);
}
