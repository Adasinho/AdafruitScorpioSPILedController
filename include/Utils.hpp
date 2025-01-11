#ifndef UTILS_HPP
#define UTILS_HPP

#include "StripId.hpp"

class Utils {
public:
	static bool validStripId(int valueToValid) {
		const int LAST_STRIP_NUMBER = static_cast<int>(StripId::STRIP_MAX);
		const bool IS_GREATER_THAT_THE_MINIMUM = (valueToValid >= 0);
		const bool IS_LOWER_THAT_THE_MAXIMUM = (valueToValid < LAST_STRIP_NUMBER);

		return (IS_GREATER_THAT_THE_MINIMUM && IS_LOWER_THAT_THE_MAXIMUM);
	}
};

#endif // UTILS_HPP