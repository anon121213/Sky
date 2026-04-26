#pragma once

#include "Sky/Core/Monitor.h"

namespace Sky
{
	class GlfwMonitor : public Monitor
	{
	public:
		GlfwMonitor();

		const std::string& GetName() const override { return m_Name; }
		int GetWidth() const override { return m_Width; }
		int GetHeight() const override { return m_Height; }
		int GetRefreshRate() const override { return m_RefreshRate; }
		float GetContentScale() const override { return m_ContentScale; }

	private:
		std::string m_Name;
		int m_Width = 0;
		int m_Height = 0;
		int m_RefreshRate = 0;
		float m_ContentScale = 1.0f;
	};
}
