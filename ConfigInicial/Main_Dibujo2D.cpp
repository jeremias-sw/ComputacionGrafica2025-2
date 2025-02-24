// Sánchez Wilhelm Jeremias
// 314309064
// Fecha de entrega: 14 de febrero de 2025

// Práctica 2. Dibujo de Primitivas
// Computación Gráfica e Interración Humano-Computadora
// Grupo 6
// FI UNAM
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 1378, HEIGHT = 1378;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Práctica 2. Jeremias SW", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	float vertices[] = {
		// --------- Cuerpo ------------------------------
		// Cuerpo (triángulo central)
		0.0f,  -0.7f, -0.03f,  0.094f, 0.404f, 0.54f,       // 0
		-0.04f,  0.2f, -0.03f,  0.094f, 0.404f, 0.54f,		// 1
		 0.04f,  0.2f, -0.03f,  0.094f, 0.404f, 0.54f,		// 2
		 // Cuerpo (triángulo izquierdo)
		-0.001f,  -0.2f, -0.02f,  0.133f, 0.6f, 0.878f,     // 3
		-0.09f,  0.17f, -0.02f,  0.094f, 0.404f, 0.54f,		// 4
		 -0.001f,  0.2f, -0.02f,  0.133f, 0.6f, 0.878f,		// 5
		 // Cuerpo (triángulo derecho)
		0.001f,  -0.2f, -0.02f,  0.133f, 0.6f, 0.878f,      // 6
		0.09f,  0.17f, -0.02f,  0.094f, 0.404f, 0.54f,		// 7
		 0.001f,  0.2f, -0.02f,  0.133f, 0.6f, 0.878f,		// 8

		 // -------- Cabeza ------------------------------
		 // Cabeza (triángulo superior)
		 -0.08f, 0.3f, 0.0f,  0.0f, 0.643f, 0.922f,			// 9
		  0.077f, 0.3f, 0.0f,  0.0f, 0.643f, 0.922f,		// 10
		  -0.04f,  0.203f, 0.0f,  0.0f, 0.643f, 0.922f,		// 11
		  // Cabeza (triángulo inferior)
		  0.08f, 0.3f, 0.0f,  0.0f, 0.643f, 0.922f,			// 12
		  0.037f, 0.2f, 0.0f,  0.0f, 0.643f, 0.922f,		// 13
		  -0.04f,  0.2f, 0.0f,  0.0f, 0.643f, 0.922f,		// 14
		  // Cabeza (triángulo en punta 1. Mandíbula izquierda)
		 -0.077f, 0.302f, 0.0f,  0.0f, 0.643f, 0.922f,			// 15
		  -0.002f, 0.302f, 0.0f,  0.0f, 0.643f, 0.922f,		// 16
		  -0.002f, 0.322f, 0.0f, 0.0f, 0.643f, 0.922f,			// 17
		  // Cabeza (triángulo en punta 2. Mandíbula derecha)
		 0.077f, 0.302f, 0.0f,  0.0f, 0.643f, 0.922f,			// 18
		  0.002f, 0.302f, 0.0f,  0.0f, 0.643f, 0.922f,		// 19
		  0.002f, 0.322f, 0.0f, 0.0f, 0.643f, 0.922f,			// 20

		  //Ojo izquierdo
		   -0.082f, 0.297f, 0.0f,  0.0f, 0.878f, 0.827f,	// 21
		   -0.09f, 0.26f, 0.0f,  0.0f, 0.71f, 0.667f,		// 22
		   -0.042f,  0.2f, 0.0f,  0.0f, 0.878f, 0.827f,		// 23
		   //Ojo derecho
			0.082f, 0.297f, 0.0f,  0.0f, 0.878f, 0.827f,	// 23
			0.09f, 0.26f, 0.0f,  0.0f, 0.71f, 0.667f,		// 24
			0.04f,  0.2f, 0.0f,  0.0f, 0.878f, 0.827f,		// 25

			// -------- Alas -------------------------------
			//Ala inferior izquierda (sombra)
		  -0.7f,  0.0f, -0.01f,  0.047f, 0.255f, 0.322f,	// 26
		   -0.089f,  -0.1f, -0.01f,  0.047f, 0.255f, 0.322f,// 27
		  -0.015f,  0.1f, -0.01f,  0.047f, 0.255f, 0.322f,	// 28
		  //Ala inferior derecha (sombra)
		   0.7f,  0.0f, -0.01f,  0.047f, 0.255f, 0.322f,	// 29
		   0.089f,  -0.1f, -0.01f,  0.047f, 0.255f, 0.322f,	// 30
		   0.015f,  0.1f, -0.01f,  0.047f, 0.255f, 0.322f,	// 31
		  //Ala inferior izquierda
		  -0.7f,  0.0f, -0.01f,  0.016f, 0.51f, 0.541f,		// 32
		   -0.1f,  -0.1f, -0.01f,  0.016f, 0.808f, 0.859f,	// 33
		  -0.015f,  0.1f, -0.01f,  0.016f, 0.51f, 0.541f,	// 34
		  //Ala inferior derecha
		   0.7f,  0.0f, -0.01f,  0.016f, 0.51f, 0.541f,		// 35
		   0.1f,  -0.1f, -0.01f,  0.016f, 0.808f, 0.859f,	// 36
		   0.015f,  0.1f, -0.01f,  0.016f, 0.51f, 0.541f,	// 37
		   //Ala superior izquierda (sombra)
		  -0.7f,  0.3f, 0.0f,  0.059f, 0.329f, 0.412f,		// 38
		   -0.03f, 0.18f, 0.0f, 0.059f, 0.329f, 0.412f,		// 39
		  -0.2f,  -0.007f, 0.0f,  0.059f, 0.329f, 0.412f,	// 40
		  //Ala superior derecha (sombra)
		   0.7f,  0.3f, 0.0f,  0.059f, 0.329f, 0.412f,		// 41
		   0.03f,  0.18f, 0.0f,  0.059f, 0.329f, 0.412f,	// 42
		   0.2f, - 0.007f, 0.0f,  0.059f, 0.329f, 0.412f,	// 43
		  //Ala superior izquierda
		  -0.7f,  0.3f, 0.0f,  0.012f, 0.824f, 0.89f,		// 44
		   -0.03f,  0.18f, 0.0f,  0.012f, 0.824f, 0.89f,	// 45
		  -0.2f,  0.0f, 0.0f,  0.012f, 0.667f, 0.729f,		// 46
		  //Ala superior derecha
		   0.7f,  0.3f, 0.0f,  0.012f, 0.824f, 0.89f,		// 47
		   0.03f,  0.18f, 0.0f,  0.012f, 0.824f, 0.89f,		// 48
		   0.2f,  0.0f, 0.0f,  0.012f, 0.667f, 0.729f,		// 49
		   

		   



		   
	};

	unsigned int indices[] = {
		0, 1, 2,	// Cuerpo
		3, 4, 5,	// Cuerpo p2
		6, 7, 8,	// cuerpo p3
		9, 10, 11,  // cabeza p1
		12, 13, 14, // cabeza p2
		15, 16, 17, // cabeza (mandíbula izquierda)
		18, 19, 20, // cabeza (mandíbula derecha)
		21, 22, 23, // Ojo Izquierdo
		24, 25, 26, // Ojo derecho
		27, 28, 29, // Ala inferior izquierda (sombra)
		30, 31, 32, // Ala inferior derecha (sombra)
		33, 34, 35, // Ala inferior izquierda
		36, 37, 38, // Ala inferior derecha
		39, 40, 41, // Ala superior izquierda (sombra)
		42, 43, 44, // Ala superior derecha (sombra)
		45, 46, 47, // Ala superior izquierda
		48, 49, 50, // Ala superior derecha
		 
		
	};
	// Set up vertex data (and buffer(s)) and attribute pointers
	/*float vertices[] = {
		0.5f,  0.5f, 0.0f,    0.0f,1.0f,0.5f,  // top right  (x,y,z)    (r, g, b)
		0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right (x,y,z)    (r, g, b)
		-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left (x,y,z)    (r, g, b)
		-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left   (x,y,z)    (r, g, b)
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};*/



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        //ourShader.Use();
        //glBindVertexArray(VAO);


        /*glPointSize(30);
        //glDrawArrays(GL_POINTS,0,2);
		//glDrawArrays(GL_LINES, 0, 4);
        
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
		//glDrawArrays(GL_TRIANGLES, 1, 4);
        glDrawElements(GL_LINE_LOOP, 4,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 51, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}