#include "Time.h"

namespace Eero {

	std::shared_ptr<Time::DeltaTimeData> Time::s_DeltaTimeData = std::make_shared<DeltaTimeData>();

	float Time::CalculateDeltaTime(float currentFrame)
	{
		s_DeltaTimeData->DeltaTime = currentFrame - s_DeltaTimeData->LastFrame;
		s_DeltaTimeData->LastFrame = currentFrame;

		return s_DeltaTimeData->DeltaTime;
	}

	int Time::Seconds(float seconds)
	{
		int rawFrameRate = seconds / s_DeltaTimeData->DeltaTime;
		int roundedFrameRate = (((int)rawFrameRate + (5 / 2)) / 5) * 5; // round to nearest 5
		return roundedFrameRate;
	}
}