#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <string>

std::string readShaderCode(std::string path) {
	// Open file
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Failed to open shader file at " << path << std::endl;
		return "";
	}

	// Read file contents using stringstream
	std::ostringstream ss;
	ss << file.rdbuf();

	// Close file and return string
	file.close();
	return ss.str();
}

void checkShaderCompilation(GLuint shader, std::string type) {
	int success;
	char infolog[1024];
	if (type != "PROGRAM") {
		// Compilation errors
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, nullptr, infolog);
			std::cerr << "Shader compilation error of type: " << type << "\n" << infolog << std::endl;
		}
		else {
			std::cout << type << " Shader compilation successful" << std::endl;
		}

	}
	else {
		// Linking errors
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, nullptr, infolog);
			std::cerr << "Shader linking error of type: " << type << "\n" << infolog << std::endl;
		}
		else {
			std::cout << "Shader linking successful" << std::endl;
		}
	}
}

GLuint compileShaders() {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shader code from files
	std::string vertexShaderCode = readShaderCode("./shaders/waves.vert.glsl");
	std::string fragmentShaderCode = readShaderCode("./shaders/waves.frag.glsl");

	// Compile shaders
	const char* vertexShaderPtr = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderPtr, NULL);
	glCompileShader(vertexShader);
	checkShaderCompilation(vertexShader, "VERTEX");

	const char* fragmentShaderPtr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderPtr, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader, "FRAGMENT");

	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderCompilation(shaderProgram, "PROGRAM");
	
	// Delete vertex and fragment shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
