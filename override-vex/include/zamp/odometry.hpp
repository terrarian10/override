#include "zamp/consts.hpp"
#include "zamp/sensors.hpp"
#include <cmath>
namespace amp {
	class odometryWheel {
	public:
		odometryWheel(amp::rotation& rotationSensor,
		              std::double_t wheel_size,
		              std::double_t offset)
		    : rotationSensor(rotationSensor)
		    , wheel_size(wheel_size)
		    , offset(offset) {};
		double rotToCm() {
			return (double(rotationSensor.get()) / 36000.0) *
			       (M_PI * wheel_size);
		}
		std::double_t getOffset() { return offset; }

	private:
		amp::rotation& rotationSensor;
		std::double_t wheel_size;
		std::double_t offset;
	};
}