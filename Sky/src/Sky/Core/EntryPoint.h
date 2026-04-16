#pragma once

#ifdef SKY_PLATFORM_WINDOWS

extern Sky::Application* Sky::CreateApplication();

int main(int argc, char** argv) {
	Sky::Log::Init();

	SKY_PROFILE_BEGIN_SESSION("Startup", "SkyProfile-Startup.json");
	const auto app = Sky::CreateApplication();
	SKY_PROFILE_END_SESSION();

	SKY_PROFILE_BEGIN_SESSION("Runtime", "SkyProfile-Runtime.json");
	app->Run();
	SKY_PROFILE_END_SESSION();

	SKY_PROFILE_BEGIN_SESSION("Shutdown", "SkyProfile-Shutdown.json");
	delete app;
	SKY_PROFILE_END_SESSION();
}

#endif 