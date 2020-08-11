#pragma once
#include "Vector2.h"

namespace AZ {
	struct matrix22 {
		float matrix[2][2]; //column row
		//m[0][0] m[1][0]
		//m[0][1] m[1][1]

		matrix22() = default;
		matrix22(const Vector2& column1, const Vector2& column2) {
			matrix[0][0] = column1[0];  matrix[1][0] = column2[0];
			matrix[0][1] = column1[1]; matrix[1][1] = column2[1];
		}

		void scale(float s) {
			matrix[0][0] = s; matrix[1][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = s;
		}	
		void scale(float sx, float sy) {
			matrix[0][0] = sx; matrix[1][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = sy;
		}
		void scale(const Vector2& s) {
			matrix[0][0] = s.x; matrix[1][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = s.y;
		}

		void rotate(float angle) {
			matrix[0][0] = std::cos(angle); matrix[1][0] = std::sin(angle);
			matrix[0][1] = -std::sin(angle); matrix[1][1] = std::cos(angle);
		}

		void SetIdentity() {
			matrix[0][0] = 1; matrix[1][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = 1;
		}

		matrix22 operator * (const matrix22& m2) {
			matrix22 result;

			result.matrix[0][0] = matrix[0][0] * m2.matrix[0][0] + matrix[1][0] * m2.matrix[0][1];
			result.matrix[1][0] = matrix[0][0] * m2.matrix[1][0] + matrix[1][0] * m2.matrix[1][1];
			result.matrix[0][1] = matrix[0][1] * m2.matrix[0][0] + matrix[1][1] * m2.matrix[0][1];
			result.matrix[1][1] = matrix[0][1] * m2.matrix[1][0] + matrix[1][1] * m2.matrix[1][1];

			return result;
		}

		Vector2 operator * (const Vector2& v) {
			Vector2 result;

			result.x = v.x * matrix[0][0] + v.y * matrix[0][1];
			result.y = v.x * matrix[1][0] + v.y * matrix[1][1];

			return result;
		}

		friend Vector2 operator * (const Vector2& v, const matrix22& m) {
			Vector2 result;

			result.x = v.x * m.matrix[0][0] + v.y * m.matrix[0][1];
			result.y = v.x * m.matrix[1][0] + v.y * m.matrix[1][1];

			return result;
		}
	};
}