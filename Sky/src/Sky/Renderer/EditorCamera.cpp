#include "skypch.h"
#include "EditorCamera.h"

#include "Sky/Core/Input.h"
#include "Sky/Core/KeyCodes.h"
#include "Sky/Core/MouseCodes.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

namespace Sky{

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void EditorCamera::UpdateView()
	{
		m_Position = CalculatePosition();

		const glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		const glm::vec2 mouse{ Input::GetMouseX(), Input::GetMouseY() };
		const glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.0015f;
		m_InitialMousePosition = mouse;

		const bool alt = Input::IsKeyPressed(Key::LeftAlt);
		const bool lmb = Input::IsMouseButtonPressed(Mouse::ButtonLeft);
		const bool mmb = Input::IsMouseButtonPressed(Mouse::ButtonMiddle);
		const bool rmb = Input::IsMouseButtonPressed(Mouse::ButtonRight);

		if (alt && lmb)
			MouseRotate(delta);
		else if (mmb)
			MousePan(delta);
		else if (alt && rmb)
			MouseZoom(delta.x + delta.y);
		else if (rmb)
		{
			const glm::vec3 oldPosition = m_Position;
			MouseRotate(delta);
			m_FocalPoint = oldPosition + GetForwardDirection() * m_Distance;
			FlyMove(ts);
		}

		UpdateView();
	}

	void EditorCamera::FlyMove(float ts)
	{
		float speed = m_FlySpeed * ts;
		if (Input::IsKeyPressed(Key::LeftShift))
			speed *= 3.0f;

		const glm::vec3 forward = GetForwardDirection();
		const glm::vec3 right   = GetRightDirection();
		const glm::vec3 worldUp{ 0.0f, 1.0f, 0.0f };

		glm::vec3 dir{ 0.0f };
		if (Input::IsKeyPressed(Key::W)) dir += forward;
		if (Input::IsKeyPressed(Key::S)) dir -= forward;
		if (Input::IsKeyPressed(Key::D)) dir += right;
		if (Input::IsKeyPressed(Key::A)) dir -= right;
		if (Input::IsKeyPressed(Key::E)) dir += worldUp;
		if (Input::IsKeyPressed(Key::Q)) dir -= worldUp;

		if (glm::dot(dir, dir) > 0.0f)
			m_FocalPoint += glm::normalize(dir) * speed;
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SKY_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
}
