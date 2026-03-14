#pragma once

#include "skypch.h"

#include <cstdint>
#include <functional>

namespace Sky {

    class UUID
    {
    public:
        UUID();
        explicit UUID(uint64_t uuid);

        uint64_t Value() const { return m_UUID; }

        operator uint64_t() const { return m_UUID; }

        bool operator==(const UUID& other) const
        {
            return m_UUID == other.m_UUID;
        }

        bool operator!=(const UUID& other) const
        {
            return m_UUID != other.m_UUID;
        }

    private:
        uint64_t m_UUID = 0;
    };

}

namespace std {

    template<>
    struct hash<Sky::UUID>
    {
        size_t operator()(const Sky::UUID& uuid) const noexcept
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };

}