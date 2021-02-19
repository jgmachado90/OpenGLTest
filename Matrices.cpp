#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm\gtx\string_cast.hpp>

void PrintMatrix(const glm::mat4& M) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j){
			std::cout
				<< std::setw(10)
				<< std::setprecision(4)
				<< std::fixed
				<< M[j][i] << ' ';
		}
		std::cout << std::endl;
	}
}

void TranslationMatrix() {
	std::cout << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "Translation Matrix" << std::endl;
	std::cout << "=================" << std::endl;

	glm::mat4 I = glm::identity<glm::mat4>();
	glm::vec3 T{ 10, 10, 10 };
	glm::mat4 Translation = glm::translate(I, T);
	
	PrintMatrix(Translation);

	glm::vec4 Position{ 10,10,10,1 };
	glm::vec4 Direction{ 10,10,10,0 };

	std::cout << std::endl;
	Position = Translation * Position;

	std::cout << glm::to_string(Position) << std::endl;
	std::cout << "=================" << std::endl;
}

void ScaleMatrix() {
	std::cout << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "Scale Matrix" << std::endl;
	std::cout << "=================" << std::endl;

	glm::mat4 I = glm::identity<glm::mat4>();
	glm::vec3 ScaleAmount{ 2, 2, 2};
	glm::mat4 Scale = glm::scale(I, ScaleAmount);

	PrintMatrix(Scale);

	glm::vec4 Position{ 100,100,0,1 };
	glm::vec4 Direction{ 100, 100, 0, 0 };

	//matriz sempre vem primeiro
	Position = Scale * Position;
	std::cout << std::endl;
	std::cout << glm::to_string(Position) << std::endl;

	std::cout << "=================" << std::endl;
}

void RotationMatrix() {
	std::cout << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "Rotation Matrix" << std::endl;
	std::cout << "=================" << std::endl;

	glm::mat4 I = glm::identity<glm::mat4>();

	constexpr float Angle = glm::radians(90.0f);
	glm::vec3 Axis{ 0,0,1 };

	glm::mat4 Rotation = glm::rotate(I, Angle, Axis);

	PrintMatrix(Rotation);

	glm::vec4 Position{ 100,0,0,1 };
	glm::vec4 Direction{ 100, 0, 0, 0 };

	Position = Rotation * Position;

	std::cout << std::endl;
	std::cout << glm::to_string(Position) << std::endl;

	std::cout << "=================" << std::endl;
}

void ComposedMatrices() {
	std::cout << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "Composed Matrix" << std::endl;
	std::cout << "=================" << std::endl;


	glm::mat4 I = glm::identity<glm::mat4>();

	glm::vec3 T {0,10,0 };
	glm::mat4 Translation = glm::translate(I, T);

	constexpr float Angle = glm::radians(45.0f);
	glm::vec3 Axis{ 0,0,1 };
	glm::mat4 Rotation = glm::rotate(I, Angle, Axis);

	glm::vec3 ScaleAmount{ 2, 2, 0 };
	glm::mat4 Scale = glm::scale(I, ScaleAmount);

	std::cout << "Translation Matrix" << std::endl;
	PrintMatrix(Translation);
	std::cout << std::endl;
	std::cout << "Rotation Matrix" << std::endl;
	PrintMatrix(Rotation);
	std::cout << std::endl;
	std::cout << "Scale Matrix" << std::endl;
	PrintMatrix(Scale);
	std::cout << std::endl;

	glm::vec4 Position{ 1,1,0,1 };
	glm::vec4 Direction{ 1, 1, 0, 0 };


	//Transformar todas essas contas em uma matriz s�
	/*Position = Scale * Position;
	Position = Rotation * Position;
	Position = Translation * Position;*/
	
	//A*B != B*A
	glm::mat4 ModelMatrix = Translation * Rotation * Scale;

	std::cout << "Transform" << std::endl;
	PrintMatrix(ModelMatrix);
	std::cout << std::endl;

	Position = ModelMatrix * Position;
	Direction = ModelMatrix * Direction;
	std::cout << "Position" << std::endl;
	std::cout << glm::to_string(Position) << std::endl;
	std::cout << std::endl;
	std::cout << "Direction" << std::endl;
	std::cout << glm::to_string(Direction) << std::endl;
	std::cout << std::endl;


	std::cout << "=================" << std::endl;
}

void ModelViewProjection() {
	std::cout << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "Composed Matrix" << std::endl;
	std::cout << "=================" << std::endl;

	//Model vai ser a matriz formada pelas transformacoes e translacao, rotacao e escala. Uma matriz composta.
	glm::mat4 ModelMatrix = glm::identity<glm::mat4>();

	//View
	glm::vec3 Eye{0,0,10};
	glm::vec3 Center{0,0,0};
	glm::vec3 Up{0,1,0};
	glm::mat4 ViewMatrix = glm::lookAt(Eye, Center, Up);

	std::cout << "View" << std::endl;
	PrintMatrix(ViewMatrix);
	
	//Projection
	constexpr float FoV = glm::radians(45.0f);
	const float AspectRatio = 800.0f / 600.0f;
	const float Near = 1.0f;
	const float Far = 100000.0f;
	glm::mat4 ProjectionMatrix = glm::perspective(FoV, AspectRatio, Near, Far);
	std::cout << "Projection" << std::endl;
	PrintMatrix(ProjectionMatrix);

	glm::mat4 ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;
	std::cout << "Model View Projection" << std::endl;
	PrintMatrix(ModelViewProjection);

	glm::vec4 Position{ 0,0,0, 1 };
	Position = ModelViewProjection * Position;
	std::cout << glm::to_string(Position) << std::endl;

	std::cout << "=================" << std::endl;
}



int main() {
	std::cout << "Hello World!" << std::endl;
	TranslationMatrix();
	ScaleMatrix();
	RotationMatrix();
	ComposedMatrices();
	ModelViewProjection();
	return 0;
}