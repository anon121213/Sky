#pragma once

#include "Skypch.h"
#include "Component.h"
#include "Transform.h"

namespace Sky {

	class SpriteRenderer : Component
	{
	public:
		SpriteRenderer(Ref<Texture2D> texture, Ref<Transform> transrom);

		void SetSprite(const Ref<Texture2D> texture) { m_SpriteTexture = texture; }
		void Render();

	private:
		Ref<Texture2D> m_SpriteTexture;
		Ref<Transform> m_Transform;
		float m_TilingFactor = 1.0f;
		glm::vec4& m_TintColor = glm::vec4(1.0f);
	};

}
