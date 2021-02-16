#include <iostream>

#include <GLFW/glfw3.h>
#include <cassert>

const int Width = 800;
const int Height = 800;


int main() {


	//Inicializar a biblioteca GLFW
	assert(glfwInit());

	//Cria uma janela
	GLFWwindow* Window = glfwCreateWindow(Width, Height, "OpenGL teste", nullptr, nullptr);
	assert(Window);

	//Loop
	while (!glfwWindowShouldClose(Window)) {
		//Processa todos os eventos da fila de eventos do GLFW
		//Eventos podem ser teclado, mouse, gamepad....
		glfwPollEvents();


		//Envia o conteúdo do framebuffer da janela para ser desenhado na tela
		glfwSwapBuffers(Window);
	
	}

	//Encerra a biblioteca
	glfwTerminate();

	return 0;
}