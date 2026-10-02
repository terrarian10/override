#pragma once
#include "odometry.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "zamp/math.hpp"
#include "zamp/motor.hpp"
#include <cstdint>
#include <map>
#include <optional>
#include <vector>
namespace amp {
	struct sensors {
		odometryWheel horizontal;
		odometryWheel vertical;
		pros::Imu imu;
		std::optional<pros::Distance> front;
		std::optional<pros::Distance> front_2;
		std::optional<pros::Distance> right;
		std::optional<pros::Distance> right_2;
		std::optional<pros::Distance> left;
		std::optional<pros::Distance> left_2;
	};
	struct motionController {
		const double lateralKP = 3.0;
		const double lateralKD = 10.0;

		const double angularKP = 50.0;
		const double angularKD = 5.0;
	};
	class chassis {
	public:
		explicit chassis(std::vector<amp::motor>& leftWheels,
		                 std::vector<amp::motor>& rightWheels,
		                 sensors& sensors,
		                 motionController moveCtrl)
		    : leftWheels(leftWheels)
		    , rightWheels(rightWheels)
		    , sensors(sensors)
		    , moveCtrl(moveCtrl) {

		    };

		int tank(std::int32_t left, std::int32_t right) {
			for (auto& i : leftWheels) {
				i.mod(left);
			}
			for (auto& i : rightWheels) {
				i.mod(right);
			}
			return 0;
		}
		int arcade(std::int32_t left, std::int32_t right) {
			for (auto& i : leftWheels) {
				i.mod(left);
			}
			for (auto& i : rightWheels) {
				i.mod(right);
			}
			return 0;
		}
		int addVolts(std::int32_t forward, std::int32_t turn) {
			for (auto& i : leftWheels) {
				i.set(forward - turn);
			}
			for (auto& i : rightWheels) {
				i.set(forward + turn);
			}
			return 0;
		}
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
		int resetPos(amp::pose setPos) {
			setPos.theta *= amp::numbers::toRADS;
			pos = setPos;
			return 0;
		}
		int modifyPos(amp::pose addPos) {
			pos.x += addPos.x;
			pos.y += addPos.y;
			pos.theta += addPos.theta * amp::numbers::toRADS;
			return 0;
		}
		void odomTick() {
			double forward = sensors.vertical.rotToCm();
			double sideways = sensors.horizontal.rotToCm();

			//  IMU To Radian
			//
			// 0 rad   = +X
			// pi/2    = +Y
			// Because ofc it cant be simple where 0 rad = +y and keep the math
			// sane positive = counterclockwise sobbbbb screw you
			double imuHeading =
			    sensors.imu.get_heading() * amp::numbers::toRADS;

			double theta =
			    amp::constrainAngle(amp::numbers::PI / 2.0 - imuHeading);

			double dForward = forward - oldMovement.y;

			double dSideways = sideways - oldMovement.x;

			double dTheta = amp::constrainAngle(theta - oldMovement.theta);

			dForward -= sensors.vertical.getOffset() * dTheta;

			dSideways -= sensors.horizontal.getOffset() * dTheta;

			double avgTheta = oldMovement.theta + dTheta / 2.0;

			double dx =
			    dForward * std::cos(avgTheta) + dSideways * std::sin(avgTheta);

			double dy =
			    dForward * std::sin(avgTheta) - dSideways * std::cos(avgTheta);

			oldOdomPos = odomEstimate;

			odomEstimate.x += dx;
			odomEstimate.y += dy;
			odomEstimate.theta = theta;

			oldMovement.x = sideways;
			oldMovement.y = forward;
			oldMovement.theta = theta;
		}

	private:
		std::vector<amp::motor>& leftWheels;
		std::vector<amp::motor>& rightWheels;
		sensors& sensors;
		motionController moveCtrl;
		amp::pose pos;
		amp::pose odomEstimate;
		amp::pose distanceEstimate;

		amp::pose oldOdomPos;

		amp::pose oldMovement; // Old forward / sideways / theta
	};
}