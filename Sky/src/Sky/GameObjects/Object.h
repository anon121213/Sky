#pragma once

#include "Sky/Core/UUID.h"

namespace Sky {
	class Object {
	public:
		static const UUID& GetGuid() { return m_Guid; }

	private:
		static UUID m_Guid;
	};
}