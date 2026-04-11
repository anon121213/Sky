#pragma once
#include <skypch.h>

#include "ComponentPool.h"
#include "Entity.h"
#include "IComponentPool.h"
#include "IGroup.h"

namespace Sky
{
	template<typename... Components>
	class Group : public IGroup
	{
	public:
		explicit Group(ComponentPool<Components>*... pools)
			: m_OwnedPools({ static_cast<IComponentPool*>(pools)... })
			, m_TypedPools(pools...)
			, m_OwnedTypeIds({ GetComponentTypeId<Components>()... })
		{
		}

		Group(const Group&) = delete;
		Group& operator=(const Group&) = delete;

		void OnAdd(const Entity entity, IComponentPool* addedPool) override
		{
			for (const auto pool : m_OwnedPools) {
				if (pool == addedPool)
					continue;

				if (!pool->Has(entity))
					return;
			}

			for (const auto pool : m_OwnedPools)
				pool->SwapToIndex(entity, m_GroupSize);

			m_GroupSize++;
		}

		void OnRemove(const Entity entity, IComponentPool* removedPool) override
		{
			if (const auto entityIndex = m_OwnedPools[0]->GetIndex(entity); entityIndex >= m_GroupSize)
				return;

			m_GroupSize--;

			for (const auto pool : m_OwnedPools)
				pool->SwapToIndex(entity, m_GroupSize);
		}

		bool OwnsComponent(const ComponentTypeId id) const override {
			for (const auto typeId : m_OwnedTypeIds)
				if (typeId == id) 
					return true;

			return false;
		}

		template<typename Func>
		void Each(Func func) {
			auto& ids = std::get<0>(m_TypedPools)->GetDenseIds();
			for (size_t i = 0; i < m_GroupSize; i++)
				func(ids[i], std::get<ComponentPool<Components>*>(m_TypedPools)->GetDense()[i]...);
		}

		size_t Size() const { return m_GroupSize; }

	private:
		size_t m_GroupSize = 0;                  
		std::vector<IComponentPool*> m_OwnedPools;
		std::tuple<ComponentPool<Components>*...> m_TypedPools;
		std::vector<ComponentTypeId> m_OwnedTypeIds;
	};

}
