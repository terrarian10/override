#pragma once
#include "pros/misc.h"
#include <list>
namespace amp {
	const std::list<pros::controller_digital_e_t> digital_buttons = {
		pros::E_CONTROLLER_DIGITAL_A,    pros::E_CONTROLLER_DIGITAL_L1,
		pros::E_CONTROLLER_DIGITAL_R2,   pros::E_CONTROLLER_DIGITAL_RIGHT,
		pros::E_CONTROLLER_DIGITAL_X,    pros::E_CONTROLLER_DIGITAL_Y,
		pros::E_CONTROLLER_DIGITAL_L2,   pros::E_CONTROLLER_DIGITAL_LEFT,
		pros::E_CONTROLLER_DIGITAL_R1,   pros::E_CONTROLLER_DIGITAL_UP,
		pros::E_CONTROLLER_DIGITAL_DOWN, pros::E_CONTROLLER_DIGITAL_B
	};
	struct motionSettings {
		int timeout = 5000;
		int iterations = 300;
		double maxVolt = 12000;
	};
}