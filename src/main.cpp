#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "ShaderUtils.h"

float vertices[] = {
	//  X,     Y,     Z,    R,    G,    B
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f,
};

unsigned int indices[] = {
	0, 1, 2, 2, 3, 0,  // back
	4, 5, 6, 6, 7, 4,  // front
	0, 1, 5, 5, 4, 0,  // bottom
	2, 3, 7, 7, 6, 2,  // top
	0, 3, 7, 7, 4, 0,  // left
	1, 2, 6, 6, 5, 1   // right
};

int main(void) {
	// SETUP
	GLFWwindow* window;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to Initialize GLFW" << std::endl;
		return -1;
	}

	// Enable 4x multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create window
	window = glfwCreateWindow(1280, 720, "Exercise 1", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);


	// SHADERS
	GLuint shaderProgram = compileShaders();


	// VAO, VBO, and EBO
	GLuint vao, vbo, ebo;

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unind VAO
	glBindVertexArray(0);


	// CAMERA
	// Transformation matrices
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 eye = {5.0f, 5.0f, 5.0f};
	glm::vec3 centre = {0.0f, 0.0f, 0.0f};
	glm::vec3 up = {0.0f, 1.0f, 0.0f};
	glm::mat4 view = glm::lookAt(eye, centre, up);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.001f, 1000.0f);



	// SHADER SETUP
	// Activate shader
	glUseProgram(shaderProgram);

	// Set up uniform values
	GLuint modelLocation = glGetUniformLocation(shaderProgram, "model");
	GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
	GLuint projLocation = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));


	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {
		// Poll for process events
		glfwPollEvents();

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// RENDER
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);
	}


	// SHUTDOWN
	// Cleanup
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(shaderProgram);

	// Terminate
	glfwTerminate();
	return 0;
}
