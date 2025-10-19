#include "Application.h"

#include "Sky/Event/ApplicationEvent.h"
#include "Sky/Log.h"

namespace Sky {

	Application::Application()
	{
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			SKY_TRACE(e.ToString());
		}
		while (true) {}
	}

}
