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

	private:
		std::vector<amp::motor>& leftWheels;
		std::vector<amp::motor>& rightWheels;
		sensors& sensors;
		amp::pose pos;
	};
} // namespace zirconium