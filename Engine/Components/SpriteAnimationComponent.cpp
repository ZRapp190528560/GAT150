#include "pch.h"
#include "SpriteAnimationComponent.h"
#include "Texture.h"

namespace AZ {
	bool spriteAnimationComponent::create(void* data) {
		m_owner = static_cast<gameObject*>(data);
		return true;
	}

	void spriteAnimationComponent::destroy() {
	}

	void spriteAnimationComponent::read(const rapidjson::Value& value) {
		spriteComponent::read(value);

		json::Get(value, "numX", m_numX);
		json::Get(value, "numY", m_numY);
		json::Get(value, "numFrames", m_numFrames);
		json::Get(value, "fps", m_fps);

		m_frameRate = 1.0f / m_fps;
	}

	void spriteAnimationComponent::update() {
		m_frameTimer += m_owner->m_engine->getTimer().deltaTime();
		if (m_frameTimer >= m_frameRate){
			m_frameTimer = 0;
			m_frame++;
			if (m_frame >= m_numFrames) m_frame = 0;
		}

		texture* texture = m_owner->m_engine->getSystem<AZ::resourceManager>()->get<AZ::texture>(m_textureName, m_owner->m_engine->getSystem<AZ::renderer>());
		Vector2 textureSize = texture->getSize();
		Vector2 cellSize = textureSize / Vector2{ m_numX, m_numY };

		m_rect.x = static_cast<int>((m_frame % m_numX) * cellSize.x);
		m_rect.y = static_cast<int>((m_frame / m_numX) * cellSize.y);
		m_rect.w = static_cast<int>(cellSize.x);
		m_rect.h = static_cast<int>(cellSize.y);
	}
}
