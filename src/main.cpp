#include <Dunjun/Common.h>
#include <Dunjun/shaderProgram.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <cmath>


GLOBAL int g_windowWidth = 640;
GLOBAL int g_windowHeight = 480;

INTERNAL void glfwHints() 
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argc, char** argv) 
{
	//initialize all the settings and libs that we will use
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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//state the vertices of the triangle that we are going to draw 

	float vertices[] = {
	//    x      y     r     g     b
		+0.5f, +0.5f, 1.0f, 1.0f, 1.0f,  //Vertex 0
		-0.5f, +0.5f, 0.0f, 0.0f, 1.0f,  //Vertex 1
		+0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  //Vertex 2
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Vertex 3
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Dunjun::ShaderProgram shaderProgram;
	shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Vertex, "data/shaders/default.vert.glsl");
	shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Fragment, "data/shaders/default.frag.glsl");

	shaderProgram.bindAttributeLocation(0, "vertPosition");
	shaderProgram.bindAttributeLocation(1, "vertColor");
	shaderProgram.link();
	shaderProgram.use();

	bool full_screen = false;
	bool running = true;
	while (running)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw Things
		{
			float time = glfwGetTime();

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const GLvoid*)(2 * sizeof(float)));

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
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