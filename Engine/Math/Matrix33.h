#pragma once
#include "Vector2.h"

namespace AZ {
	struct matrix33 {
		float matrix[3][3]; //column row
		/*m[0][0] m[1][0] m[2][0]
		m[0][1] m[1][1] m[2][0]
		m[0][2] m[1][2] m[2][2]*/

		void scale(float s) {
			matrix[0][0] = s; matrix[1][0] = 0; matrix[2][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = s; matrix[2][1] = 0;
			matrix[0][2] = 0; matrix[1][2] = 0; matrix[2][2] = 1;
		}
		void scale(float sx, float sy) {
			matrix[0][0] = sx; matrix[1][0] = 0; matrix[2][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = sy; matrix[2][1] = 0;
			matrix[0][2] = 0; matrix[1][2] = 0; matrix[2][2] = 1;
		}
		void scale(const Vector2& s) {
			matrix[0][0] = s.x; matrix[1][0] = 0; matrix[2][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = s.y; matrix[2][1] = 0;
			matrix[0][2] = 0; matrix[1][2] = 0; matrix[2][2] = 1;
		}

		void rotate(float angle) {
			matrix[0][0] = std::cos(angle); matrix[1][0] = std::sin(angle); matrix[2][0] = 0;
			matrix[0][1] = -std::sin(angle); matrix[1][1] = std::cos(angle); matrix[2][1] = 0;
			matrix[0][2] = 0; matrix[1][2] = 0; matrix[2][2] = 1;
		}

		void translate(const Vector2& v) {
			matrix[0][0] = 1; matrix[1][0] = 0; matrix[2][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = 1; matrix[2][1] = 0;
			matrix[0][2] = v.x; matrix[1][2] = v.y; matrix[2][2] = 1;
		}

		Vector2 getPosition() const {
			return { matrix[0][2], matrix[1][2] };
		}

		Vector2 getScale() const {
			return { matrix[0][0], matrix[1][1] };
		}

		float getAngle() const {
			return std::atan2(matrix[1][0], matrix[0][0]);
		}

		void SetIdentity() {
			matrix[0][0] = 1; matrix[1][0] = 0; matrix[2][0] = 0;
			matrix[0][1] = 0; matrix[1][1] = 1; matrix[2][1] = 0;
			matrix[0][2] = 0; matrix[1][2] = 0; matrix[2][2] = 1;
		}

		matrix33 operator * (const matrix33& m2) {
			matrix33 result;

			result.matrix[0][0] = matrix[0][0] * m2.matrix[0][0] + matrix[1][0] * m2.matrix[0][1] + matrix[2][0] * m2.matrix[0][2];
			result.matrix[0][1] = matrix[0][1] * m2.matrix[0][0] + matrix[1][1] * m2.matrix[0][1] + matrix[2][1] * m2.matrix[0][2];
			result.matrix[0][2] = matrix[0][2] * m2.matrix[0][0] + matrix[1][2] * m2.matrix[0][1] + matrix[2][2] * m2.matrix[0][2];

			result.matrix[1][0] = matrix[0][0] * m2.matrix[1][0] + matrix[1][0] * m2.matrix[1][1] + matrix[2][0] * m2.matrix[1][2];
			result.matrix[1][1] = matrix[0][1] * m2.matrix[1][0] + matrix[1][1] * m2.matrix[1][1] + matrix[2][1] * m2.matrix[1][2];
			result.matrix[1][2] = matrix[0][2] * m2.matrix[1][0] + matrix[1][2] * m2.matrix[1][1] + matrix[2][2] * m2.matrix[1][2];
			
			result.matrix[2][0] = matrix[0][0] * m2.matrix[2][0] + matrix[1][0] * m2.matrix[2][1] + matrix[2][0] * m2.matrix[2][2];
			result.matrix[2][1] = matrix[0][1] * m2.matrix[2][0] + matrix[1][1] * m2.matrix[2][1] + matrix[2][1] * m2.matrix[2][2];
			result.matrix[2][2] = matrix[0][2] * m2.matrix[2][0] + matrix[1][2] * m2.matrix[2][1] + matrix[2][2] * m2.matrix[2][2];

			return result;
		}

		Vector2 operator * (const Vector2& v) {
			Vector2 result;

			result.x = v.x * matrix[0][0] + v.y * matrix[0][1] + matrix[0][2];
			result.y = v.x * matrix[1][0] + v.y * matrix[1][1] + matrix[1][2];

			return result;
		}

		friend Vector2 operator * (const Vector2& v, const matrix33& m) {
			Vector2 result;

			result.x = v.x * m.matrix[0][0] + v.y * m.matrix[0][1] + m.matrix[0][2];
			result.y = v.x * m.matrix[1][0] + v.y * m.matrix[1][1] + m.matrix[1][2];

			return result;
		}
	};
}
