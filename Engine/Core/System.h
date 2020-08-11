#pragma once

namespace AZ {
	class system {
	public:
		virtual bool startup() = 0;
		virtual void shutdown() = 0;
		virtual void update() = 0;
	};
}