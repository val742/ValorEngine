#include "Window.h"

GLFWwindow* window() {
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	
};
void valorWindow::cleanup() {
	glfwDestroyWindow(window);
};