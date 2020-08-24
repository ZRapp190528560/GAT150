#pragma once
#include "SpriteComponent.h"

namespace AZ {
	class spriteAnimationComponent : public spriteComponent {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() override { return new spriteAnimationComponent(*this); }

		void read(const rapidjson::Value& value);

		virtual void update() override;

	protected:
		int m_frame{ 0 };
		float m_frameTimer{ 0 };
		float m_frameRate{ 0 };

		int m_numX{ 0 };
		int m_numY{ 0 };
		int m_numFrames{ 0 };
		int m_fps{ 0 };
	};
}