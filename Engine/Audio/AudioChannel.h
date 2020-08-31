#pragma once
#include <fmod.hpp>

namespace AZ {
	class audioChannel
	{
	public:
		audioChannel() = default;
		audioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool isPlaying();
		void stop();

	protected:
		FMOD::Channel* m_channel{ nullptr };
	};
}