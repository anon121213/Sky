#include "skypch.h"
#include "GameObject.h"

namespace Sky {
	GameObject::GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
		m_Transform = CreateRef<Transform>(position, rotation, scale);
		AddComponent(m_Transform);
	}
}