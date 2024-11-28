#version 450 core

layout(triangles) in;
in vec3 tesPos[];
in vec3 tesNormal[];
in vec2 tesUv[];
in vec3 tesEyeDir[];
in vec3 tesLightDir[];

layout(triangle_strip, max_vertices = 3) out;
out vec3 geoPos;
out vec3 geoNormal;
out vec2 geoUv;
out vec3 geoEyeDir;
out vec3 geoLightDir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	mat4 MVP = projection * view * model;

	for (int i = 0; i < 3; i++) {
		vec4 worldPos = MVP * vec4(tesPos[i], 1);
		gl_Position = worldPos;
		geoPos = worldPos.xyz;
		geoNormal = tesNormal[i];
		geoUv = tesUv[i];
		geoEyeDir = tesEyeDir[i];
		geoLightDir = tesLightDir[i];
		EmitVertex();
	}
	EndPrimitive();
}
