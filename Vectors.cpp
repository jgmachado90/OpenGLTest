#include <iostream>

#define GLM_SWIZZLE

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

void Constructors() {
	std::cout << std::endl;


	glm::vec2 Point0{ 10.0f, 10.0f };
	glm::vec3 Point1{10.0f, 0.0f, 0.0f};
	glm::vec4 Point2{ 10.0f, 0.0f, 0.0f, 10.0f};
	glm::ivec2 Point3{ 3,4 };
	glm::bvec3 Point4{ true, false, true };
	glm::dvec2 Point5{ 10.0, 10.0 };
	glm::vec3 Point6{ Point0, 1.0f };
	glm::vec4 Point7{ Point2 };

	std::cout << "Point0" << glm::to_string(Point0) << std::endl;
	std::cout << "Point1" << glm::to_string(Point1) << std::endl;
	std::cout << "Point2" << glm::to_string(Point2) << std::endl;
	std::cout << "Point3" << glm::to_string(Point3) << std::endl;
	std::cout << "Point4" << glm::to_string(Point4) << std::endl;
	std::cout << "Point5" << glm::to_string(Point5) << std::endl;
	std::cout << "Point6" << glm::to_string(Point6) << std::endl;
	std::cout << "Point7" << glm::to_string(Point7) << std::endl;

}

void Components() {

	std::cout << std::endl;

	glm::vec4 P{ 1,2,3,4};
	std::cout << "X: " << P.x << " Y: " << P.y << " Z: " << P.z << " W: " << P.w << std::endl;
	std::cout << "R: " << P.x << " G: " << P.y << " B: " << P.z << " A: " << P.a << std::endl;
	std::cout << "0: " << P[0] << " 1: " << P[1] << " 2: " << P[2] << " 3: " << P[3] << std::endl;
}

void Swizzle() {
	std::cout << std::endl;

	glm::vec3 P{ 1,2,3 };
	glm::vec3 Q = P.xxx;
	glm::vec3 R = P.xyx;
	
	std::cout << glm::to_string(R) << std::endl;

}
void Operations() {
	std::cout << std::endl;

	glm::vec3 P0{ 10.0f, 10.0f, 0.0f, };
	glm::vec3 P1{ 10.0f, 10.0f, 10.0f };

	glm::vec3 R;

	//SOMA
	R = P0 + P1;
	std::cout << glm::to_string(R) << std::endl;

	//SUBTRAÇÂO
	R = P0 - P1;
	std::cout << glm::to_string(R) << std::endl;

	//ESCALA
	R = P0 * 5.0f;
	std::cout << glm::to_string(R) << std::endl;

	//MULTIPLICAÇÂO
	R = P0 * P1;
	std::cout << glm::to_string(R) << std::endl;

	//tamanho do vetor
	float L = glm::length(P0);
	std::cout << L << std::endl;

	//Normalizar vetor
	glm::vec3 Norm = glm::normalize(P0);

	//Produto escalar
	float Dot = glm::dot(P0, P1);

	//Produto Vetorial
	glm::vec3 Cross = glm::cross(P0, P1);

	//Distancia entre 2 pontos
	float Distance = glm::distance(P0, P1);

	//Refração
	glm::vec3 Refract = glm::refract(P0, Norm, 1.0f);

	//Reflexão
	glm::vec3 Reflect = glm::reflect(P0, Norm);

}


int main() {

	Constructors();
	Components();
	Swizzle();
	Operations();

	return 0;
}