#pragma once
#include <skypch.h>

namespace Sky
{
    using ComponentTypeId = std::size_t;

    inline ComponentTypeId GetUniqueComponentTypeId() {
        static std::size_t counter = 0;
        return counter++;
    }

    template<typename T>
    inline ComponentTypeId GetComponentTypeId() {
        static const ComponentTypeId id = GetUniqueComponentTypeId();
        return id;
    }
} 