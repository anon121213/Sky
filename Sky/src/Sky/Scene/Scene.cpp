#include <skypch.h>
#include "Scene.h"
#include "Entity.h"

#include "Components.h"
#include "glm/fwd.hpp"
#include "Sky/Renderer/Renderer2D.h"

namespace Sky
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{m_Registry.create(), this};
		entity.AddComponent<TransformComponent>(glm::mat4{1.0f});
		auto& tag = entity.AddComponent<TagComponent>(name.empty() ? "Entity" : name);
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<SpriteRendererComponent>(entt::get<TransformComponent>);
			for (auto entity : group)
			{
				auto& [transform, spriteRenderer] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, spriteRenderer.Color);
			}

			Renderer2D::EndScene();
		}
	}
}
