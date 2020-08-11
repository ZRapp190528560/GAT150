#pragma once
#include <string>

namespace AZ {
	class resource {
	public:
		virtual bool create(const std::string& name, void* data = nullptr) = 0;
		virtual void destroy() = 0;
	};
}