// Valor engine by Valores M.
// Using GLFW to create window and process input
#include <GLFW/glfw3.h>
#include "window.h"

valorWindow vw;

int main() {

	// Make window
	vw.makeWindow();
	// Window cleanup command
	vw.cleanup();
	return(0);
};

