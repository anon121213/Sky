#include <Sky.h>

class Sandbox : public Sky::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Sky::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};


Sky::Application* Sky::CreateApplication()
{
	return new Sandbox();
}