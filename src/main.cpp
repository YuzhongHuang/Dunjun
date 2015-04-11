#include <Dunjun/Common.h>
#include <gl\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLOBAL int g_windowWidth = 640;
GLOBAL int g_windowHeight = 480;

void glfwHints() 
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argc, char** argv) 
{
	if (!glewInit())
	{
		return EXIT_FAILURE;
	}

	GLFWwindow* window;

	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	glfwHints();
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);

	if (!window) 
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	float vertices[] = {
		+0.0f, +0.5f,
		-0.5f, -0.5f,
		+0.5f, -0.5f,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char* vertexShaderText = {
		"#version 120\n"
		"\n"
		"attribute vec2 position;"
		"void main()"
		"{"
		"   gl_Position = vec4(position, 0.0, 1.0);"
		"}"
	};

	const char* fragmentShaderText = {
		"#version 120\n"
		"\n"
		"void main()"
		"{"
		"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
		"}"
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "position");

	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	bool full_screen = false;
	bool running = true;
	while (running)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw Things
		{
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
		}

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

			int count;
			const GLFWvidmode* mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

			std::cout << mode[count - 1].width << std::endl;

			if (full_screen)
			{
				newWindow = glfwCreateWindow(1600, 900, "Dunjun", glfwGetPrimaryMonitor(), window);
			}
			else
			{
				newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, window);
			}

			glfwDestroyWindow(window);
			window = newWindow;
			glfwMakeContextCurrent(window);
		}
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}