#pragma once
#include "Vector2.h"

namespace AZ
{
	namespace Math {
		const float PI = 3.14159265358979f;
		const float TWO_PI = PI * 2;
		const float HALF_PI = PI * 0.5f;
		const float THREE_HALF_PI = PI * 1.5f;

		inline float rad_to_deg(float radians) {
			return radians * (180 / PI);
		}
		inline float deg_to_rad(float degrees) {
			return degrees * (PI / 180);
		}

		template <typename T>
		inline T Clamp(T v, T min, T max) {
			if (v < min) v = min;
			if (v > max) v = max;

			return v;
		}

		template <>
		inline Vector2 Clamp<Vector2>(Vector2 v, Vector2 min, Vector2 max) {
			v.x = Clamp(v.x, min.x, max.x);
			v.y = Clamp(v.y, min.y, max.y);

			return v;
		}

		template <typename T>
		inline T Lerp(T a, T b, float t) {
			t = Clamp(t, 0.0f, 1.0f);
			return (a + ((b - a) * t));
		}
	}
}