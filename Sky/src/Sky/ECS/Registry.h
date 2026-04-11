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
		Registry() = default;
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
			const auto it = m_Pools.find(id);
			if (it == m_Pools.end()) return false;
			return static_cast<ComponentPool<T>*>(it->second)->Has(entity);
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
			if (!(... && m_Pools.count(GetComponentTypeId<Components>())))
				return;

			IComponentPool* smallest = nullptr;
			size_t minSize = SIZE_MAX;

			for (auto pool : { static_cast<IComponentPool*>(GetPool<Components>())... }) {
				if (pool->Size() < minSize) {
					minSize = pool->Size();
					smallest = pool;
				}
			}

			if (!smallest || minSize == 0) return;

			for (Entity e : smallest->GetDenseIds()) {
				if (!(Has<Components>(e) && ...))
					continue;

				callback(e, Get<Components>(e)...);
			}
		}

		bool IsValid(const Entity entity) const {
			const uint32_t id = GetEntityIndex(entity);
			return id < m_Generations.size() &&
				GetEntityGeneration(entity) == m_Generations[id];
		}

		~Registry() {
			for (auto& [id, pool] : m_Pools)
				delete pool;

			for (const auto group : m_Groups)
				delete group;
		}

	private:
		template<typename T>
		ComponentPool<T>* GetPool() {
			const ComponentTypeId id = GetComponentTypeId<T>();

			if (const auto it = m_Pools.find(id); it != m_Pools.end())
				return static_cast<ComponentPool<T>*>(it->second);

			ComponentPool<T>* pool = new ComponentPool<T>();
			m_Pools[id] = pool;
			return pool;
		}

		std::unordered_map<ComponentTypeId, IComponentPool*> m_Pools;
		std::vector<Entity> m_FreeList;  
		std::vector<uint32_t> m_Generations;
		std::vector<IGroup*> m_Groups;

		Entity m_Next = 1;               
	};

}

