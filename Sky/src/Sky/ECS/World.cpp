#include <skypch.h>

#include "World.h"

namespace Sky
{
	void World::RemoveSystem(const System& system)
	{
		m_Systems.erase(system.GetId());
	}

	void World::OnAwake()
	{
		for (auto& [id, system] : m_Systems)
			system->OnAwake(*this);
	}

	void World::OnStart()
	{
		for (auto& [id, system] : m_Systems)
			system->OnStart(*this);
	}

	void World::OnUpdate(const Timestep dt)
	{
		for (auto& [id, system] : m_Systems)
			system->OnUpdate(*this, dt);
	}

	void World::OnLateUpdate(const Timestep dt)
	{
		for (auto& [id, system] : m_Systems)
			system->OnLateUpdate(*this, dt);
	}

	void World::OnFixedUpdate()
	{
		for (auto& [id, system] : m_Systems)
			system->OnFixedUpdate(*this);
	}

	void World::OnStop()
	{
		for (auto& [id, system] : m_Systems)
			system->OnStop(*this);
	}
}
