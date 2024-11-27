#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "Camera.h"
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
	Camera camera(5.0f, glm::radians(45.0f), glm::radians(45.0f));

	// Transformation matrices
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.001f, 1000.0f);

	// Controls
	double cursorX, cursorY;
	double lastX, lastY;
	glfwGetCursorPos(window, &lastX, &lastY);


	// SHADER SETUP
	// Activate shader
	glUseProgram(shaderProgram);

	// Uniform locations
	GLuint modelLocation = glGetUniformLocation(shaderProgram, "model");
	GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
	GLuint projLocation = glGetUniformLocation(shaderProgram, "projection");


	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {
		// Poll for process events
		glfwPollEvents();

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Close on ESC
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);


		// MOVE CAMERA
		float deltaX = 0.0f;
		float deltaY = 0.0f;
		float deltaR = 0.0f;

		// Radius
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			deltaR--;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			deltaR++;

		// Theta and phi
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			// Enable unlimited movement
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			// Calculate movement
			glfwGetCursorPos(window, &cursorX, &cursorY);
			deltaX = cursorX - lastX;
			deltaY = cursorY - lastY;
		}
		else {
			// Restore normal cursor behaviour
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		// Update previous cursor position
		glfwGetCursorPos(window, &lastX, &lastY);

		// Update camera
		camera.update(deltaX, deltaY, deltaR);

		// Recalculate view matrix
		glm::mat4 view = camera.getViewMatrix();


		// RENDER
		// Update uniform values
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind vao
		glBindVertexArray(vao);

		// Draw
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
