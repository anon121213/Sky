#pragma once

#include "Sky/Core/Layer.h"

#include "Sky/Events/ApplicationEvent.h"
#include "Sky/Events/KeyEvent.h"
#include "Sky/Events/MouseEvent.h"

namespace Sky {

	class SKY_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}