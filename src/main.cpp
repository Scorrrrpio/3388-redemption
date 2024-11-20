#include <iostream>
#include <GLFW/glfw3.h>

int main(void) {
	// SETUP
	GLFWwindow* window;

	// initialize glfw
	if (!glfwInit()) {
		std::cerr << "Failed to Initialize GLFW" << std::endl;
		return -1;
	}

	// enable 4x multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	// create window
	window = glfwCreateWindow(1280, 720, "Exercise 1", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {
		// poll for process events
		glfwPollEvents();

		// render
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 1, 1);

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0.5);
		glVertex2f(0.5, -0.25);
		glVertex2f(-0.5, -0.25);
		glEnd();

		// swap buffers
		glfwSwapBuffers(window);
	}


	// SHUTDOWN
	glfwTerminate();
	return 0;
}
