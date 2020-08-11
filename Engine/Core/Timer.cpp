#include "pch.h"
#include "Timer.h"

namespace AZ {
	void timer::reset()	{
		m_timePoint = clock::now();
	}

	timer::clock::rep AZ::timer::elapsedTicks()	{
		clock_duration duration = (clock::now() - m_timePoint);

		return duration.count();
	}

	timer::clock::rep AZ::timer::ticksPerSecond() {
		return clock_duration::period::den;
	}

	double timer::elapsedSeconds(){
		return elapsedTicks() / static_cast<double>(ticksPerSecond());
	}

	void frameTimer::tick(){
		m_dt = elapsedSeconds();
		m_timePoint = clock::now();
	}
}
