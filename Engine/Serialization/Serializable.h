#pragma once
#include "Json.h"

namespace neu
{
	class Iserializable
	{
	public:
		virtual ~Iserializable() {};

		virtual bool Write(const rapidjson::Value& value) const = 0;
		virtual bool Read(const rapidjson::Value& value) = 0;
	};
}