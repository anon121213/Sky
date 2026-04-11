#pragma once
#include <skypch.h>

#include "Entity.h"
#include "IComponentPool.h"
#include "ComponentTypeId.h"

namespace Sky
{
    class IGroup {
    public:
        virtual ~IGroup() = default;
        virtual void OnAdd(Entity entity, IComponentPool* addedPool) = 0;
        virtual void OnRemove(Entity entity, IComponentPool* removedPool) = 0;
        virtual bool OwnsComponent(ComponentTypeId id) const = 0;
    };

}
