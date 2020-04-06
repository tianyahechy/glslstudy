#pragma once
#include <Windows.h>
namespace CELL
{
	class lifeiTimeStamp
	{
	private:
		LARGE_INTEGER	_frequency;
		LARGE_INTEGER	_startCount;
	public:
		lifeiTimeStamp()
		{
			QueryPerformanceFrequency(&_frequency);
			QueryPerformanceCounter(&_startCount);
		}
		~lifeiTimeStamp()
		{
			QueryPerformanceCounter(&_startCount);
		}
		void update()
		{
			QueryPerformanceCounter(&_startCount);
		}
		//��ȡ΢��
		double getElapsedTimeInMicroSec()
		{
			LARGE_INTEGER endCount;
			QueryPerformanceCounter(&endCount);
			double startTimeInMicroSec = _startCount.QuadPart * (1000000.0 / _frequency.QuadPart);
			double endTimeInMicroSec = endCount.QuadPart * (1000000.0 / _frequency.QuadPart);
			return endTimeInMicroSec - startTimeInMicroSec;
		}
		//��ȡ����
		double getElapsedTimeInMilliSec()
		{
			return this->getElapsedTimeInMicroSec() * 0.001;
		}
		//��ȡ��ǰ��
		double getElapsedSecond()
		{
			return this->getElapsedTimeInMicroSec() * 0.000001;
		}
		
	};
}
