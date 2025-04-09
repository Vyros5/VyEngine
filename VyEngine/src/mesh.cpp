#include "mesh.hpp"

#pragma region VERTEX

std::vector<Vertex> Vertex::genList(float* vertices, int numVertices)
{
	std::vector<Vertex> vertList(numVertices);

	int stride = 8;

    for (int i = 0; i < numVertices; i++) {
        vertList[i].position = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 2]
        );

        vertList[i].normal = glm::vec3(
            vertices[i * stride + 3],
            vertices[i * stride + 4],
            vertices[i * stride + 5]
        );

        vertList[i].texCoord = glm::vec2(
            vertices[i * stride + 6],
            vertices[i * stride + 7]
        );
    }

    return vertList;
}

#pragma endregion


