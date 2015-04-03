#include <Dunjun/Common.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLOBAL int g_windowWidth = 640;
GLOBAL int g_windowHeight = 480;

int main(int argc, char** argv) 
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);

	if (!window) 
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	bool full_screen = false;
	bool running = true;
	while (running)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window))
		{
			running = false;
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			running = false;
		}

		if (glfwGetKey(window, GLFW_KEY_F11))
		{
			full_screen = !full_screen;
			GLFWwindow* newWindow;

			if (full_screen)
				newWindow = glfwCreateWindow(1600, 900, "Dunjun", glfwGetPrimaryMonitor(), window);
			else
				newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, window);

			glfwDestroyWindow(window);
			window = newWindow;
			glfwMakeContextCurrent(window);
		}
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}