#pragma once

#include <windows.h>

namespace AZ {
	struct Color {
		float r, g, b, a;

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {};
		Color(float r, float g, float b, float a = 1) : r{ r }, g{ g }, b{ b }, a{ a } {};

		float& operator [] (size_t index) {
			switch (index)
			{
			case (1):
				return r;
			case (2):
				return g;
			case (3):
				return b;
			default:
				break;
			}
		}
		const float& operator [] (size_t index) const {
			switch (index)
			{
			case (1):
				return r;
			case (2):
				return g;
			case (3):
				return b;
			default:
				break;
			}
		}


		void Set(float r, float g, float b) { 
			this->r = r; 
			this->g = g; 
			this->b = b;
		}

		Color operator + (const Color& c) const { return {r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return { r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return { r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return { r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return { r + s, g + s, b + s }; }
		Color operator - (float s) const { return { r - s, g - s, b - s }; }
		Color operator * (float s) const { return { r * s, g * s, b * s }; }
		Color operator / (float s) const { return { r / s, g / s, b / s }; }

		Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }

		Color& operator += (float s) { r += s; g += s; b += s; return *this; }
		Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
		Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
		Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

		friend std::istream& operator >> (std::istream& stream, Color& c);

		SDL_Colour pack888() const;

		operator SDL_Colour() const { return pack888(); }

		static const Color red;
		static const Color blue;
		static const Color green;
		static const Color yellow;
		static const Color magenta;
		static const Color cyan;
		static const Color white;
	};

	inline SDL_Colour Color::pack888() const {
		SDL_Colour colour;
		colour.r = static_cast<BYTE>(r * 255.0);
		colour.g = static_cast<BYTE>(g * 255.0);
		colour.b = static_cast<BYTE>(b * 255.0);

		return colour;
	}
}
