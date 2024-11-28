#version 450 core

layout(triangles, equal_spacing, cw) in;
in vec3 tcsPos[];
in vec3 tcsNormal[];
in vec2 tcsUv[];
in vec3 tcsEyeDir[];
in vec3 tcsLightDir[];

out vec3 tesPos;
out vec3 tesNormal;
out vec2 tesUv;
out vec3 tesEyeDir;
out vec3 tesLightDir;

void main() {
	tesPos = gl_TessCoord.x * tcsPos[0] +
		 gl_TessCoord.y * tcsPos[1] +
		 gl_TessCoord.z * tcsPos[2];
	tesNormal = normalize(gl_TessCoord.x * tcsNormal[0] +
			      gl_TessCoord.y * tcsNormal[1] +
			      gl_TessCoord.z * tcsNormal[2]);
	tesUv = gl_TessCoord.x * tcsUv[0] +
		gl_TessCoord.y * tcsUv[1] +
		gl_TessCoord.z * tcsUv[2];
	tesEyeDir = normalize(gl_TessCoord.x * tcsEyeDir[0] +
			      gl_TessCoord.y * tcsEyeDir[1] +
			      gl_TessCoord.z * tcsEyeDir[2]);
	tesLightDir = normalize(gl_TessCoord.x * tcsLightDir[0] +
			        gl_TessCoord.y * tcsLightDir[1] +
			        gl_TessCoord.z * tcsLightDir[2]);
}
