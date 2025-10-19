#include <Sky.h>

class Sandbox : public Sky::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};


Sky::Application* Sky::CreateApplication()
{
	return new Sandbox();
}