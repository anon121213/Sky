#pragma once 

#include "skypch.h"
#include "Object.h"
#include "Sky/Core/UUID.h"
#include "Sky/Components/Component.h"
#include "Sky/Components/Transform.h"

namespace Sky {
	class GameObject : Object {
	public:
		GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

		const Ref<Transform> GetTransform() { return m_Transform; }

		template<typename T>
		Ref<Component> GetComponenet() {
			for (auto& kv : component) {
				if (typedef(component.second) == typedef(T))
					return component.second;
			}

			return nullptr;
		}

		template<typename T>
		void AddComponent() {
			Ref<Component> component = static_cast<Component>(CreateRef<T>);
			m_Components[component->GetId()] = component;
		}
		
		void AddComponent(Ref<Component> component) {
			if (m_Components.find(component->GetId()) != m_Components.end())
				return;

			m_Components[component->GetId()] = component;
		}

	private:
		Ref<Transform> m_Transform;
		std::unordered_map<UUID&, Ref<Component>> m_Components; // make key to type of component for quicly fined
	};
}