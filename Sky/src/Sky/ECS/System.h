#pragma once
#include <skypch.h>

#include "Registry.h"
#include "Sky/Core/Timestep.h"

namespace Sky
{
	class World;

	class System {
    public:
		void Construct(const uint32_t id, Registry* registry)
		{
            if (m_Id != UINT32_MAX)
				return;

			m_Id = id;
            m_Registry = registry;
		}

		uint32_t GetId() const { return m_Id; }
        Registry& GetRegistry() const { return *m_Registry; }

        virtual void OnAwake(World& world) {}
        virtual void OnStart(World& world) {}
        virtual void OnUpdate(World& world, Timestep dt) {}
        virtual void OnLateUpdate(World& world, Timestep dt) {}
        virtual void OnFixedUpdate(World& world) {}
        virtual void OnStop(World& world) {}

    private:
        uint32_t m_Id = UINT32_MAX;
		Registry* m_Registry = nullptr;
    };

}
