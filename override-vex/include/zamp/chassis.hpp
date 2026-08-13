#include "zamp/consts.hpp"
#include "zamp/motor.hpp"
#include "zamp/odometry.hpp"
#include <cstdint>
#include <vector>
namespace amp {
	struct sensors {
		odometryWheel horizontal;
		odometryWheel vertical;
	};
	class chassis {
	public:
		explicit chassis(std::vector<amp::motor>& leftWheels,
		                 std::vector<amp::motor>& rightWheels,
		                 sensors& sensors)
		    : leftWheels(leftWheels)
		    , rightWheels(rightWheels)
		    , sensors(sensors) {

		    };

		int tank(std::int32_t left, std::int32_t right) {
			for (auto& i : leftWheels) {
				i.set(left);
			}
			for (auto& i : rightWheels) {
				i.set(right);
			}
			return 0;
		}
		int resetPos(amp::pose setPos) {
			pos = setPos;
			return 0;
		}
		int modifyPos(amp::pose addPos) {
			pos.x += addPos.x;
			pos.y += addPos.y;
			pos.theta += addPos.theta;
			return 0;
		}
		void odomTick() {
			std::double_t forward = sensors.vertical.rotToCm();
			std::double_t sideways = sensors.horizontal.rotToCm();
			std::double_t theta = pos.theta;

			std::double_t dForward = forward - oldMovement.y;
			std::double_t dSideways = sideways - oldMovement.x;
			std::double_t dTheta = theta - oldMovement.theta;

			dForward -= sensors.vertical.getOffset() * dTheta;
			dSideways -= sensors.horizontal.getOffset() * dTheta;

			std::double_t avgTheta = oldMovement.theta + dTheta / 2.0;

			std::double_t dx =
			    dForward * std::sin(avgTheta) + dSideways * std::cos(avgTheta);
			std::double_t dy =
			    dForward * std::cos(avgTheta) - dSideways * std::sin(avgTheta);
			oldPos = pos;
			pos.x = dx;
			pos.y = dy;
		}

	private:
		std::vector<amp::motor>& leftWheels;
		std::vector<amp::motor>& rightWheels;
		sensors& sensors;
		amp::pose pos;
		amp::pose oldPos;

		amp::pose oldMovement; // Old forward / sideways / theta
	};
}