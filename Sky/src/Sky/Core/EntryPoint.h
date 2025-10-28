#pragma once

#ifdef SKY_PLATFORM_WINDOWS

extern Sky::Application* Sky::CreateApplication();

int main(int argc, char** argv) {
	Sky::Log::Init();
	Sky::Log::GetCoreLogger()->warn("Initialized log!");

	auto app = Sky::CreateApplication();
	app->Run();
	delete app;
}

#endif 