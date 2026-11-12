#pragma once
#include "odometry.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "zamp/consts.hpp"
#include "zamp/math.hpp"
#include "zamp/motor.hpp"
#include <cstdint>
#include <map>
#include <numbers>
#include <optional>
#include <vector>
namespace amp {
	// All the sensors that are important to the chassis
	struct chassisSensors {
		odometryWheel vertical;
		odometryWheel horizontal;
		pros::Imu imu;
		// Distance sensors for maybe global positioning later
		std::optional<pros::Distance> front;
		std::optional<pros::Distance> front_2;
		std::optional<pros::Distance> right;
		std::optional<pros::Distance> right_2;
		std::optional<pros::Distance> left;
		std::optional<pros::Distance> left_2;
	};

	// Math thing for determining when robot stops
	struct motionController {
		const double lateralKP = 3.0;
		const double lateralKD = 10.0;
		const double angularKP = 50.0;
		const double angularKD = 5.0;
	};

	// Actual chassis object
	class chassis {
	public:
		explicit chassis(std::vector<amp::motor>& leftWheels,
		                 std::vector<amp::motor>& rightWheels,
		                 chassisSensors& chassisSensors,
		                 motionController moveCtrl)
		    : leftWheels(leftWheels)
		    , rightWheels(rightWheels)
		    , chassisSensors(chassisSensors)
		    , moveCtrl(moveCtrl) {

		    };

		// Getters, obtain useful information
		amp::pose getPos() { return pos; }
		amp::motionController getCtrl() { return moveCtrl; }

		// Tank Drive command, multiplies both sides of DT by given value
		int tank(std::int32_t left, std::int32_t right) {
			for (auto& i : leftWheels) {
				i.mod(left);
			}
			for (auto& i : rightWheels) {
				i.mod(right);
			}
			return 0;
		}

		// Tank drive but with pair initializer
		int tank(std::pair<int, int> vals) {
			for (auto& i : leftWheels) {
				i.mod(vals.first);
			}
			for (auto& i : rightWheels) {
				i.mod(vals.second);
			}
			return 0;
		}

		// Add a set amount of volts to both sides of the DT
		int addVolts(std::int32_t left, std::int32_t right) {
			for (auto& i : leftWheels) {
				i.set(left);
			}
			for (auto& i : rightWheels) {
				i.set(right);
			}
			return 0;
		}

		// Arcade drivestyle, tank but one is forward/back other is turn
		int arcade(std::int32_t forward, std::int32_t turn) {
			for (auto& i : leftWheels) {
				i.mod(forward - turn);
			}
			for (auto& i : rightWheels) {
				i.mod(forward + turn);
			}
			return 0;
		}

		// Returns ports and speeds
		std::map<int, int> getMotors() {
			std::map<int, int> toRet;
			for (auto& motor : leftWheels) {
				toRet[motor.get(motorStats::PORT)] =
				    motor.get(motorStats::SPEED);
			}
			for (auto& motor : rightWheels) {
				toRet[motor.get(motorStats::PORT)] =
				    motor.get(motorStats::SPEED);
			}
			return toRet;
		}

		// Sets the chassis pose
		int resetPos(amp::pose setPos) {
			pos = setPos;
			return 0;
		}

		// Modifies the chassis pose
		int modifyPos(amp::pose addPos) {
			pos.x += addPos.x;
			pos.y += addPos.y;
			pos.theta += addPos.theta;

			return 0;
		}

		// Drives chassis to given pose
		int driveTo(amp::pose pose, amp::moveSettings settings = { 12000 }) {
			tank(amp::poseTo(pos,
			                 pose,
			                 { moveCtrl.lateralKP, moveCtrl.angularKP },
			                 settings));
			return 0;
		}

		// Odom handler
		void odomTick() {
			double forward = chassisSensors.vertical.rotToCm();
			double sideways = chassisSensors.horizontal.rotToCm();

			double imuHeading = chassisSensors.imu.get_heading();

			double theta = amp::constrainAngle(
			    90.0 - imuHeading); // useable theta for math

			double dForward = forward - oldMovement.y;

			double dSideways = sideways - oldMovement.x;

			double dTheta = amp::constrainAngle(theta - oldMovement.theta);

			double dThetaRad = dTheta * (std::numbers::pi / 180.0);

			// How far bot has gone forward
			dForward -= chassisSensors.vertical.getOffset() * dThetaRad;

			// How far bot has gone to side
			dSideways -= chassisSensors.horizontal.getOffset() * dThetaRad;

			double avgTheta = oldMovement.theta + dTheta / 2.0;

			// How much the bots X has increased
			double dx =
			    dForward * std::cos(avgTheta * (amp::numbers::PI / 180)) +
			    dSideways * std::sin(avgTheta * (amp::numbers::PI / 180));

			// How much the bots Y has increased
			double dy =
			    dForward * std::sin(avgTheta * (amp::numbers::PI / 180)) -
			    dSideways * std::cos(avgTheta * (amp::numbers::PI / 180));

			// Update estimates and changes over time
			oldOdomPos = odomEstimate;

			odomEstimate.x += dx;
			odomEstimate.y += dy;
			odomEstimate.theta = theta;

			oldMovement.x = sideways;
			oldMovement.y = forward;
			oldMovement.theta = theta;
		}

	private:
		// Initialize chassis variables
		std::vector<amp::motor>& leftWheels;
		std::vector<amp::motor>& rightWheels;
		chassisSensors& chassisSensors;
		motionController moveCtrl;
		amp::pose pos{};
		amp::pose odomEstimate{};
		amp::pose distanceEstimate{};

		amp::pose oldOdomPos{};

		amp::pose oldMovement{}; // Old forward / sideways / theta
	};
}