#include "skypch.h"
#include "Registry.h"

namespace Sky
{
	Entity Registry::Create() {
		uint32_t id;

		if (!m_FreeList.empty()) {
			id = m_FreeList.back();
			m_FreeList.pop_back();
			return MakeEntity(id, m_Generations[id]); 
		}

		id = m_Next++;
		m_Generations.push_back(0);
		return MakeEntity(id, 0);
	}

	void Registry::Destroy(const Entity entity) {
		SKY_ASSERT(IsValid(entity), "Entity is not valid");

		const uint32_t id = GetEntityIndex(entity);

		for (auto& [typeId, pool] : m_Pools) {
			if (pool->Has(entity))
				pool->Remove(entity);
		}

		m_Generations[id]++;  
		m_FreeList.push_back(id);
	}

}
