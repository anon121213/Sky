#include "Skypch.h"
#include "SpriteRenderer.h"
#include "Sky/Renderer/Renderer2D.h"

namespace Sky {

	SpriteRenderer::SpriteRenderer(Ref<Texture2D> texture, Ref<Transform> transform)
		: m_SpriteTexture(texture), m_Transform(transform) { }

	void SpriteRenderer::Render()
	{
		Renderer2D::DrawRotatedQuad(m_Transform->GetPosition(),
			m_Transform->GetRotation().z,
			{ m_Transform->GetScale().x, m_Transform->GetScale().y }, 
			m_SpriteTexture,
			m_TilingFactor,
			m_TintColor);
	}

}
