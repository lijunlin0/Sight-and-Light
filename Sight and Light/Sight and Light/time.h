#pragma once
#include<chrono>
class time
{
public:
	static long long update_ms;
	static const long long frame_ms = 17;

	static long long current_time()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
};
