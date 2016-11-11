#ifndef __H_WAVE_POINTS
#define __H_WAVE_POINTS

#include <vector>

/**
 * Base class for storing discretized points.
 * @author Mateusz Gasior
 */
class WavePoints : public std::vector<double>
{
public:
	/**
	 * Overridden construtor that reserves given amount of elements.
	 * @param size Amount of element to be reserved by vector.
	 */
	WavePoints(unsigned int size);

	/**
	 * Overridden copy construtor based on another wave.
	 * @param toCopy wave to copy.
	 */
	WavePoints(const WavePoints& toCopy);

	/**
	 * Default destructor.
	 */
	~WavePoints();
};

#endif
