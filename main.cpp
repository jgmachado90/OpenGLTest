#include <iostream>
#include <cassert>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

const int Width = 800;
const int Height = 800;


int main() {

	
	//Inicializa a biblioteca GLFW
	assert(glfwInit() == GLFW_TRUE);

	//Cria uma janela
	GLFWwindow* Window = glfwCreateWindow(Width, Height, "OpenGL teste", nullptr, nullptr);
	assert(Window);
	//Referencia a janela
	glfwMakeContextCurrent(Window);

	//Inicializa a biblioteca GLEW
	assert(glewInit() == GLEW_OK);

	//Verifica a versão do OpenGL usada
	GLint GLMajorVersion = 0;
	GLint GLMinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
	std::cout << "OpenGL Version: " << GLMajorVersion << "." << GLMinorVersion << std::endl;

	//Mostra a placa de vídeo usada
	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	//Definir um triangulo em coordenadas normalizadas
	std::array<glm::vec3, 3> Triangle = {
		glm::vec3{-1.0f, -1.0f, 0.0f },
		glm::vec3{ 1.0f, -1.0f, 0.0f },
		glm::vec3{ 0.0f,  1.0f, 0.0f },
	};

	//ModelMatrix
	glm::mat4 ModelMatrix = glm::identity<glm::mat4>();

	//ViewMatrix
	//posição que a camera ta
	glm::vec3 Eye{ 0,0,5};
	//posição que ta olhando
	glm::vec3 Center{ 0,0,0 };
	//vetor up da camera
	glm::vec3 Up{ 0,1,0 };
	glm::mat4 ViewMatrix = glm::lookAt(Eye, Center, Up);

	//ProjectionMatrix
	constexpr float FoV = glm::radians(45.0f);
	const float AspectRatio = Width / Height;
	const float Near = 0.001f;
	const float Far = 1000.0f;
	glm::mat4 ProjectionMatrix = glm::perspective(FoV, AspectRatio, Near, Far);

	//MVP 
	glm::mat4 ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;

	//Aplicar a ModelView nos vértices do triangulo
	for (glm::vec3& Vertex : Triangle) {
		glm::vec4 ProjectedVertex = ModelViewProjection * glm::vec4{ Vertex, 1.0f };
		ProjectedVertex /= ProjectedVertex.w;
		//Esse vai ser o vértice copiado para a GPU e desenhado na tela
		Vertex = ProjectedVertex;
	}

	//Copiar os vertices do triangulo para a memória da GPU
	GLuint VertexBuffer;

	//Pedir para o OpenGL gerar o id do VertexBuffer
	glGenBuffers(1, &VertexBuffer);

	//Ativar o VertexBuffer como sendo o buffer para onde copiar os dados do triangulo
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	//Copiar os dados para a memória de vídeo
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle.data(), GL_STATIC_DRAW);


	//Definir a cor de fundo
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	//Loop
	while (!glfwWindowShouldClose(Window)) {

		//glClear vai limpar o framebuffer. GL_COLOR_BUFFER_BIT diz para limpar o buffer de cor.
		// Depois de limpar, ele vai preencher com a cor que foi configurada na ultima chamada do glClearColor.	
		// Quando for desenhar geometrias 3D volta ao glClear porque tem que limpar o buffer de profundidade (depth buffer).
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableVertexAttribArray(0);

		//Diz para o OpenGL que o VertexBuffer vai ser o Buffer ativo no momento
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);


		//Informa para o OpenGL onde, dentro do VertexBuffer, os vértices estão
		//O array triangles é contíguo em memória, basta dizer quantos vértices vamos usar pra desenhar o triangulo
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		//Finalmente, diz para o OpenGL desenhar o triangulo com os dados que estão armazenados no VertexBuffer.
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Reverter o estado que nós criamos
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);

		//Processa todos os eventos da fila de eventos do GLFW
		//Eventos podem ser teclado, mouse, gamepad....
		glfwPollEvents();


		//Envia o conteúdo do framebuffer da janela para ser desenhado na tela
		glfwSwapBuffers(Window);
	
	}

	//Desalocar o vertexBuffer
	glDeleteBuffers(1, &VertexBuffer);

	//Encerra a biblioteca
	glfwTerminate();

	return 0;
}