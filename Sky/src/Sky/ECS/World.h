#pragma once
#include <skypch.h>
#include "System.h"
#include "Sky/Core/Timestep.h"

namespace Sky
{
	class World
	{
	public:
        template<typename T, typename... Args>
        T& AddSystem(Args&&... args) {
            uint32_t id = m_NextSystemId++;
            auto system = CreateScope<T>(std::forward<Args>(args)...);
            system->Construct(id, &m_Registry);
            T& ref = *system;
            m_Systems[id] = std::move(system);
            return ref;
        }

        void RemoveSystem(const System& system);

        void OnAwake();
        void OnStart();
        void OnUpdate(Timestep dt);
        void OnLateUpdate(Timestep dt);
        void OnFixedUpdate();
        void OnStop();

		Registry& GetRegistry() { return m_Registry; }

    private:
        std::unordered_map<uint32_t, Scope<System>> m_Systems;
        uint32_t m_NextSystemId = 0;
		Registry m_Registry;
	};
}
