#pragma once
#include <skypch.h>

#include "ComponentPool.h"
#include "Entity.h"
#include "Group.h"
#include "IComponentPool.h"
#include "IGroup.h"
#include "ComponentTypeId.h"

namespace Sky
{
	class Registry
	{
	public:
		Registry()
		{
			m_Pools.reserve(64);
		};

		Registry(const Registry&) = delete;
		Registry& operator=(const Registry&) = delete;

		Entity Create();

		void Destroy(Entity entity);

		template<typename T, typename... Args>
		void Replace(Entity entity, Args&&... args)
		{
			SKY_ASSERT(IsValid(entity), "Entity is invalid");
			auto pool = GetPool<T>();
			pool->Add(entity, std::forward<Args>(args)...);

			for (auto group : m_Groups)
				group->OnAdd(entity, pool);
		}

		template<typename T>
		T& Get(Entity entity) {
			SKY_ASSERT(IsValid(entity), "Entity is invalid");
			SKY_ASSERT(Has<T>(entity), "Entity does not have this component");
			return GetPool<T>()->Get(entity);
		}

		template<typename T>
		bool Has(Entity entity) {
			SKY_ASSERT(IsValid(entity), "Entity is invalid");
			const ComponentTypeId id = GetComponentTypeId<T>();
			
			if (id >= m_Pools.size() || m_Pools[id] == nullptr)
				return false;

			return m_Pools[id]->Has(entity);
		}

		template<typename T>
		void Remove(Entity entity)
		{
			SKY_ASSERT(IsValid(entity), "Entity is invalid");
			if (!Has<T>(entity))
				return;

			const auto pool = GetPool<T>();

			for (auto group : m_Groups)
				group->OnRemove(entity, pool);

			pool->Remove(entity);
		}

		template<typename... Components>
		Group<Components...>* CreateGroup() {
			for (auto group : m_Groups)
				for (auto typeId : { GetComponentTypeId<Components>()... })
					SKY_ASSERT(!group->OwnsComponent(typeId), "Component already owned by another group");

			auto group = new Group<Components...>(GetPool<Components>()...);
			m_Groups.push_back(group);
			return group;
		}

		template<typename... Components>
		Group<Components...>* GetGroup() {
			for (auto group : m_Groups) {
				bool match = true;
				for (auto typeId : { GetComponentTypeId<Components>()... }) {
					if (!group->OwnsComponent(typeId)) {
						match = false;
						break;
					}
				}
				if (match) return static_cast<Group<Components...>*>(group);
			}
			return nullptr;
		}

		template<typename... Components, typename Func>
		void View(Func callback) {
			if (!(... && (GetComponentTypeId<Components>() < m_Pools.size() &&
				m_Pools[GetComponentTypeId<Components>()] != nullptr)))
				return;

			std::array<IComponentPool*, sizeof...(Components)> pools = {
				GetPool<Components>()...
			};

			IComponentPool* smallest = nullptr;
			size_t minSize = SIZE_MAX;

			for (auto pool : pools) {
				if (pool->Size() < minSize) {
					minSize = pool->Size();
					smallest = pool;
				}
			}

			if (!smallest || minSize == 0) return;

			for (Entity e : smallest->GetDenseIds()) {
				bool hasAll = true;
				for (auto pool : pools) {
					if (!pool->Has(e)) { hasAll = false; break; }
				}
				if (!hasAll) continue;

				callback(e, Get<Components>(e)...);
			}
		}

		bool IsValid(const Entity entity) const {
			const uint32_t id = GetEntityIndex(entity);
			return id < m_Generations.size() &&
				GetEntityGeneration(entity) == m_Generations[id];
		}

		~Registry() {
			for (auto pool : m_Pools)
				delete pool;

			for (const auto group : m_Groups)
				delete group;
		}

	private:
		template<typename T>
		ComponentPool<T>* GetPool() {
			const ComponentTypeId id = GetComponentTypeId<T>();

			if (id >= m_Pools.size())
				m_Pools.resize(id + 1);

			if (m_Pools[id] == nullptr)
			{
				ComponentPool<T>* pool = new ComponentPool<T>();
				m_Pools[id] = pool;
				return pool;
			}

			return static_cast<ComponentPool<T>*>(m_Pools[id]);
		}

		std::vector<IComponentPool*> m_Pools;
		std::vector<Entity> m_FreeList;  
		std::vector<uint32_t> m_Generations;
		std::vector<IGroup*> m_Groups;

		Entity m_Next = 1;               
	};

}

