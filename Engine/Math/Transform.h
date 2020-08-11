#pragma once
#include "Vector2.h"
#include "Math/Matrix33.h"

namespace AZ {
	struct Transform {
		Vector2 position;
		float scale{ 1 };
		float angle{ 0 };

		matrix33 matrix;

		Transform() : position(0,0), scale(1), angle(0) {}
		Transform(const Vector2& pos, const float scale = 1, const float angle = 0) : position(pos), scale(scale), angle(angle) {}

		void update();
		void update(const matrix33& mx);

		friend std::istream& operator >> (std::istream& stream, Transform& t);
	};
}