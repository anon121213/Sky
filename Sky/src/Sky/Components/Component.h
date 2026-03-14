#pragma once

#include "Skypch.h"
#include "Sky/Core/UUID.h"

namespace Sky {
	class Component {
	public:
		UUID& GetId() { return m_Id; }

	private:
		UUID m_Id;
	};
}