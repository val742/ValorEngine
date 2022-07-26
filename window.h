#ifndef WINDOW_H
#define WINDOW_H
#include <GLFW/glfw3.h>
#include <vector>

class valorWindow {
private:
	GLFWwindow* window;
public:
	GLFWwindow* makeWindow();
	void cleanup();
};

#endif // !WINDOW_H