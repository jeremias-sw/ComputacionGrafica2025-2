/*
Práctica 4
Jeremias Sánchez
25 de febrero de 2025
314309064
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1920, HEIGHT = 1080;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4: Modelado geometrico. Jeremias Sanchez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {

		// ------------------------------------------------------------------------
		// Vertices cubo verde (cabeza, cuerpo, brazos, piernas) (0, 36)

		-0.5f, -0.5f, 0.5f, 0.408f, 0.82f,0.243f,	// 0
		0.5f, -0.5f, 0.5f,  0.408f, 0.82f,0.243f,	// 1
		0.5f,  0.5f, 0.5f,  0.408f, 0.82f,0.243f,	// 2
		0.5f,  0.5f, 0.5f,  0.408f, 0.82f,0.243f,	// 3
		-0.5f,  0.5f, 0.5f, 0.408f, 0.82f,0.243f,	// 4
		-0.5f, -0.5f, 0.5f, 0.408f, 0.82f,0.243f,	// 5

		-0.5f, -0.5f,-0.5f, 0.408f, 0.82f,0.243f,	// 6
		 0.5f, -0.5f,-0.5f, 0.408f, 0.82f,0.243f,	// 7
		 0.5f,  0.5f,-0.5f, 0.408f, 0.82f,0.243f,	// 8
		 0.5f,  0.5f,-0.5f, 0.408f, 0.82f,0.243f,	// 9
		-0.5f,  0.5f,-0.5f, 0.408f, 0.82f,0.243f,	// 10
		-0.5f, -0.5f,-0.5f, 0.408f, 0.82f,0.243f,	// 11

		 0.5f, -0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 12
		 0.5f, -0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 13
		 0.5f,  0.5f, -0.5f, 0.408f, 0.82f,0.243f,	// 14
		 0.5f,  0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 15
		 0.5f,  0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 16
		 0.5f,  -0.5f, 0.5f, 0.408f, 0.82f,0.243f,	// 17

		-0.5f,  0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 18
		-0.5f,  0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 19
		-0.5f, -0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 20
		-0.5f, -0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 21
		-0.5f, -0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 22
		-0.5f,  0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 23

		-0.5f, -0.5f, -0.5f, 0.408f, 0.82f,0.243f,	// 24
		0.5f, -0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 25
		0.5f, -0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 26
		0.5f, -0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 27
		-0.5f, -0.5f,  0.5f, 0.408f, 0.82f,0.243f,	// 28
		-0.5f, -0.5f, -0.5f, 0.408f, 0.82f,0.243f,	// 29

		-0.5f,  0.5f, -0.5f, 0.408f, 0.82f,0.243f,	// 30
		0.5f,  0.5f, -0.5f,  0.408f, 0.82f,0.243f,	// 31
		0.5f,  0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 32
		0.5f,  0.5f,  0.5f,  0.408f, 0.82f,0.243f,	// 33
		-0.5f,  0.5f,  0.5f, 0.408f, 0.82f,0.243f,	// 34
		-0.5f,  0.5f, -0.5f, 0.408f, 0.82f,0.243f,	// 35

		// ------------------------------------------------------------------------
		// Vertices cubo rojo (lengua, espalda, cresta) (36, 73)

		-0.5f, -0.5f, 0.5f, 0.894f, 0.408f,0.345f,	// 36
		0.5f, -0.5f, 0.5f,  0.894f, 0.408f,0.345f,	// 37
		0.5f,  0.5f, 0.5f,  0.894f, 0.408f,0.345f,	// 38
		0.5f,  0.5f, 0.5f,  0.894f, 0.408f,0.345f,	// 39
		-0.5f,  0.5f, 0.5f, 0.894f, 0.408f,0.345f,	// 40
		-0.5f, -0.5f, 0.5f, 0.894f, 0.408f,0.345f,	// 41

		-0.5f, -0.5f,-0.5f, 0.894f, 0.408f,0.345f,	// 42
		 0.5f, -0.5f,-0.5f, 0.894f, 0.408f,0.345f,	// 43
		 0.5f,  0.5f,-0.5f, 0.894f, 0.408f,0.345f,	// 44
		 0.5f,  0.5f,-0.5f, 0.894f, 0.408f,0.345f,	// 45
		-0.5f,  0.5f,-0.5f, 0.894f, 0.408f,0.345f,	// 46
		-0.5f, -0.5f,-0.5f, 0.894f, 0.408f,0.345f,	// 47

		 0.5f, -0.5f,  0.5f,  0.894f, 0.408f,0.345f,	// 48
		 0.5f, -0.5f, -0.5f,  0.894f, 0.408f,0.345f,	// 49
		 0.5f,  0.5f, -0.5f,  0.894f, 0.408f,0.345f,	// 50
		 0.5f,  0.5f, -0.5f,  0.894f, 0.408f,0.345f,	// 51
		 0.5f,  0.5f,  0.5f,  0.894f, 0.408f,0.345f,	// 52
		 0.5f,  -0.5f, 0.5f, 0.894f, 0.408f,0.345f,		// 53

		-0.5f,  0.5f,  0.5f,  0.894f, 0.408f,0.345f,	// 54
		-0.5f,  0.5f, -0.5f,  0.894f, 0.408f,0.345f,	// 55
		-0.5f, -0.5f, -0.5f,  0.894f, 0.408f,0.345f,	// 56
		-0.5f, -0.5f, -0.5f,  0.894f, 0.408f,0.345f,	// 57
		-0.5f, -0.5f,  0.5f,  0.894f, 0.408f,0.345f,	// 59
		-0.5f,  0.5f,  0.5f,  0.894f, 0.408f,0.345f,	// 60

		-0.5f, -0.5f, -0.5f, 0.894f, 0.408f,0.345f,		// 61
		0.5f, -0.5f, -0.5f,  0.894f, 0.408f,0.345f,		// 62
		0.5f, -0.5f,  0.5f,  0.894f, 0.408f,0.345f,		// 63
		0.5f, -0.5f,  0.5f,  0.894f, 0.408f,0.345f,		// 64
		-0.5f, -0.5f,  0.5f, 0.894f, 0.408f,0.345f,		// 65
		-0.5f, -0.5f, -0.5f, 0.894f, 0.408f,0.345f,		// 66

		-0.5f,  0.5f, -0.5f, 0.894f, 0.408f,0.345f,		// 67
		0.5f,  0.5f, -0.5f,  0.894f, 0.408f,0.345f,		// 68
		0.5f,  0.5f,  0.5f,  0.894f, 0.408f,0.345f,		// 69
		0.5f,  0.5f,  0.5f,  0.894f, 0.408f,0.345f,		// 70
		-0.5f,  0.5f,  0.5f, 0.894f, 0.408f,0.345f,		// 71
		-0.5f,  0.5f, -0.5f, 0.894f, 0.408f,0.345f,		// 72

		// ------------------------------------------------------------------------
		// Vertices cubo blanco (boca, caparazón, cola inferior) (73, 109)

		-0.5f, -0.5f, 0.5f, 0.937f, 0.929f,0.933f,	// 73
		0.5f, -0.5f, 0.5f,  0.937f, 0.929f,0.933f,	// 74
		0.5f,  0.5f, 0.5f,  0.937f, 0.929f,0.933f,	// 75
		0.5f,  0.5f, 0.5f,  0.937f, 0.929f,0.933f,	// 76
		-0.5f,  0.5f, 0.5f, 0.937f, 0.929f,0.933f,	// 77
		-0.5f, -0.5f, 0.5f, 0.937f, 0.929f,0.933f,	// 78

		-0.5f, -0.5f,-0.5f, 0.937f, 0.929f, 0.933f,	// 79
		 0.5f, -0.5f,-0.5f, 0.937f, 0.929f, 0.933f,	// 80
		 0.5f,  0.5f,-0.5f, 0.937f, 0.929f, 0.933f,	// 81
		 0.5f,  0.5f,-0.5f, 0.937f, 0.929f, 0.933f,	// 82
		-0.5f,  0.5f,-0.5f, 0.937f, 0.929f, 0.933f,	// 83
		-0.5f, -0.5f,-0.5f, 0.937f, 0.929f, 0.933f,	// 84

		 0.5f, -0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 85
		 0.5f, -0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 86
		 0.5f,  0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 87
		 0.5f,  0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 88
		 0.5f,  0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 89
		 0.5f,  -0.5f, 0.5f, 0.937f, 0.929f, 0.933f,	// 90

		-0.5f,  0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 91
		-0.5f,  0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 92
		-0.5f, -0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 93
		-0.5f, -0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 94
		-0.5f, -0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 95
		-0.5f,  0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 96

		-0.5f, -0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 97
		0.5f, -0.5f, -0.5f,  0.937f, 0.929f, 0.933f,	// 98
		0.5f, -0.5f,  0.5f,  0.937f, 0.929f, 0.933f,	// 99
		0.5f, -0.5f,  0.5f,  0.937f, 0.929f, 0.933f,	// 100
		-0.5f, -0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 101
		-0.5f, -0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 102

		-0.5f,  0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 103
		0.5f,  0.5f, -0.5f,  0.937f, 0.929f, 0.933f,	// 104
		0.5f,  0.5f,  0.5f,  0.937f, 0.929f, 0.933f,	// 105
		0.5f,  0.5f,  0.5f,  0.937f, 0.929f, 0.933f,	// 106
		-0.5f,  0.5f,  0.5f, 0.937f, 0.929f, 0.933f,	// 107
		-0.5f,  0.5f, -0.5f, 0.937f, 0.929f, 0.933f,	// 108

		// ------------------------------------------------------------------------
		// Vertices cubo azul (ojos) (109, 145)

			-0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f,// 109
			0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f, // 110
			0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,	 // 111
			0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,	 // 112
			-0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f, // 113
			-0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f, // 114

			-0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f,// 115
			0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 116
			0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f,  // 117
			0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f,  // 118
			-0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 119
			-0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f,// 120

			0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f,  // 121
			0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 122
			0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f,  // 123
			0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f,  // 124
			0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,	  // 125
			0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f,  // 126

			-0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,   // 127
			-0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f,  // 128
			-0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 129
			-0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 130
			-0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f, // 131
			-0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,  // 132

			-0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f,// 133
			0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 134
			0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f,  // 135
			0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f,  // 136
			-0.5f, -0.5f, 0.5f, 0.243f, 0.322f, 0.671f, // 137
			-0.5f, -0.5f, -0.5f, 0.243f, 0.322f, 0.671f,// 138

			-0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 139
			0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f,  // 140
			0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,   // 141
			0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,	  // 142
			-0.5f, 0.5f, 0.5f, 0.243f, 0.322f, 0.671f,  // 143
			-0.5f, 0.5f, -0.5f, 0.243f, 0.322f, 0.671f, // 144

			// ------------------------------------------------------------------------
		// Vertices cubo cafe (zapatos) (145, 181)

			-0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f, // 145
			0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 146
			0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,   // 147
			0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,	  // 148
			-0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 149
			-0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f, // 150

			-0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f,// 151
			0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 152
			0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f,  // 153
			0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f,  // 154
			-0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 155
			-0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f,// 156

			0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 157
			0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 158
			0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f,  // 159
			0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f,  // 160
			0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,   // 161
			0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 162

			-0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 163
			-0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 164
			-0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f,// 165
			-0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f,// 166
			-0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f, // 167
			-0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 168

			-0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f,// 169
			0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 170
			0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 171
			0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 172
			-0.5f, -0.5f, 0.5f, 0.471f, 0.255f, 0.09f, // 173
			-0.5f, -0.5f, -0.5f, 0.471f, 0.255f, 0.09f,// 174

			-0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 175
			0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f,  // 176
			0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,	  // 177
			0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,   // 178
			-0.5f, 0.5f, 0.5f, 0.471f, 0.255f, 0.09f,  // 179
			-0.5f, 0.5f, -0.5f, 0.471f, 0.255f, 0.09f, // 180
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
	
		// ==========================================================================================
		// ============================= DIBUJO DE LA FIGURA ========================================
		// ==========================================================================================


		// ================================================================
		// ------------ CABEZA --------------------------------------------
		// ================================================================
		// 1. cabeza (rectángulo verde)
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.32f, 0.83f, 0.42f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.38f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// -----------------------------------------
		// 2. nariz (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.42f, 0.43f, 0.45f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.13f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// -----------------------------------------
		// 3. hocico (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.55f, 0.35f, 0.3f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.5f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// -----------------------------------------
		// 4. cachetes (cubo blanco) 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.42f, 0.45f, 0.60f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.3f, 0.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// -----------------------------------------
		// 5. boca 1 (cubo blanco) 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.08f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.72f, 0.55f, 1.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 6. boca 2 (cubo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.08f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.72f, 0.55f, -1.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 7. boca 3 (rectangulo inferior blanco) 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.02f, 0.3f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.7f, 0.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// -----------------------------------------
		// 8. ojo 1 (cubo azul)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.08f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.46f, 2.85f, 1.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 145);
		// 9. ojo 1 (cubo azul)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.08f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.46f, 2.85f, -1.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 145);
		// -----------------------------------------
		// 10. lengua (cubo rojo) 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.09f, 0.09f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.0f, 1.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		// 11. punta de lengua (cubo rojo) 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-10.0f, 0.9f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		// -----------------------------------------
		// 12. cresta 1 (cubo rojo) 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.12f, 0.18f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.5f,4.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		// 13. cresta 2 (cubo rojo)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.12f, 0.18f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.5f, 2.6f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		// ----------------------------------------------------------------
		// -------------- fin cabeza --------------------------------------
		//=================================================================


		// ================================================================
		// ------------ CUERPO --------------------------------------------
		// ================================================================
		// 14. cuerpo (rectángulo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.87f, 0.5f, 0.38f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.45f, -0.4f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 15. cuerpo (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.83f, 0.5f, 0.42f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.5f, -0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// ---------------------------------------------------------
		// 16. cuello (rectángulo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.36f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 17. cuello (rectángulo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.36f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.3f, -0.4f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// ---------------------------------------------------------
		// 18. concha (rectángulo blAnco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.48f, 0.1f, 0.46f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.17f, 1.4f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 19. concha 2 (rectángulo rojo)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.37f, 0.1f, 0.37f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.55f, 2.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		// 20. concha 3 (rectangulo rojo)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.3f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.87f, 2.8f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		// ----------------------------------------------------------------
		// -------------- fin cuerpo --------------------------------------
		//=================================================================


		// ================================================================
		// ------------ PIERNAS --------------------------------------------
		// ================================================================
		// 21. cuerpo/muslos (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.48f, 0.38f, 0.65f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.2f, -0.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 22. pierna 1  izquierda (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.38f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.4f, -1.2f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 23. pierna 2 derecha (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.38f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.4f, -1.2f, -1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// ---------------------------------------------------
		// 24. base zapato 1 (rectángulo café)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.24f, 0.2f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.0f, -2.65f, -1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 181);
		// 25. base zapato 2 (rectángulo café)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.24f, 0.2f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.0f, -2.65f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 181);
		// 26. punta zapato 1 (rectángulo café)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.14f, 0.2f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.0f, -4.88f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 181);
		// 27. punta zapato 2 (rectángulo café)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.14f, 0.2f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.0f, -4.88f, -1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 181);
		// ----------------------------------------------------------------
		// -------------- fin piernas -------------------------------------
		//=================================================================


		// ================================================================
		// ------------ BRAZOS --------------------------------------------
		// ================================================================
		// 28. brazo 1 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.38f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.6f, -0.9f, 1.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 29. brazo 2 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.38f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.6f, -0.9f, -1.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 30. antebrazo 1 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.26f, 0.15f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.12f, -3.4f, 1.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 31. antebrazo 2 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.26f, 0.15f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.12f, -3.4f, -1.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 32. mano 1 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.12f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.17f, -5.0f, 1.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 33. mano 2 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.12f, 0.13f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.17f, -5.0f, -1.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// ----------------------------------------------------------------
		// -------------- fin brazos --------------------------------------
		//=================================================================


		// ================================================================
		// ------------ COLA --------------------------------------------
		// ================================================================
		// 34. cola 1 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.26f, 0.48f, 0.33f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(3.4f, -0.23f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 35. cola 1 (rectángulo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.26f, 0.48f, 0.28f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(3.6f, -0.35f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 36. cola 2 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.46f, 0.36f, 0.3f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.7f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 37 cola 2 (rectángulo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.46f, 0.36f, 0.25f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.8f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 38. cola 3 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.46f, 0.25f, 0.26f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(3.22f, 0.6f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 39. cola 3 (rectángulo blanco)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.46f, 0.25f, 0.21f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(3.3f, 0.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);
		// 40. cola 4 (rectángulo verde)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.215f));				// Ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(5.8f, 1.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// ----------------------------------------------------------------
		// -------------- fin cola ----------------------------------------
		//=================================================================
		

		
		// Dibuja todos los elementos
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 // --------------------------------------------------------------
 // ---------- Sección del control de la vista -------------------
 // --------------------------------------------------------------
 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.004f;
	 if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
 }


