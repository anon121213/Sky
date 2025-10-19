#pragma once

#ifdef SKY_PLATFORM_WINDOWS

extern Sky::Application* Sky::CreateApplication();

int main(int argc, char** argv) {
	Sky::Log::Init();
	Sky::Log::GetCoreLogger()->warn("Initialized log!");
	Sky::Log::GetClientLogger()->warn("Hello");

	auto app = Sky::CreateApplication();
	app->Run();
	delete app;
}

#endif 