#pragma once
#include "Resource/resource.h"
#include "AudioChannel.h"
#include <fmod.hpp>

namespace AZ{
	class sound : public resource{
	public:
		virtual bool create(const std::string& name, void* data = nullptr) override;
		virtual void destroy() override;

		audioChannel play(bool loop = false);

	private:
		FMOD::System* m_system{ nullptr };
		FMOD::Sound* m_sound{ nullptr };
	};
}

