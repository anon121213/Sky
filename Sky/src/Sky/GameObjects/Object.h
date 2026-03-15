#pragma once

#include "Sky/Core/UUID.h"

namespace Sky {
	class Object {
	public:
		const UUID& GetGuid() { return m_Guid; }

	private:
		UUID m_Guid;
	};
}