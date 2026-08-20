#include "pros/rotation.hpp"
#include "zamp/consts.hpp"
#include <cmath>
namespace amp {
	class odometryWheel {
	public:
		odometryWheel(pros::Rotation& rotationSensor,
		              std::double_t wheel_size,
		              std::double_t offset)
		    : rotationSensor(rotationSensor)
		    , wheel_size(wheel_size)
		    , offset(offset) {};
		double rotToCm() {
			return (double(rotationSensor.get_position()) / 36000.0) *
			       (M_PI * wheel_size);
		}
		void reset() { rotationSensor.reset_position(); }
		std::double_t getOffset() { return offset; }

	private:
		pros::Rotation& rotationSensor;
		std::double_t wheel_size;
		std::double_t offset;
	};
}