#include <Sky.h>
#include <Sky/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Sky
{
	class SkyEditor : public Application
	{
	public:
		SkyEditor()
			: Application("Sky Editor")
		{
			PushLayer(new EditorLayer());
		}

		~SkyEditor()
		{
		}
	};


	Application* CreateApplication()
	{
		return new SkyEditor();
	}
}