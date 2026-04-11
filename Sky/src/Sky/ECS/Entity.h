#pragma once
#include <skypch.h>

namespace Sky
{
	using Entity = uint32_t;

	constexpr uint32_t ENTITY_INDEX_BITS = 24;
	constexpr uint32_t ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1; 
	constexpr uint32_t ENTITY_GEN_MASK = ~ENTITY_INDEX_MASK;           
	constexpr Entity NullEntity = 0;

	inline uint32_t GetEntityIndex(Entity e) { return e & ENTITY_INDEX_MASK; }
	inline uint32_t GetEntityGeneration(Entity e) { return (e >> ENTITY_INDEX_BITS) & (ENTITY_GEN_MASK >> ENTITY_INDEX_BITS); }
	inline Entity   MakeEntity(uint32_t id, uint32_t gen) { return id | (gen << ENTITY_INDEX_BITS); }

}