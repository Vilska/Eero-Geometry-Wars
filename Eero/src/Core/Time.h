#pragma once

#include <memory>

namespace Eero {

	class Time {
	public:
		static float CalculateDeltaTime(float currentFrame);

		static int Seconds(float seconds);
	private:
		struct DeltaTimeData
		{
			float DeltaTime, LastFrame;
		};

		static std::shared_ptr<DeltaTimeData> s_DeltaTimeData;
	};

}
