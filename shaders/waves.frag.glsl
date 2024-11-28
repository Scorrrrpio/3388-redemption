#version 330 core

in vec3 worldPos;
in vec3 vertexNormal;
in vec2 uv;
in vec3 eyeDirection;
in vec3 lightDirection;

out vec4 fragColour;

void main() {
	fragColour = vec4(uv, 0.0, 1.0);
}
