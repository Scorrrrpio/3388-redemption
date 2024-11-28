#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 worldPos;
out vec3 vertexNormal;
out vec2 uv;
out vec3 lightDirection;
out vec3 eyeDirection;

uniform float time;
uniform float texScale;

uniform vec3 lightPos;
uniform vec3 eyePos;

// NOTE: MVP will move to geometry shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vec2 texOffset = vec2(sin(time) * 0.5, cos(time) * 0.5);

	worldPos = aPos;
	vertexNormal = aNormal;
	uv = (aPos.xz + texOffset + time * 0.08) / texScale;
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	lightDirection = normalize(lightPos - aPos);
	eyeDirection = normalize(eyePos - aPos);
}
