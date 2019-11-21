#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIN_SIZE_WIDTH 1024
#define WIN_SIZE_HEIGHT 768

/// <summary>
/// Function for handling events when the window is resized.
///
/// PARAMETERS:
/// - window: Pointer to the window to be handled
/// - width: Window's new width
/// - height: Window's new height
///
/// </summary>
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // Setting the viewport to a new size!
}

/// <summary>
/// Function for handling events when the window received an input.
///
/// PARAMETERS:
/// - window: Pointer to the window to be handled
///
/// </summary>
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfwWindowHint is specific for each platform (e.g. mac OS, windows 10...)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // If the version of the user's GPU are below of the GL requirements... We must handle
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef MAC_OS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	std::cout << "Application started!" << std::endl;

	// Creating the window regardless the operating system
	GLFWwindow* window = glfwCreateWindow(WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT, "My Game", NULL, NULL);

	// Handling the error if the window wasn't created
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Loading GLAD's manager to handle OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // Registering a callback related to Window resize

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT); // Painting the with the clearColor parameters
        
        processInput(window); // Checking for interruptions
        
		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents(); // Signalize tha application that an event was dispatched
	}

	glfwTerminate();

	return 0;
}
