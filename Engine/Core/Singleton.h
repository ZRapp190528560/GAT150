#pragma once

namespace AZ {
	template <typename T>
	class singleton {
	public:
		singleton(const singleton&) = delete;
		singleton& operator = (const singleton&) = delete;

		static T& instance() {
			static T s_instance;
			return s_instance;
		}

	protected:
		singleton() {}
	};
}