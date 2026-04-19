#pragma once

#include <string>

namespace Sky
{
	class FileDialogs
	{
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter, const char* defaultExt = nullptr);
	};
}