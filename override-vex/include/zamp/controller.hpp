#include "pros/misc.h"
#include "pros/misc.hpp"
#include <cstdint>
namespace amp {
	enum class controllerInteractions {
		STICK_LEFT_X,
		STICK_RIGHT_X,
		STICK_LEFT_Y,
		STICK_RIGHT_Y,
		BUTTON_UP,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_L1,
		BUTTON_L2,
		BUTTON_R1,
		BUTTON_R2
	};
	class controller {
	public:
		controller()
		    : master(pros::E_CONTROLLER_MASTER) {

		    };

		std::int32_t get(controllerInteractions input) {
			switch (input) {
				case controllerInteractions::STICK_LEFT_X:
					return master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

				case controllerInteractions::STICK_RIGHT_X:
					return master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

				case controllerInteractions::STICK_LEFT_Y:
					return master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

				case controllerInteractions::STICK_RIGHT_Y:
					return master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

				case controllerInteractions::BUTTON_UP:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

				case controllerInteractions::BUTTON_DOWN:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

				case controllerInteractions::BUTTON_LEFT:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

				case controllerInteractions::BUTTON_RIGHT:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

				case controllerInteractions::BUTTON_A:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_A);

				case controllerInteractions::BUTTON_B:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_B);

				case controllerInteractions::BUTTON_X:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_X);

				case controllerInteractions::BUTTON_Y:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_Y);

				case controllerInteractions::BUTTON_L1:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

				case controllerInteractions::BUTTON_L2:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

				case controllerInteractions::BUTTON_R1:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

				case controllerInteractions::BUTTON_R2:
					return master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

				default: return 0;
			}
		}
		std::int32_t set(const char* toSet) {
			if (toSet[0] == '.' || toSet[0] == '-') {
				master.rumble(toSet);
			} else {
				master.clear();
				master.set_text(0, 0, toSet);
			}
			return 0;
		}

	private:
		pros::Controller master;
	};
}