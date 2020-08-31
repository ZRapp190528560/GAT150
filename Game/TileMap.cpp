#include "pch.h"
#include "TileMap.h"
#include "Object/Scene.h"
#include "Object/GameObject.h"
#include "Object/ObjectFactory.h"

namespace AZ {
	void tileMap::read(const rapidjson::Value& value){
		AZ::json::Get(value, "numX", m_numX);
		AZ::json::Get(value, "numY", m_numY);
		AZ::json::Get(value, "size", m_size);
		AZ::json::Get(value, "start", m_start);
		AZ::json::Get(value, "tileNames", m_tileNames);
		AZ::json::Get(value, "tiles", m_tiles);
	}

	bool tileMap::create(AZ::scene* scene){
		for (size_t i = 0; i < m_tiles.size(); i++) {
			int index = m_tiles[i];
			if (index) {
				gameObject* gameObject = objectFactory::instance().create<AZ::gameObject>(m_tileNames[index]);

				float x = i % m_numX;
				float y = i / m_numX;
				gameObject->m_transform.position = m_start + Vector2{ x, y } * m_size;
				scene->addGameObject(gameObject);
			}
		}
		return false;
	}
}
