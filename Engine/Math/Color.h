#pragma once
#include <cstdint>
#include <sstream>
#include <string>
#include <iostream>
namespace neu
{
	//typedef unsigned char u8_t;
	//using u8_t = unsigned char;

	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		friend std::istream& operator >> (std::istream& stream, Color& color);
	};

	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		std::string str;
		// red
		str = line.substr(line.find("{") + 1, line.find(",") - line.find("}") - 1);
		color.r = (uint8_t)(std::stof(str) * 255);
		line = line.substr(line.find(",") + 1);
		// green
		str = line.substr(0, line.find(","));
		color.g = (uint8_t)(std::stof(str) * 255);
		// blue
		str = line.substr(line.find(",") + 1, (line.find("}") ) - line.find(",") - 1);
		color.b = (uint8_t)(std::stof(str) * 255);
		// default alpha to 255
		color.a = 255;
		return stream;
	}
}
