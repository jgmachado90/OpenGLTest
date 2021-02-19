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


int main() {
	std::cout << "Hello World!" << std::endl;
	TranslationMatrix();
	ScaleMatrix();
	return 0;
}