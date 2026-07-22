#include "pros/motors.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <system_error>
namespace amp {
	enum motorStats { PORT, EFFICIENCY, SPEED, ROTATION };
	class motor {
	public:
		motor(int port)
		    : item(port) {};

		/*
		 * Sets the motor speed
		 * \param speed
		 *  Speed Value Between -12000 and 12000
		 */
		std::int32_t set(const std::int32_t speed) {
			item.move_voltage(speed);
			return 0;
		}

		/*
		 * Gets a motor statistic
		 * \param stat
		 *   A motorstats enum that determines what numerical statistic to fetch
		 */
		std::int32_t get(motorStats toGet) {
			if (toGet == motorStats::PORT) {
				return item.get_port();
			} else if (toGet == motorStats::EFFICIENCY) {
				// efficciency between 1 and 100
				return std::round(item.get_efficiency() * 100);
			} else if (toGet == motorStats::SPEED) {
				return std::round(100 * (item.get_actual_velocity() /
				                         item.get_target_velocity()));
			}
			throw std::runtime_error("Get Statement Not Found");
			return 1;
		}

	private:
		pros::Motor item;
	};
} // namespace amp