#include "RenderComponent.h"


namespace neu
{
	bool RenderComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	
	bool RenderComponent::read(const rapidjson::Value& value)
	{
		READ_DATA(value, sort_order);
		return true;
	}
}

//void neu::RenderComponent::Draw(Renderer& renderer)
//{
//}
