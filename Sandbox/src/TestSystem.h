#pragma once

#include <Sky.h>

#include "Sky/ECS/System.h"

class TestSystem : public Sky::System
{
public:
	void OnAwake(Sky::World& world) override;
	void OnUpdate(Sky::World& world, Sky::Timestep dt) override;
};