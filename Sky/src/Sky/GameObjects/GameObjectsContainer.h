#pragma once

#include "skypch.h"
#include "GameObject.h"
#include "ObjectsContainer.h"

namespace Sky {
	class GameObjectsContainer : ObjectsContainer
	{
	public: 
		void AddObject(Object& go) const override;
		void RemoveObject(Object& go) const override;
		void RemoveObject(UUID& id) const override;

		virtual void OnUpdate(const Timestep ts) const override;
	private:
		std::unordered_map<UUID&, GameObject&> m_GameObjects;
	};
}