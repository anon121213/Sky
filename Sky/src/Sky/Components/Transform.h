#pragma once

#include <glm/glm.hpp>

namespace Sky {
	class Transform : Component
	{
	public:
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

		const void SetPosition(const float x, const float y, const float z);
		const void SetRotation(const float x, const float y, const float z);
		const void SetScale(const float x, const float y, const float z);

		const void SetPosition(const glm::vec3& position);
		const void SetRotation(const glm::vec3& rotation);
		const void SetScale(const glm::vec3& scale);

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Position; }
		const glm::vec3& GetScale() const { return m_Position; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}