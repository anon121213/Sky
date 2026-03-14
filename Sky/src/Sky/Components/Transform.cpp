#include "skypch.h"
#include "Transform.h"

namespace Sky {

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_Position = position;
		m_Rotation = rotation;
		m_Scale = scale;
	}

	const void Transform::SetPosition(const float x, const float y, const float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}

	const void Transform::SetRotation(const float x, const float y, const float z)
	{
		m_Rotation.x = x;
		m_Rotation.y = y;
		m_Rotation.z = z;
	}

	const void Transform::SetScale(const float x, const float y, const float z)
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Rotation.z = z;
	}

	const void Transform::SetPosition(const glm::vec3& position)
	{
		m_Rotation.x = position.x;
		m_Rotation.y = position.y;
		m_Rotation.z = position.z;
	}

	const void Transform::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation.x = rotation.x;
		m_Rotation.y = rotation.y;
		m_Rotation.z = rotation.z;
	}

	const void Transform::SetScale(const glm::vec3& scale)
	{
		m_Rotation.x = scale.x;
		m_Rotation.y = scale.y;
		m_Rotation.z = scale.z;
	}

}