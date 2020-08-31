#pragma once
#include "Core/Json.h"
#include "Math/Vector2.h"
#include <vector>

namespace AZ {
	class scene;
	class tileMap {
	public:
		void read(const rapidjson::Value& value);
		bool create(scene* scene);

	protected:
		int m_numX{ 0 };
		int m_numY{ 0 };
		Vector2 m_size;
		Vector2 m_start;
		std::vector<std::string> m_tileNames;
		std::vector<int> m_tiles;
	};
}