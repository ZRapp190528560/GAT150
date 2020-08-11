#include "pch.h"
#include <string>
#include "Transform.h"


namespace AZ {
	std::istream& AZ::operator>>(std::istream& stream, Transform& t){
		stream >> t.position;

		std::string line;
		std::getline(stream, line);
		t.scale = stof(line);

		std::getline(stream, line);
		t.angle = stof(line);

		return stream;                
	}
	void Transform::update(){
		matrix33 mxScale;
		mxScale.scale(scale);

		matrix33 mxRotate;
		mxRotate.rotate(angle);

		matrix33 mxTranslate;
 		mxTranslate.translate(position);

		matrix = mxScale * mxRotate * mxTranslate;
	}
	void Transform::update(const matrix33& mx){
		update();
		matrix = matrix * mx;
	}
}
