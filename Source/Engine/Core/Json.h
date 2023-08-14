#pragma once
#include <rapidjson/<find the header document.h>
namespace kiko
{
	class Json
	{

	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false)
	};
}