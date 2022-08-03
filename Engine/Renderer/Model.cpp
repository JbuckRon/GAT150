#include "Model.h"
#include "../Core/File.h"
#include <sstream>
#include <string>
#include <iostream>

namespace neu 
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	void Model::Draw(Renderer& renderer, const Vector2& position,float angle,  float scale)
	{
		/*neu::Color color;
		color.r = neu::random(256);
		color.g = neu::random(256);
		color.b = neu::random(256);
		color.a = 255;*/

		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}
	void Model::Load(const std::string filename)
	{
		std::string buffer;

		neu::ReadFile(filename, buffer);

		std::istringstream stream(buffer);
		stream >> m_color;
		std::string line;
		std::getline(stream, line);

		//std::cout << line << std::endl;

		size_t numPoints = std::stoi(line);

		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}
	}
	float Model::CalculateRadius()
	{
		float radius = 0;

		//find largest length (radius)
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}
}

