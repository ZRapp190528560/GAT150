#include "pch.h"
#include "Texture.h"
#include "Graphics/Renderer.h"

bool AZ::texture::create(const std::string& name, void* _renderer) {
	m_renderer = static_cast<renderer*>(_renderer)->m_renderer;

	SDL_Surface* surface = IMG_Load(name.c_str());
	if (!surface) {
		return false;
	}
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	if (m_texture == nullptr) {
		return false;
	}

	return true;
}
void AZ::texture::destroy() {
	SDL_DestroyTexture(m_texture);
}

void AZ::texture::draw(const Vector2& position, const Vector2& scale, float angle) {
	Vector2 size = getSize();
	size *= scale;

	SDL_Rect rect;
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = static_cast<int>(size.x);
	rect.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

void AZ::texture::draw(const SDL_Rect& source, const Vector2& position, const Vector2& scale, float angle) {
	Vector2 size = { source.w, source.h };
	size *= scale;

	SDL_Rect rect;
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = static_cast<int>(size.x);
	rect.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(m_renderer, m_texture, &source, &rect, angle, nullptr, SDL_FLIP_NONE);
}

AZ::Vector2 AZ::texture::getSize()
{
	int w, h;
	SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);

	return { w, h };
}
