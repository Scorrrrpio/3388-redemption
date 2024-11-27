#version 330 core
in vec3 vertexNormal;
out vec4 fragColour;

void main() {
	fragColour = vec4(vertexNormal, 1.0);
}
