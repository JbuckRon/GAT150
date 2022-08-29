#include "Model.h"
#include "../Core/File.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
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

	bool Model::Create(const std::string& filename, ...)
	{
		if (!Load(filename))
		{
			LOG("Error could not read file %s", filename.c_str());
			return false;
		}
		return true;
	}

	void Model::Draw(Renderer& renderer, const Vector2& position,float angle,  const Vector2& scale)
	{
		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Matrix3x3 mx = transform.matrix;

		for (int i = 0; i < m_points.size() - 1; i++)
		{
			neu::Vector2 p1 = mx * m_points[i];
			neu::Vector2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1, p2, m_color);
		}
	}
	bool Model::Load(const std::string filename)
	{
		std::string buffer;

		if (!neu::ReadFile(filename, buffer))
		{
			LOG("Error could not read file %s", filename.c_str());
			return false;
		}

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
		return true;
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

