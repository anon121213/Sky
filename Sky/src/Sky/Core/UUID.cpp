#include "skypch.h"
#include "UUID.h"

#include <random>

namespace Sky {

    static std::mt19937_64& GetUUIDEngine()
    {
        static std::random_device rd;
        static std::mt19937_64 engine(rd());
        return engine;
    }

    static uint64_t GenerateRandomUInt64()
    {
        static std::uniform_int_distribution<uint64_t> distribution;
        return distribution(GetUUIDEngine());
    }

    UUID::UUID()
        : m_UUID(GenerateRandomUInt64())
    {
    }

    UUID::UUID(uint64_t uuid)
        : m_UUID(uuid)
    {
    }

}