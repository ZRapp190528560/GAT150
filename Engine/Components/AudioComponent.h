#pragma once
#include "Component.h"
#include "Audio/AudioChannel.h"

namespace AZ{
	class audioComponent : public component{
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() const override { return new audioComponent{ *this }; }

		void read(const rapidjson::Value& value) override;

		virtual void update() override;

		void play();
		void stop();
		void setSoundName(const std::string& soundName) { m_soundName = soundName; }

	protected:
		std::string m_soundName;
		bool m_loop{ false };
		bool m_playOnAwake{ false };

		audioChannel m_channel;
	};
}