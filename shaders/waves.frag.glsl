#version 450 core

in vec3 geoPos;
in vec3 geoNormal;
in vec2 geoUv;
in vec3 geoEyeDir;
in vec3 geoLightDir;

out vec4 fragColour;

void main() {
	fragColour = vec4(geoUv, 0.0, 1.0);
}
