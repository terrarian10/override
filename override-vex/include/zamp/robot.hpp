#pragma once
#include "pros/motors.hpp"
#include "zamp/chassis.hpp"
#include "zamp/consts.hpp"
#include "zamp/motor.hpp"
#include "zamp/object.hpp"
#include <vector>
namespace amp {
	// Robot
	class robot {
	public:
		// Init robot
		explicit robot(amp::chassis& chassis, std::vector<amp::object>& mechs)
		    : chassis(chassis)
		    , mechs(mechs) {}
		// Tank drive
		void tank_drive(int left, int right) {
			chassis.addVolts(12000, 12000);
			chassis.tank(left, right);
		}
		// Set state
		// Which calls the mechanisms,,, set state... oh wow this is so much
		// code to do so little
		void setState(std::string mech, std::string state) {
			for (auto& m : mechs) {
				if (m.getName() == mech) { m.setState(state); }
			}
		}
		// WEEEEEEEEEEE speeeed
		void moveToPose(amp::pose poseTo, amp::moveSettings settings) {
			chassis.addVolts(12000, 12000);

			chassis.driveTo(poseTo, settings);
		}

		// Take planned movements n make em real
		void updateBot() {
			for (auto& mot : chassis.getMotors()) {
				pros::Motor(mot.first).move_voltage(mot.second);
			}
			for (auto& obj : mechs) {
				for (auto& section : obj.motors) {
					for (auto& mot : section.second) {
						mot.setObject();
					};
				}
				for (auto& airG : obj.airs) {
					for (auto& air : airG.second) {
						air.setObject();
					}
				}
			}
		}

		// Getters
		amp::pose getPose() { return chassis.getPos(); }

		// Tickers
		void tickOdom() { chassis.odomTick(); }

	private:
		amp::chassis& chassis;
		std::vector<amp::object>& mechs;
	};
}