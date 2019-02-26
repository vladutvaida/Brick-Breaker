#include "Object2D.h"

#include <Core/Engine.h>
Mesh* Object2D::CreateCircle(std::string name, float radius, glm::vec3 color, bool fill)
{
	const double PI = 3.141592653;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	int i;
	int N = 1000;
	float x, y;
	double alpha = 0;
	float R = radius;
	for (i = 0; i < N; i++) {
		x = R * cos(alpha);
		y = R * sin(alpha);

		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), glm::vec3(0, 1, 0)));
		alpha += N / PI;
	}

	for (i = 0; i < N - 1; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	Mesh* circle = new Mesh(name);
	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices

	}

	circle->InitFromData(vertices, indices);

	return circle;

}
Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}