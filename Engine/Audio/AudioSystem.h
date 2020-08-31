#pragma once
#include "Core/System.h"
#include <fmod.hpp>

namespace AZ {
	class audioSystem : public system{
	public:
		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		friend class sound;

	protected:
		FMOD::System* m_system{ nullptr };
	};
}

