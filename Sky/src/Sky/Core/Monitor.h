#pragma once

#include "Sky/Core/Core.h"

#include <string>

namespace Sky
{
	class Monitor
	{
	public:
		virtual ~Monitor() = default;

		virtual const std::string& GetName() const = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetRefreshRate() const = 0;
		virtual float GetContentScale() const = 0;

		static Scope<Monitor> CreatePrimary();
	};
}
