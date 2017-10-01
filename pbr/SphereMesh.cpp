
#include "SphereMesh.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

SphereMesh::SphereMesh(GLuint resolution)
{
	std::vector<Vertex> vertices;
	std::vector<Triangle> indices;

	const float PI = glm::pi<float>();
	const float TWO_PI = glm::two_pi<float>();
	const float INV_RESOLUTION = 1.0f / static_cast<float>(resolution - 1);

	for (GLuint uIndex = 0; uIndex < resolution; ++uIndex)
	{
		const float uAlpha = uIndex * INV_RESOLUTION;
		const float theta = glm::mix(0.0f, TWO_PI, uAlpha);

		for (GLuint vIndex = 0; vIndex < resolution; ++vIndex)
		{
			const float vAlpha = vIndex * INV_RESOLUTION;
			const float phi = glm::mix(0.0f, PI, vAlpha);

			const glm::vec3 vertexPosition =
			{
				std::cos(theta) * std::sin(phi),
				std::sin(theta) * std::sin(phi),
				std::cos(phi)
			};

			Vertex vertex =
			{
				vertexPosition,
				glm::normalize(vertexPosition),
				{ 1.0 - uAlpha, 1.0 - vAlpha }
			};

			vertices.push_back(vertex);
		}
	}

	for (GLuint jIndex = 0; jIndex < resolution - 1; ++jIndex)
	{
		for (GLuint iIndex = 0; iIndex < resolution - 1; ++iIndex)
		{
			GLuint i = iIndex;
			GLuint j = jIndex;

			GLuint p0 = i + j		     * resolution;
			GLuint p1 = i + 1 + j        * resolution;
			GLuint p2 = i + (j + 1)      * resolution;
			GLuint p3 = i + 1 + (j + 1)  * resolution;

			Triangle t1{ p3, p2, p0 };
			Triangle t2{ p1, p3, p0 };

			indices.push_back(t1);
			indices.push_back(t2);
		}
	}

	initialize(vertices, indices);
}