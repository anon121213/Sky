#pragma once

#include "Sky/Core/Layer.h"

#include "Sky/Events/ApplicationEvent.h"

namespace Sky {

	class SKY_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}