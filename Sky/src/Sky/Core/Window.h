#pragma once

#include "skypch.h"

#include "Sky/Core/Core.h"
#include "Sky/Events/Event.h"

namespace Sky {
	
	enum class WindowMode
	{
		Windowed,
		Maximized
	};

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		WindowMode Mode;

		explicit WindowProps(std::string title = "Sky Engine",
			uint32_t width = 1920,
			uint32_t height = 1080,
			WindowMode mode = WindowMode::Windowed)
			: Title(std::move(title)), Width(width), Height(height), Mode(mode)
		{
		}
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}