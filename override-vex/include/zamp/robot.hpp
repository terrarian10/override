#pragma once
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "zamp/chassis.hpp"
#include "zamp/object.hpp"
#include <cstdint>
#include <vector>
namespace amp {
	class robot {
	public:
		explicit robot(std::vector<int> mots,
		               std::vector<std::pair<std::uint8_t, std::uint8_t>> airs,
		               amp::chassis& chassis,
		               std::vector<amp::object>& mechs)
		    : chassis(chassis)
		    , mechs(mechs) {}

		void tank_drive(int left, int right) {
			chassis.addVolts(12000, 12000);
			chassis.tank(left, right);
		}
		void updateBot() {
			for (auto& mot : chassis.getMotors()) {
				pros::Motor(mot.first).move_voltage(mot.second);
			}
			for (auto& obj : mechs) {
				for (auto& mot : obj.getMotors()) {
					pros::Motor(mot.first).move_voltage(mot.second);
				}
				for (auto& airG : obj.getAirs()) {
					pros::adi::DigitalOut([&]() {
						if (airG.first.second != 255) {
							return pros::adi::DigitalOut(airG.first);
						}
						return pros::adi::DigitalOut(airG.first.first);
					}())
					    .set_value(airG.second);
				}
			}
		}
		void updateSensorData() { chassis.odomTick(); }

	private:
		amp::chassis& chassis;
		std::vector<amp::object>& mechs;
	};
}