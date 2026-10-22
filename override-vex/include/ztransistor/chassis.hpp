#include "zamp/chassis.hpp"
#include "zamp/consts.hpp"
#include "zamp/math.hpp"
#include "ztransistor/consts.hpp"
#include "ztransistor/main.hpp"
#include <cmath>
namespace amp {
	class moveToPose : amp::command {
	public:
		moveToPose(amp::pose pose,
		           amp::chassis& chassis,
		           std::pair<double, double> threshold,
		           amp::motionSettings settings = { 12700, 300, 12000 })
		    : pose(pose)
		    , chassis(chassis)
		    , settings(settings) {}
		bool run() {
			amp::poseTo(
			    chassis.getPos(),
			    pose,
			    { chassis.getCtrl().lateralKP, chassis.getCtrl().angularKP },
			    { settings.maxVolt });
			if (std::hypot(std::abs(pose.x - chassis.getPos().x),
			               std::abs(pose.y - chassis.getPos().y)) <
			    threshold.first)
				return false;
			return true;
		}

	private:
		amp::pose pose;
		amp::chassis& chassis;
		std::pair<double, double> threshold;
		amp::motionSettings settings;
	};
}