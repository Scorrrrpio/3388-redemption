#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 vertPos;
out vec3 vertNormal;
out vec2 vertUv;
out vec3 vertEyeDir;
out vec3 vertLightDir;

uniform float time;
uniform float texScale;

uniform vec3 lightPos;
uniform vec3 eyePos;

void main() {
	vec2 texOffset = vec2(sin(time) * 0.5, cos(time) * 0.5);

	vertPos = aPos;
	vertNormal = aNormal;
	vertUv = (aPos.xz + texOffset + time * 0.08) / texScale;

	vertLightDir = normalize(lightPos - aPos);
	vertEyeDir = normalize(eyePos - aPos);
}
