#include <GL/glew.h>
#include<GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <soil.h>
#include <iostream>
#include "shader_s.h"
int main()
{
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(700, 500, "1 lab Zemlyanukhin", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	float vertices[] = {
		// Позиции        // Текстурные координаты
		// Тело (основа)
		-0.3f,  0.0f,     0.0f, 0.5f,  // Левая нижняя часть тела (0)
		 0.3f,  0.0f,     1.0f, 0.5f,  // Правая нижняя часть тела (1)
		 0.0f,  0.3f,     0.5f, 1.0f,  // Верхняя часть тела (2)

		 // Левая клешня
		 -0.5f,  0.1f,     0.0f, 0.5f,  // Левая нижняя клешня (3)
		 -0.4f,  0.3f,     0.0f, 1.0f,  // Левая верхняя клешня (4)
		 -0.5f,  0.4f,     0.0f, 0.5f,  // Конец левой клешни (5)

		 // Правая клешня
		  0.5f,  0.1f,     1.0f, 0.5f,  // Правая нижняя клешня (6)
		  0.4f,  0.3f,     1.0f, 1.0f,  // Правая верхняя клешня (7)
		  0.5f,  0.4f,     1.0f, 0.5f,  // Конец правой клешни (8)

		  // Левая передняя нога
		  -0.35f, -0.1f,    0.0f, 0.0f,  // Левое переднее соединение ноги (9)
		  -0.5f, -0.3f,     0.0f, 0.0f,  // Левый передний конец ноги (10)

		  // Правая передняя нога
		   0.35f, -0.1f,    1.0f, 0.0f,  // Правое переднее соединение ноги (11)
		   0.5f, -0.3f,     1.0f, 0.0f,  // Правый передний конец ноги (12)

		   // Левая задняя нога
		   -0.25f, -0.2f,    0.0f, 0.0f,  // Левое заднее соединение ноги (13)
		   -0.4f, -0.5f,     0.0f, 0.0f,  // Левый задний конец ноги (14)

		   // Правая задняя нога
			0.25f, -0.2f,    1.0f, 0.0f,  // Правое заднее соединение ноги (15)
			0.4f, -0.5f,     1.0f, 0.0f,  // Правый задний конец ноги (16)

			// Глаза
			-0.1f,  0.35f,    0.4f, 1.0f,  // Левый глаз (17)
			 0.1f,  0.35f,    0.6f, 1.0f,  // Правый глаз (18)
	};

	unsigned int indices[] = {
		// Тело
		0, 1, 2,  // Треугольник тела

		// Левая клешня
		0, 3, 4,  // Основание левой клешни
		4, 5, 3,  // Верхняя часть левой клешни

		// Правая клешня
		1, 6, 7,  // Основание правой клешни
		7, 8, 6,  // Верхняя часть правой клешни

		// Ноги
		0, 9, 10,  // Левая передняя нога
		1, 11, 12, // Правая передняя нога
		0, 13, 14, // Левая задняя нога
		1, 15, 16, // Правая задняя нога

		// Глаза
		2, 17, 18  // Глаза
	};




	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);         // Позиции
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));  // Текстурные координаты
	glEnableVertexAttribArray(1);
	//texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nChannels;
	unsigned char* data = SOIL_load_image("red1.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "texture error\n";
	}
	SOIL_free_image_data(data);
	Shader ourShader("vertexshader.vs", "fragmentshader.fs");
	while (!glfwWindowShouldClose(window)) {
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		ourShader.use();
		ourShader.setInt("texture", 0);
		glBindVertexArray(VAO);
		glEnable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}
	return 0;
}
