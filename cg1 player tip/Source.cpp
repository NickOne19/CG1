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
		// �������        // ���������� ����������
		// ���� (������)
		-0.3f,  0.0f,     0.0f, 0.5f,  // ����� ������ ����� ���� (0)
		 0.3f,  0.0f,     1.0f, 0.5f,  // ������ ������ ����� ���� (1)
		 0.0f,  0.3f,     0.5f, 1.0f,  // ������� ����� ���� (2)

		 // ����� ������
		 -0.5f,  0.1f,     0.0f, 0.5f,  // ����� ������ ������ (3)
		 -0.4f,  0.3f,     0.0f, 1.0f,  // ����� ������� ������ (4)
		 -0.5f,  0.4f,     0.0f, 0.5f,  // ����� ����� ������ (5)

		 // ������ ������
		  0.5f,  0.1f,     1.0f, 0.5f,  // ������ ������ ������ (6)
		  0.4f,  0.3f,     1.0f, 1.0f,  // ������ ������� ������ (7)
		  0.5f,  0.4f,     1.0f, 0.5f,  // ����� ������ ������ (8)

		  // ����� �������� ����
		  -0.35f, -0.1f,    0.0f, 0.0f,  // ����� �������� ���������� ���� (9)
		  -0.5f, -0.3f,     0.0f, 0.0f,  // ����� �������� ����� ���� (10)

		  // ������ �������� ����
		   0.35f, -0.1f,    1.0f, 0.0f,  // ������ �������� ���������� ���� (11)
		   0.5f, -0.3f,     1.0f, 0.0f,  // ������ �������� ����� ���� (12)

		   // ����� ������ ����
		   -0.25f, -0.2f,    0.0f, 0.0f,  // ����� ������ ���������� ���� (13)
		   -0.4f, -0.5f,     0.0f, 0.0f,  // ����� ������ ����� ���� (14)

		   // ������ ������ ����
			0.25f, -0.2f,    1.0f, 0.0f,  // ������ ������ ���������� ���� (15)
			0.4f, -0.5f,     1.0f, 0.0f,  // ������ ������ ����� ���� (16)

			// �����
			-0.1f,  0.35f,    0.4f, 1.0f,  // ����� ���� (17)
			 0.1f,  0.35f,    0.6f, 1.0f,  // ������ ���� (18)
	};

	unsigned int indices[] = {
		// ����
		0, 1, 2,  // ����������� ����

		// ����� ������
		0, 3, 4,  // ��������� ����� ������
		4, 5, 3,  // ������� ����� ����� ������

		// ������ ������
		1, 6, 7,  // ��������� ������ ������
		7, 8, 6,  // ������� ����� ������ ������

		// ����
		0, 9, 10,  // ����� �������� ����
		1, 11, 12, // ������ �������� ����
		0, 13, 14, // ����� ������ ����
		1, 15, 16, // ������ ������ ����

		// �����
		2, 17, 18  // �����
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);         // �������
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));  // ���������� ����������
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
