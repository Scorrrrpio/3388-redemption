#version 450 core

in vec3 vertPos[];
in vec3 vertNormal[];
in vec2 vertUv[];
in vec3 vertEyeDir[];
in vec3 vertLightDir[];

layout(vertices = 3) out;
out vec3 tcsPos[];
out vec3 tcsNormal[];
out vec2 tcsUv[];
out vec3 tcsEyeDir[];
out vec3 tcsLightDir[];

void main() {
	tcsPos[gl_InvocationID] = vertPos[gl_InvocationID];
	tcsNormal[gl_InvocationID] = vertNormal[gl_InvocationID];
	tcsUv[gl_InvocationID] = vertUv[gl_InvocationID];
	tcsEyeDir[gl_InvocationID] = vertEyeDir[gl_InvocationID];
	tcsLightDir[gl_InvocationID] = vertLightDir[gl_InvocationID];

	gl_TessLevelOuter[0] = 16.0;
	gl_TessLevelOuter[1] = 16.0;
	gl_TessLevelOuter[2] = 16.0;
	gl_TessLevelInner[0] = 16.0;
}
