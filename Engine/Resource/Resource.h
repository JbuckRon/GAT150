#pragma once
#include <string>
namespace neu
{
	class Resource
	{
	public:
		virtual bool Create(const std::string& filename , ...) = 0;
	};
}