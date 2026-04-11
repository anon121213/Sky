#pragma once
#include "Entity.h"

namespace Sky
{
	class IComponentPool
	{
	public:
		virtual ~IComponentPool() = default;
		virtual void Remove(Entity entity) = 0;
		virtual bool Has(const Entity entity) const = 0;
		virtual void SwapToIndex(Entity entity, size_t index) = 0;
		virtual size_t Size() const = 0;
		virtual std::vector<Entity>& GetDenseIds() = 0;
		virtual size_t GetIndex(Entity entity) const = 0;
	};
}
