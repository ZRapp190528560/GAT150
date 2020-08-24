#pragma once
#include "RenderComponent.h"
#include <string>

namespace AZ {
	class spriteComponent : public renderComponent {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() override { return new spriteComponent(*this); }

		void read(const rapidjson::Value& value);

		virtual void update() override;
		virtual void draw() override;

	protected:
		AZ::Vector2 m_origin{ 0,0 };
		std::string m_textureName;
		SDL_Rect m_rect{ 0,0,0,0 };
	};
}