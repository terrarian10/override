
#pragma once
#include "pros/rotation.hpp"
#include <cmath>
namespace amp {
	// Odo meter y
	class odometryWheel {
	public:
		odometryWheel(int rotationSensor,
		              std::double_t wheel_size,
		              std::double_t offset)
		    : rotationSensor(rotationSensor)
		    , wheel_size(wheel_size)
		    , offset(offset) {};
		double rotToCm() {
			return (double(rotationSensor.get_position()) / 36000.0) *
			       (M_PI * wheel_size); // CM From rotation amount
		}
		void reset() { rotationSensor.reset_position(); } // Resets it
		std::double_t getOffset() { return offset; } // Gets the current offset

	private:
		pros::Rotation rotationSensor;
		std::double_t wheel_size;
		std::double_t offset;
	};
}