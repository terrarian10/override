#include "pros/imu.hpp"
#include "pros/rotation.hpp"
#include <cstdint>
namespace amp {
	class rotation {
	public:
		rotation(int port)
		    : thing(port) {};
		std::int32_t get() { return thing.get_position(); }
		std::int32_t reset() { return thing.reset(); }
		std::int32_t set(std::int32_t pos) { return thing.set_position(pos); }

	private:
		pros::Rotation thing;
	};

	class imu {
	public:
		imu(int port)
		    : thing(port) {}

	private:
		pros::IMU thing;
	};
}