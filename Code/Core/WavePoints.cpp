#include "WavePoints.h"

WavePoints::WavePoints(unsigned int size) : std::vector<double>(size)
{
}

WavePoints::WavePoints(const WavePoints & toCopy) : WavePoints(toCopy.size())
{
	for (unsigned int i = 0; i < toCopy.size(); i++)
	{
		this->at(i) = toCopy.at(i);
	}
}

WavePoints::~WavePoints()
{
}
