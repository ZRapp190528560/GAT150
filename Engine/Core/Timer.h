#pragma once
#include <chrono>

namespace AZ {
	class timer {
	public:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = std::chrono::duration<clock::rep, std::nano>;
	public:
		timer() : m_timePoint(clock::now()) {}

		void reset();
		clock::rep elapsedTicks();
		clock::rep ticksPerSecond();

		double elapsedSeconds();

	protected:
		clock::time_point m_timePoint;
	};

	class frameTimer : public timer {
	public:
		void tick();
		float deltaTime() { return m_dt; }

	protected:
		float m_dt{ 0.0f };
	};
}