#pragma once
#include "Json.h"

namespace neu
{
	class Iserializable
	{
	public:
		virtual ~Iserializable() {};

		virtual bool write(const rapidjson::Value& value) const = 0;
		virtual bool read(const rapidjson::Value& value) = 0;
	};
}