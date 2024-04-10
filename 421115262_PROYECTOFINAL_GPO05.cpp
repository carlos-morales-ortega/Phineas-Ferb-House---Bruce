#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 4.0f, 10.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 positionSpot(5.0f, 2.5f, -5.0f);
glm::vec3 directionSpot(5.0f, -10.0f, -5.0f);
bool active;
bool animarP1 = false;
bool animarP2 = false;
bool animarP3 = false;

//Variables auxiliares
float	rotarP1 = 0.0f;
bool	flagP1 = false;
bool	teclaP1 = false;

float	rotarP2 = 0.0f;
bool	flagP2 = false;
bool	teclaP2 = false;

float	rotarP3 = 0.0f;
bool	flagP3 = false;
bool	teclaP3 = false;

bool	activeT = true;
bool	flag = true;
bool	flag2 = true;
bool	flag3 = true;
float	rotarT = 0.0f;
double	aux1 = 0.0f;
double	aux2 = 0.0f;
int	num = 5.0f;
int conteo = 0.0f;

float	rotarG = 0.0f;
bool	activeG = true;

float tiempo;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,0.0, 0.0),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(8.0f,0.0f,  0.0f),
	glm::vec3(8.0f,0.0f, 0.0f)
};




glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final - 421115262", nullptr, nullptr);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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



	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader agua("Shaders/agua.vs", "Shaders/agua.frag");
	Shader bola("Shaders/bola.vs", "Shaders/bola.frag");


	Model fachada((char*)"ModelsProyecto/fachada.obj");
	Model puerta1((char*)"ModelsProyecto/puertaPrincipal.obj");
	Model puerta2((char*)"ModelsProyecto/puertaCuarto.obj");
	Model pasto((char*)"ModelsProyecto/pasto.obj");
	Model ventana((char*)"ModelsProyecto/ventana.obj");

	Model ducky((char*)"ModelsProyecto/duckymomo.obj");
	Model cabina((char*)"ModelsProyecto/CabinaPF.obj");
	Model cabinaC1((char*)"ModelsProyecto/CabinaPFCristal.obj");
	Model cabinaC2((char*)"ModelsProyecto/CabinaPFCristal2.obj");
	Model cabinaC3((char*)"ModelsProyecto/CabinaPFCristal3.obj");
	Model cabinaP((char*)"ModelsProyecto/CabinaPFPuerta.obj");
	Model cabeza((char*)"ModelsProyecto/cabeza.obj");
	Model gnomo((char*)"ModelsProyecto/Gnome.obj");
	Model buroP((char*)"ModelsProyecto/buroP.obj");
	Model buroF((char*)"ModelsProyecto/buroF.obj");
	Model piso((char*)"ModelsProyecto/piso.obj");
	Model camaP((char*)"ModelsProyecto/camaP.obj");
	Model camaF((char*)"ModelsProyecto/camaF.obj");
	Model pecera((char*)"ModelsProyecto/pecera.obj");
	Model cristalP1((char*)"ModelsProyecto/cristalPC1.obj");
	Model cristalP2((char*)"ModelsProyecto/cristalPC2.obj");
	Model cristalP3((char*)"ModelsProyecto/cristalPC3.obj");
	Model cristalP4((char*)"ModelsProyecto/cristalPC4.obj");
	Model aguaP((char*)"ModelsProyecto/aguaPecera.obj");
	Model globoS((char*)"ModelsProyecto/soporteGlobo.obj");
	Model globo((char*)"ModelsProyecto/globo.obj");
	Model tel((char*)"ModelsProyecto/telefono.obj");
	Model lampa((char*)"ModelsProyecto/lamp.obj");
	Model lampBola((char*)"ModelsProyecto/bolaLamp.obj");

	Model camaCandace((char*)"ModelsProyecto/camaCandace.obj");
	Model buroCandace((char*)"ModelsProyecto/buroCandace.obj");
	Model espejoCandace((char*)"ModelsProyecto/espejoCandace.obj");
	Model tocadorCandace((char*)"ModelsProyecto/tocadorCandace.obj");
	Model perry((char*)"ModelsProyecto/perry.obj");

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f); //especular blanco
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



		// Point light 2
		glm::vec3 lightColor2;
		lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		lightColor2.z = sin(glfwGetTime() * Light2.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.075f);

		// Point light 3
		glm::vec3 lightColor3;
		lightColor3.x = abs(sin(glfwGetTime() * Light3.x));
		lightColor3.y = abs(sin(glfwGetTime() * Light3.y));
		lightColor3.z = sin(glfwGetTime() * Light3.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

		// Point light 4
		glm::vec3 lightColor4;
		lightColor4.x = abs(sin(glfwGetTime() * Light4.x));
		lightColor4.y = abs(sin(glfwGetTime() * Light4.y));
		lightColor4.z = sin(glfwGetTime() * Light4.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0, 0.0f, 0.0);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.075f);


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);



		//Carga de modelo 
		view = camera.GetViewMatrix();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);





		//Fachada Phineas & Ferb
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fachada.Draw(lightingShader);
		glBindVertexArray(0);

		//Fachada Phineas & Ferb
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pasto.Draw(lightingShader);
		glBindVertexArray(0);

		//puerta Casa Phineas & Ferb
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-5.432f, 0.824f, 3.795f));
		model = glm::rotate(model, glm::radians(rotarP1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puerta1.Draw(lightingShader);
		glBindVertexArray(0);

		//puerta Cuarto Phineas & Ferb
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-3.921f, 0.824f, 1.786f));
		model = glm::rotate(model, glm::radians(rotarP2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puerta2.Draw(lightingShader);
		glBindVertexArray(0);

		//Ventana
		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.30f); //Para activar la transparencia
		ventana.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		//Cabina telefónica
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -.027f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cabina.Draw(lightingShader);
		glBindVertexArray(0);

		//Teléfono
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.231f, 0.981f, 0.695f));
		model = glm::rotate(model, glm::radians(rotarT), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		tel.Draw(lightingShader);
		glBindVertexArray(0);

		//Cabina telefónica cristal 1
		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.30f); //Para activar la transparencia
		cabinaC1.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		//Cabina telefónica cristal 2
		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.30f); //Para activar la transparencia
		cabinaC2.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		//Cabina telefónica cristal 3
		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.582f, .82f, .869f));
		model = glm::rotate(model, glm::radians(rotarP3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.30f); //Para activar la transparencia
		cabinaC3.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		//Cabina telefónica puerta
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.582f, 0.819f, 0.863f));
		model = glm::rotate(model, glm::radians(rotarP3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cabinaP.Draw(lightingShader);
		glBindVertexArray(0);

		//DuckyMomo
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ducky.Draw(lightingShader);
		glBindVertexArray(0);

		//Cabeza Moai
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cabeza.Draw(lightingShader);
		glBindVertexArray(0);

		//Gnomo
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		gnomo.Draw(lightingShader);
		glBindVertexArray(0);

		//Buro P
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		buroP.Draw(lightingShader);
		glBindVertexArray(0);

		//Buro F
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		buroF.Draw(lightingShader);
		glBindVertexArray(0);

		//Cama P
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		camaP.Draw(lightingShader);
		glBindVertexArray(0);

		//Pecera
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pecera.Draw(lightingShader);
		glBindVertexArray(0);

		//Cristales Pecera
		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.75f); //Para activar la transparencia
		cristalP1.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.75f); //Para activar la transparencia
		cristalP2.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.75f); //Para activar la transparencia
		cristalP3.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);

		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 0.75f); //Para activar la transparencia
		cristalP4.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0, 1.0f); //Para desactivar la transparencia
		glBindVertexArray(0);


		//Pecera
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globoS.Draw(lightingShader);
		glBindVertexArray(0);

		//Globo terraqueo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.709f, 0.608f, -.409f));
		model = glm::rotate(model, glm::radians(25.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotarG), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globo.Draw(lightingShader);
		glBindVertexArray(0);

		//Cama Ferb
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		camaF.Draw(lightingShader);
		glBindVertexArray(0);

		//Lampara Ferb
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lampa.Draw(lightingShader);
		glBindVertexArray(0);


		//Cama Candace
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		camaCandace.Draw(lightingShader);
		glBindVertexArray(0);

		//buro Candace
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		buroCandace.Draw(lightingShader);
		glBindVertexArray(0);

		//espejo Candace
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		espejoCandace.Draw(lightingShader);
		glBindVertexArray(0);

		//tocador
		//  Candace
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		tocadorCandace.Draw(lightingShader);
		glBindVertexArray(0);

		//Perry
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		perry.Draw(lightingShader);
		glBindVertexArray(0);

		agua.Use();
		tiempo = glfwGetTime() * .8f;
		glBindVertexArray(0);
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(agua.Program, "model");
		viewLoc = glGetUniformLocation(agua.Program, "view");
		projLoc = glGetUniformLocation(agua.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(agua.Program, "time"), tiempo);
		aguaP.Draw(agua);

		bola.Use();
		tiempo = glfwGetTime() * .8f;
		glBindVertexArray(0);
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(bola.Program, "model");
		viewLoc = glGetUniformLocation(bola.Program, "view");
		projLoc = glGetUniformLocation(bola.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(bola.Program, "time"), tiempo);
		lampBola.Draw(bola);
		glBindVertexArray(0);







		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
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

	//Abre
	if (animarP1) {
		if (rotarP1 <= 80.0f) {
			rotarP1 += 0.3f;
		}
		else {
			animarP1 = false; //Para la animación de abrir
			teclaP1 = true; //Activa para permitir la tecla de espacio
		}
	}
	//Cierra
	if (flagP1) {
		if (rotarP1 >= 0.0f) {
			rotarP1 -= 0.3f;
		}
		else {
			flagP1 = false; //Para la animacion que cierra
			teclaP1 = false; //Desactiva para permitir espacio para abrir
		}
	}

	//Abre
	if (animarP2) {
		if (rotarP2 <= 0.0f) {
			rotarP2 += 0.3f;
		}
		else {
			animarP2 = false; //Para la animación de abrir
			teclaP2 = true; //Activa para permitir la tecla de espacio
		}
	}
	//Cierra
	if (flagP2) {
		if (rotarP2 >= -94.0f) {
			rotarP2 -= 0.3f;
		}
		else {
			flagP2 = false; //Para la animacion que cierra
			teclaP2 = false; //Desactiva para permitir espacio para abrir
		}
	}


	//Abre
	if (animarP3) {
		if (rotarP3 <= 90.0f) {
			rotarP3 += 0.4f;
		}
		else {
			animarP3 = false; //Para la animación de abrir
			teclaP3 = true; //Activa para permitir la tecla de espacio
		}
	}
	//Cierra
	if (flagP3) {
		if (rotarP3 >= 0.0f) {
			rotarP3 -= 0.4f;
		}
		else {
			flagP3 = false; //Para la animacion que cierra
			teclaP3 = false; //Desactiva para permitir espacio para abrir
		}
	}

	if (activeG) {
		if (rotarG <= 360.0f) {
			rotarG += 0.4f;
		}
		else {
			rotarG = 0;
		}
	}

	if (activeT) {
		aux1 = glfwGetTime();

		if ((int(aux1) % num) == 0 and (conteo % 2) == 0) {
			flag2 = true;
			conteo++;
		}
		else if ((int(aux1) % num) == 0) {
			flag2 = false;
			rotarT = 0.0f;
			conteo++;
		}
	}

	if (flag2) {
		if (rotarT <= 15.0f and flag == true) {
			rotarT += 2.4f;
			if (rotarT >= 15.0f) {
				flag = false;
			}
		}
		else if (rotarT >= -15.0f and flag == false) {
			rotarT += -2.4f;
			if (rotarT <= -15.0f) {
				flag = true;
			}
		}
	}
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


	if (keys[GLFW_KEY_1])
	{
		if (flagP1 == false && teclaP1 == false) {
			animarP1 = true;
		}
		if (animarP1 == false && teclaP1 == true) {
			flagP1 = true;
		}

	}

	if (keys[GLFW_KEY_2])
	{
		if (flagP2 == false && teclaP2 == false) {
			animarP2 = true;
		}
		if (animarP2 == false && teclaP2 == true) {
			flagP2 = true;
		}

	}

	if (keys[GLFW_KEY_3])
	{
		if (flagP3 == false && teclaP3 == false) {
			animarP3 = true;
		}
		if (animarP3 == false && teclaP3 == true) {
			flagP3 = true;
		}

	}

	if (keys[GLFW_KEY_P])
	{
		if (activeG == true) {
			activeG = false;
		}
		else {
			activeG = true;
		}

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