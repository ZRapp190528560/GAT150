#include "pch.h"
#include "Color.h"

const AZ::Color AZ::Color::red{ 1, 0, 0 };
const AZ::Color AZ::Color::blue{ 0, 0, 1 };
const AZ::Color AZ::Color::green{ 0, 1, 0 };
const AZ::Color AZ::Color::yellow{ 1, 1, 0 };
const AZ::Color AZ::Color::magenta{ 1, 0, 1 };
const AZ::Color AZ::Color::cyan{ 0, 1, 1 };
const AZ::Color AZ::Color::white{ 1, 1, 1 };

namespace AZ {
	std::istream& operator >> (std::istream& stream, Color& c) {
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos) {
			std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			c.r = std::stof(cr);

			line = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);

			std::string cg = line.substr(0, line.find(","));
			c.g = std::stof(cr);

			std::string cb = line.substr(line.find(",") + 1, line.find("}") - 1);
			c.b = std::stof(cb);
		}

		return stream;
	}

}