#pragma once
#include "pros/motors.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
namespace amp {
	enum class motorStats { PORT, EFFICIENCY, SPEED, ROTATION };
	class motor {
	public:
		motor(int port)
		    : item(port)
		    , voltage(0) {};

		/*
		 * Sets the motor speed
		 * \param speed
		 *  Speed Value Between -12000 and 12000
		 */
		std::int32_t set(const std::int32_t speed) {
			voltage = speed;
			return 0;
		}
		std::int32_t setObject() {
			item.move_voltage(voltage);
			return 0;
		}
		std::int32_t getAppliedVoltage() { return voltage; }

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
				// Speed as percent between 0 and 100
				return std::round(100 * (item.get_actual_velocity() /
				                         item.get_target_velocity()));
			} else if (toGet == motorStats::ROTATION) {
				// Return motors relative rotation
				return std::round(item.get_position());
			}
			throw std::runtime_error("Get Statement Not Found");
			return 1;
		}

	private:
		pros::Motor item;
		int32_t voltage;
	};
} // namespace amp