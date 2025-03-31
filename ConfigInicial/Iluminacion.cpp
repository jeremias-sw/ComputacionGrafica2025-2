/*
Sánchez Wilhelm Jeremias
314309064
Práctica 8
Fecha de entrega: 30 de marzo de 2025
*/


// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 1920, HEIGHT = 1080;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(22.5f, 16.5f, 2.5f);   // posición de la fuente de luz
float movelightPos = 0.0f;              // variable para manipular el movimiento de la fuente
GLfloat deltaTime = 0.0f;               // elementos para el intercambio
GLfloat lastFrame = 0.0f;               // después de cada frame
float rot = 0.0f;                       // variable para rotación
bool activanim = false;     

bool esLuna = false;  // variable para el cambio de iluminación

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Jeremias Sanchez. Materiales e Iluminacion", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model red_dog((char*)"Models/RedDog.obj");
    Model orange((char*)"Models/orange/source/fr_caraOrange/fr_caraOrange.obj");
    Model casa((char*)"Models/casa/lowpoly_land2.obj");
    Model moon((char*)"Models/moon/textures/moon_2.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    float vertices[] = {

        // Posición             // dirección del vector normal
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        lightingShader.Use();
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position"); // se cargan 
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");         // los shaders
        glUniform3f(lightPosLoc, lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos); // se define la posición 
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z); // matriz de la cámara

        // Con el booleano establecido previamente se definen los parámetros de la iluminación a usarse
        if (esLuna) {
            // Set lights properties (luz nocturna)
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.5f, 0.5f, 0.5f); 
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.4f, 0.4f, 0.8f);   // luz con altos niveles de azul
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.4f, 0.4f, 0.4f);
        }
        else {
            // Set lights properties (luz diurna)
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 807.3f, 807.3f, 807.3f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.9f, 0.8f, 0.6f);       // luz cálida
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.9f, 0.9f, 0.9f);
        }


        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.0f, 0.0f, 0.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.4f, 0.4f, 0.4f);    // propiedades
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.8f, 0.8f, 0.8f);    // relativamente
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.3f, 0.3f, 0.3f);   // neutrales
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 0.1f);              // para los objetos


        // Draw the loaded model
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        casa.Draw(lightingShader);         // se dibuja el escenario (casa con río)

        model = glm::translate(model, glm::vec3(3.0f, 4.75f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        red_dog.Draw(lightingShader);       // se dibuja el perrito en el escenario

        //glDrawArrays(GL_TRIANGLES, 0, 36);
        
       

        glBindVertexArray(0);


        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        if (esLuna) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos + movelightPos);
            model = glm::scale(model, glm::vec3(0.5f)); // escala pequeña
            glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            moon.Draw(lampshader);              // se dibuja el modelo de la luna (sin texturas)
            glBindVertexArray(0);
        }
        else {
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos + movelightPos);
            model = glm::scale(model, glm::vec3(1.0f)); // mayor escala en representación del sol
            glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            moon.Draw(lampshader);  // se dibuja el sol (sin texturas)
            glBindVertexArray(0);
        }

        
        

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }

    if (keys[GLFW_KEY_O]) // Mover el sol en su órbita
    {
        rot += 0.002f; // Incrementa el ángulo (ajustable para velocidad)
        if (rot > glm::pi<float>()) // Limita a media circunferencia
            rot = glm::pi<float>();
    }
    if (keys[GLFW_KEY_L]) // Retroceder el sol
    {
        rot -= 0.002f;
        if (rot < 0.0f)
            rot = 0.0f;
    }

    // Movimiento semicircular con radio 8.0f
    float radius = 21.0f;
    lightPos.x = radius * cos(rot) + 3.5f;
    lightPos.y = radius * sin(rot) + 3.5f; // Elevación inicial en y
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    /*if (keys[GLFW_KEY_O])
    {
       
        movelightPos += 0.1f;
    }

    if (keys[GLFW_KEY_L])
    {
        
        movelightPos -= 0.1f;
    }*/

    if (key == GLFW_KEY_N && action == GLFW_PRESS) {

        esLuna = !esLuna;
    }


}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


