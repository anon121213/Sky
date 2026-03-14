#pragma once

#include "skypch.h"
#include "Object.h"
#include "Sky/Core/Timestep.h"

namespace Sky {

	class ObjectsContainer 
	{
	public:
		virtual void AddObject(Object& go) const = 0;
		virtual void RemoveObject(Object & go) const = 0;
		virtual void RemoveObject(UUID& id) const = 0;

		virtual void OnUpdate(const Timestep ts) const = 0;
	};

}