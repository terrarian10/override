#include "zamp/sensors.hpp"
#include <cmath>
#include <cstdint>
namespace amp {
	class odometryWheel {
	public:
		odometryWheel(amp::rotation& rotationSensor, std::double_t wheel_size)
		    : rotationSensor(rotationSensor)
		    , wheel_size(wheel_size) {};
		std::int32_t rotToCm() {
			return double(rotationSensor.get()) / 36000 * wheel_size;
		}

	private:
		amp::rotation& rotationSensor;
		std::double_t wheel_size;
	};
}