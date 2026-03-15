#pragma once

#include "Skypch.h"
#include "Sky/Core/UUID.h"

namespace Sky {
	class Component {
	public:
		virtual ~Component() = default;

		const UUID& GetId() { return m_Id; }
	private:
		UUID m_Id;
	};
}